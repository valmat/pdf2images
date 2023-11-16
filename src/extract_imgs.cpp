#include <iostream>
#include "configs/Configs.h"
#include "pdf/Pdf.h"
#include "utils/progress_bar.h"

int main(int argc, char* argv[])
{
    const Configs cfg(argc, argv);
    if (!cfg) {
        return 1;
    }

    if(!pdf::Pdf::is_pdf_fext(cfg.inp_file)) {
        std::cerr << "File " << cfg.inp_file << " is not a pdf." << std::endl; 
        return 2;
    }

    pdf::Pdf doc(cfg.inp_file);

    if(!doc.is_valid()) {
        std::cerr << "Failed to read pdf file " << cfg.inp_file << std::endl; 
        return 3;
    }

    if(!doc.is_pdf()) {
        std::cerr << "File " << cfg.inp_file << " is not a pdf." << std::endl; 
        return 4;
    }    

    if (doc.is_locked()) {
        std::cerr << "Locked document " << cfg.inp_file << std::endl; 
        return 5;
    }
    if (doc.is_encrypted()) {
        std::cerr << "Encrypted document " << cfg.inp_file << std::endl; 
        return 6;
    }

    auto img_fmt = !cfg.bw ?
        pdf::Renderer::img_formats::img_rgb24 :
        pdf::Renderer::img_formats::img_gray8;

    auto progress_callback = cfg.quiet ? nullptr : &progress_bar_update;
    
    pdf::Renderer pdfRenderer(img_fmt);

    try {
        doc.to_images(
            pdfRenderer,
            cfg.out_dir,
            cfg.pdf_render_fmt,
            cfg.pdf_render_pages_from,
            cfg.pdf_render_pages_limit,
            cfg.pdf_render_xres,
            cfg.pdf_render_yres,
            cfg.pdf_render_dpi,
            progress_callback
        );
    } catch (pdf::Error& err) {
        std::cerr << err.what() << std::endl; 
        return 7;
    }

    return 0;
}