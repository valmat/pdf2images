#include <iostream>
#include "configs/ConfigsImg.h"
#include "pdf/Pdf.h"
#include "utils/check_create.h"
#include "utils/progress_bar.h"

int main(int argc, char* argv[])
{
    const ConfigsImg cfg(argc, argv);
    if (!cfg) {
        return 1;
    }

    pdf::Pdf doc;
    if(auto opt_doc = check_create(cfg.inp_file); opt_doc.has_value()) {
        doc = std::move(opt_doc.value());
    } else {
        return 2;
    }

    auto progress_callback = cfg.quiet ? nullptr : &progress_bar_update;

    try {
        doc.to_text("./txt.txt", progress_callback, cfg.pdf_render_pages_from, cfg.pdf_render_pages_limit);

    } catch (pdf::Error& err) {
        std::cerr << err.what() << std::endl; 
        return 3;
    }

    return 0;
}
