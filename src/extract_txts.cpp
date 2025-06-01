#include <iostream>
#include "configs/ConfigsTxt.h"
#include "pdf/Pdf.h"
#include "utils/check_create.h"
#include "utils/progress_bar.h"

int main(int argc, char* argv[])
{
    const ConfigsTxt cfg(argc, argv);
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
        if(cfg.out_file.empty()) {
            doc.to_text(
                cfg.out_dir,
                cfg.out_file_prefix,
                cfg.out_file_postfix,
                progress_callback,
                cfg.pdf_pages_from,
                cfg.pdf_pages_limit);
        } else {
            doc.to_text(
                cfg.out_file,
                cfg.nopagebreak,
                progress_callback,
                cfg.pdf_pages_from,
                cfg.pdf_pages_limit);
        }

    } catch (pdf::Error& err) {
        std::cerr << err.what() << std::endl; 
        return 3;
    }

    return 0;
}
