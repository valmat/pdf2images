#include <iostream>
#include "configs/Configs.h"
#include "pdf/Pdf.h"
#include "utils/check_create.h"
#include "utils/progress_bar.h"

int main(int argc, char* argv[])
{
    const Configs cfg(argc, argv);
    if (!cfg) {
        return 1;
    }

    pdf::Pdf doc;
    if(auto opt_doc = check_create(cfg.inp_file); opt_doc.has_value()) {
        doc = std::move(opt_doc.value());
    } else {
        return 1;
    }

    auto img_fmt = !cfg.bw ?
        pdf::Renderer::img_formats::img_rgb24 :
        pdf::Renderer::img_formats::img_gray8;

    auto progress_callback = cfg.quiet ? nullptr : &progress_bar_update;

    pdf::Renderer pdfRenderer(img_fmt);

    try {
        // doc.to_images(
        //     pdfRenderer,
        //     cfg.out_dir + cfg.out_file_prefix,
        //     progress_callback,
        //     cfg.pdf_render_fmt,
        //     cfg.pdf_render_pages_from,
        //     cfg.pdf_render_pages_limit,
        //     cfg.pdf_render_xres,
        //     cfg.pdf_render_yres,
        //     cfg.pdf_render_dpi
        // );

    // XXX DBG
    doc.to_text("./txt.txt", progress_callback, cfg.pdf_render_pages_from, cfg.pdf_render_pages_limit);

    } catch (pdf::Error& err) {
        std::cerr << err.what() << std::endl; 
        return 7;
    }

    return 0;
}
