#include <iostream>
#include "argagg/argagg.hpp"
#include "pdf/units.h"
#include "configs/AppConfigs.h"
#include "pdf/Pdf.h"


int main(int argc, char* argv[])
{
    argagg::parser argparser {{
        {
            "help", {"-h", "--help"},
            "Print help and exit", 0
        },{
            "from", {"-f", "--from"},
            "From file", 1},
        {
            "conf", {"-c", "--conf"},
            "Configs file", 1
        },{
            "to", {"-t", "--to"},
            "To dir", 1
        },{
            "bw", {"--bw"},
            "Make black and white (default: off)", 0
        }
    }};
    argagg::parser_results args;
      
    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception& e) {
        argagg::fmt_ostream fmt(std::cerr);
        std::cerr << argparser << std::endl;
        std::cerr << "Encountered exception while parsing arguments: " << e.what() << std::endl;
        return 1;
    }
    if (args["help"]) {
        
        std::cerr << args.program << " [options]" << std::endl;
        std::cerr << argparser << std::endl;
        return 1;
    }
    if (!args["from"] || !args["to"]) {
        std::cerr << argparser << std::endl;
        std::cerr << args.program << ": '--from' and '--to' options are required" << std::endl;
        return 1;
    }

    std::string ini_file_name = args["conf"].as<std::string>("-");
    
    std::string file_name = args["from"].as<std::string>();
    std::string to_dir    = args["to"]  .as<std::string>();

    AppConfigs cfg;
    {
        std::string ini_file(ini_file_name);
        if (ini_file != "-") {
            cfg = AppConfigs(ini_file);
        }
        if (!cfg) {
            std::cerr << cfg.msg() << std::endl; 
            return 1;
        }
    }

    if(file_name.empty()) {
        std::cerr << "File name is empty." <<  std::endl; 
        return 1;
    }    
    if(to_dir.empty()) {
        std::cerr << "Dir name is empty." <<  std::endl; 
        return 1;
    }    

    bool is_pdf = pdf::Pdf::is_pdf_fext(file_name);
    
    if(!is_pdf) {
        std::cerr << "File " << file_name << " is not a pdf." << std::endl; 
        return 1;
    }

    if(is_pdf) {
        pdf::Pdf doc(file_name);

        if(!doc.is_valid()) {
            std::cerr << "Failed to read pdf file " << file_name << std::endl; 
            return 1;
        }

        is_pdf = doc.is_pdf();

        if(is_pdf) {
            if (doc.is_locked()) {
                std::cerr << "Locked document " << file_name << std::endl; 
                return 1;
            }
            if (doc.is_encrypted()) {
                std::cerr << "Encrypted document " << file_name << std::endl; 
                return 1;
            }

            auto img_fmt = !args["bw"] ?
                pdf::Renderer::img_formats::img_rgb24 :
                pdf::Renderer::img_formats::img_gray8;
            
            pdf::Renderer pdfRenderer(img_fmt);

            if(to_dir.back() != '/') {
                to_dir += '/';
            }

            try {
                doc.to_images(pdfRenderer, to_dir, cfg.pdf_render_fmt, cfg.pdf_render_pages_limit, cfg.pdf_render_xres, cfg.pdf_render_yres, cfg.pdf_render_dpi);
            } catch (pdf::Error& err) {
                std::cerr << err.what() << std::endl; 
                return 1;

            }
        }
    }

    return 0;
}

// bin/extract_imgs.bin configs-dev.ini ../test-docs/pdfs/12.pdf  /tmp/0/out
// bin/extract_imgs.bin -f /tmp/0/1.pdf -t /tmp/0/out/ --conf configs-dev.ini
// bin/extract_imgs.bin -f /tmp/0/1.pdf -t /tmp/0/out/