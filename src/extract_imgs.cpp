#include <iostream>
#include "pdf/units.h"
#include "configs/AppConfigs.h"
#include "pdf/Pdf.h"


int main(int argc, char* argv[])
{
    const AppConfigs cfg(argc, argv);
    if (!cfg) {
        return 1;
    }

    if(!pdf::Pdf::is_pdf_fext(cfg.inp_file)) {
        std::cerr << "File " << cfg.inp_file << " is not a pdf." << std::endl; 
        return 1;
    }

    pdf::Pdf doc(cfg.inp_file);

    if(!doc.is_valid()) {
        std::cerr << "Failed to read pdf file " << cfg.inp_file << std::endl; 
        return 1;
    }

    if(!doc.is_pdf()) {
        std::cerr << "File " << cfg.inp_file << " is not a pdf." << std::endl; 
        return 1;
    }    

    if (doc.is_locked()) {
        std::cerr << "Locked document " << cfg.inp_file << std::endl; 
        return 1;
    }
    if (doc.is_encrypted()) {
        std::cerr << "Encrypted document " << cfg.inp_file << std::endl; 
        return 1;
    }

    auto img_fmt = !cfg.bw ?
        pdf::Renderer::img_formats::img_rgb24 :
        pdf::Renderer::img_formats::img_gray8;
    
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
            cfg.pdf_render_dpi
        );
    } catch (pdf::Error& err) {
        std::cerr << err.what() << std::endl; 
        return 1;

    }

    return 0;
}

// bin/extract_imgs.bin configs-dev.ini ../test-docs/pdfs/12.pdf  /tmp/0/out
// bin/extract_imgs.bin -f /tmp/0/1.pdf -t /tmp/0/out/ --conf configs-dev.ini
// bin/extract_imgs.bin -f /tmp/0/1.pdf -t /tmp/0/out/