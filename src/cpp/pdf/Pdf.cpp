#include <string>
#include <algorithm>
#include <filesystem>
#include "Pdf.h"

#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-destination.h>
#include <poppler-page.h>

namespace fs = std::filesystem;

namespace pdf {

    Pdf::~Pdf()
    {
        for(poppler::page* page: _pages) {
            delete page;
        }
        delete _doc;
    }

    Pdf::Pdf(const std::string& file_name) noexcept
    {
        {
            std::vector<char> bytes;
            std::ifstream file(file_name, std::ios::in | std::ios::binary);
            if(!file) {
                return;
            }
            _is_valid = true;
            
            bytes.reserve(4);
            // Check pdf magic number (https://en.wikipedia.org/wiki/Magic_number_%28programming%29)
            const char pdf_magic[4] = {'%','P','D','F'};
            for (size_t i = 0; i < 4; ++i) {
                char c;
                file.read(&c, 1);
                if(pdf_magic[i] != c) {return;}
                bytes.push_back(c);
            }

            auto it     = std::istreambuf_iterator<char>(file);
            auto it_end = std::istreambuf_iterator<char>();

            copy(it, it_end, back_inserter(bytes));
            _doc = poppler::document::load_from_data(&bytes);
        }
        // If magic number is checked and it was possible to create a document, we believe that we have a PDF
        _is_pdf = _doc;
        
        _init_pages();
    }

    Pdf::Pdf(std::string_view data, load_from_raw_t) noexcept
    {
        _is_valid = !data.empty();
        
        // Check pdf magic number
        const char pdf_magic[4] = {'%','P','D','F'};
        for (size_t i = 0; i < 4; ++i) {
            if(pdf_magic[i] != data[i]) {return;}
        }
        _doc = poppler::document::load_from_raw_data(data.data(), data.size());
        _is_pdf = _doc;
        
        _init_pages();
    }

    void Pdf::_init_pages() noexcept
    {
        if(!_doc) {return;}

        // Load pages
        size_t pages_num = _doc->pages();
        _pages.reserve(pages_num);
        for (size_t i = 0; i < pages_num; ++i) {
            _pages.emplace_back(_doc->create_page(i));
            if(!_pages.back()) {
                std::cerr << "Failed to create page " << i << std::endl;
                return;
            }
        }
    }

    bool Pdf::is_pdf_fext(const std::string& file_name) noexcept
    {
        if(file_name.size() < 4) {
            return false;
        }
        if('.' != file_name[file_name.size() - 4]) {
            return false;
        }
        char fext_chars[] = {'p', 'd', 'f', 'P', 'D', 'F'};
        for (int i = 0; i < 3; ++i) {
            char c = file_name[file_name.size() - 3 + i];
            if(fext_chars[i] != c && fext_chars[i + 3] != c) {
                return false;
            }            
        }
        return true;
    }

    bool Pdf::is_locked() const noexcept
    {
        return _doc->is_locked();
    }
    bool Pdf::is_encrypted() const noexcept
    {
        return _doc->is_encrypted();
    }

    std::string Pdf::mode() const noexcept
    {
        poppler::document::page_mode_enum pm = _doc->page_mode();
        switch (pm) {
            case poppler::document::use_none:     return "use_none";
            case poppler::document::use_outlines: return "use_outlines";
            case poppler::document::use_thumbs:   return "use_thumbs";
            case poppler::document::fullscreen:   return "fullscreen";
            case poppler::document::use_oc:       return "use_oc";
            case poppler::document::use_attach:   return "use_attach";
        }
        return "undefined";        
    }

    std::string Pdf::layout() const noexcept
    {
        poppler::document::page_layout_enum pl = _doc->page_layout();
        switch (pl) {
            case poppler::document::no_layout:        return "no_layout";
            case poppler::document::single_page:      return "single_page";
            case poppler::document::one_column:       return "one_column";
            case poppler::document::two_column_left:  return "two_column_left";
            case poppler::document::two_column_right: return "two_column_right";
            case poppler::document::two_page_left:    return "two_page_left";
            case poppler::document::two_page_right:   return "two_page_right";
        }
        return "undefined";
    }

    static std::string to_utf8(const poppler::ustring& x)
    {
        if(x.length()) {
            poppler::byte_array buf = x.to_utf8();
            return std::string(buf.data(), buf.size());
        }

        return {};
    }

    std::vector<PdfPage> Pdf::pages() const
    {
        std::vector<PdfPage> result;
        result.reserve(_pages.size());

        for (poppler::page* page: _pages) {
            PdfPage pdfPage;
            pdfPage.text = to_utf8(page->text());

            std::vector<TxtWord> words;
            for (poppler::text_box& box: page->text_list()) {

                TxtPos pos {
                    static_cast<float>(box.bbox().left()),
                    static_cast<float>(box.bbox().top()),
                    static_cast<float>(box.bbox().right()),
                    static_cast<float>(box.bbox().bottom()),
                    box.rotation() 
                };

                std::string word = to_utf8(box.text());
                words.emplace_back(TxtWord{std::move(pos), std::move(word)});
            }

            pdfPage.words = std::move(words);
            result.emplace_back(PdfPage{std::move(pdfPage)});
        }

        return result;
    }

    PdfResult Pdf::aggregate() const
    {
        return PdfResult {pages(), layout(), mode()};
    }

    void Pdf::to_images(
        const Renderer& renderer,
        const std::string& to_file_prefix,
        const std::string& img_format,
        int pages_from,
        int pages_limit,
        double xres,
        double yres,
        int dpi,
        std::function<void(uint, uint, uint)> progress_callback,
        int x,
        int y,
        int w,
        int h,
        Renderer::rotations rotate) const
    {
        if(0 == pages_from) {
            pages_from = 1;
        }

        size_t pages_first = (pages_from < 0) ?
            static_cast<size_t>(_pages.size() + pages_from) :
            static_cast<size_t>(pages_from - 1);

        size_t pages_end = (pages_limit > 0) ?
            std::min(static_cast<size_t>(pages_first + pages_limit), _pages.size()) :
            _pages.size();

        for (size_t i = pages_first; i < pages_end; ++i) {
            std::string to_file = to_file_prefix + std::to_string(i+1) + "." + img_format;
            renderer.renderer(_pages[i], to_file, img_format, xres, yres, dpi, x, y, w, h, rotate);
            if(progress_callback != nullptr) {
                progress_callback(i+1, pages_first+1, pages_end);
            }
        }
    }

    std::vector<file_buff_t> Pdf::to_buffs(
          const Renderer& renderer,
        const std::string& img_format,
        int pages_limit,
        double xres,
        double yres,
        int dpi,
        int x,
        int y,
        int w,
        int h,
        Renderer::rotations rotate) const
    {
        size_t pages_num = (pages_limit > 0) ?
            std::min(static_cast<size_t>(pages_limit), _pages.size()) :
            _pages.size();

        fs::path to_file_prefix = fs::temp_directory_path() / ("_p2i_" + std::to_string(reinterpret_cast<size_t>(this)) + "_");
        
        std::vector<file_buff_t> result;
        result.reserve(pages_num);
        for (size_t i = 0; i < pages_num; ++i) {
            std::string to_file = to_file_prefix.native() + std::to_string(i) + "." + img_format;
            renderer.renderer(_pages[i], to_file, img_format, xres, yres, dpi, x, y, w, h, rotate);
            {
                std::ifstream file(to_file, std::ios::binary | std::ios::in);
                if(!file) {
                    std::cerr << "Error loading image file "<< to_file << std::endl;
                    return {};
                }
                result.emplace_back( file_buff_t(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()) );
            }            
            fs::remove(to_file);
        }

        return result;
    }
}