#pragma once
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "Renderer.h"

// Forward declaration
namespace poppler {
    class document;
    class page;
}

namespace pdf {

    using file_buff_t = std::vector<char>;

    class Pdf final
    {
        std::unique_ptr<poppler::document, void(*)(poppler::document*)> _doc{nullptr, nullptr};
        std::vector<std::unique_ptr<poppler::page, void(*)(poppler::page*)>> _pages;

        bool _is_pdf   = false;
        bool _is_valid = false;

        struct load_from_raw_t {};
    public:
        constexpr static load_from_raw_t load_from_raw {};

        Pdf() = default;
        ~Pdf() = default;

        Pdf(const std::string& file_name) noexcept;
        Pdf(std::string_view data, load_from_raw_t) noexcept;

        Pdf(Pdf &&) noexcept            = default;
        Pdf &operator=(Pdf &&) noexcept = default;
        Pdf(const Pdf &)                = delete;
        Pdf &operator=(const Pdf &)     = delete;

        bool is_pdf   () const noexcept { return _is_pdf;   }
        bool is_valid () const noexcept { return _is_valid; }

        bool is_locked    () const noexcept;
        bool is_encrypted () const noexcept;

        std::string mode   () const noexcept;
        std::string layout () const noexcept;

        size_t pages_num() const noexcept { return _pages.size(); }
        std::vector<PdfPage> pages() const;

        PdfResult aggregate() const;

        void to_images(
            const Renderer& renderer,
            const std::string& to_file_prefix,
            std::function<void(uint, uint, uint)> progress_callback = nullptr,
            const std::string& img_format = "png",
            int pages_from = 1,
            int pages_limit = -1,
            double xres = 72.0,
            double yres = 72.0,
            int dpi = -1,
            int x = -1,
            int y = -1,
            int w = -1,
            int h = -1,
            Renderer::rotations rotate = Renderer::rotate_0) const;        

        [[nodiscard]]
        std::vector<file_buff_t> to_buffs(
            const Renderer& renderer,
            const std::string& img_format = "png",
            int pages_limit = -1,
            double xres = 72.0,
            double yres = 72.0,
            int dpi = -1,
            int x = -1,
            int y = -1,
            int w = -1,
            int h = -1,
            Renderer::rotations rotate = Renderer::rotate_0) const;

        void to_text(const std::string& output_dir,
            const std::string& out_prefix,
            const std::string& out_postfix,
            std::function<void(uint, uint, uint)> progress_callback,
            int pages_from = 1,
            int pages_limit = -1) const;

        void to_text(const std::string& output_file,
            bool nopagebreak,
            std::function<void(uint, uint, uint)> progress_callback,
            int pages_from = 1,
            int pages_limit = -1) const;

        static bool is_pdf_fext(const std::string& file_name) noexcept;

    private:
        void _init_pages() noexcept;
    };   
}
