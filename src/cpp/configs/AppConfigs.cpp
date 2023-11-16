#include <iostream>
#include "AppConfigs.h"
#include "argagg/argagg.hpp"

// Разрешаем создание неинициализированных объектов
AppConfigs::AppConfigs(int argc, char* argv[]) noexcept
{

    argagg::parser argparser {{
        {
            "help", {"-h", "--help"},
            "Print help and exit", 0
        },{
            "inp", {"-i", "--inp", "--input"},
            "Input file", 1
        },{
            "out", {"-o", "--out", "--output"},
            "Output directory (default '.')", 1
        },{
            "ext", {"-e", "--ext"},
            "Pdf render images format (default 'png')", 1
        },{
            "from", {"-f", "--from"},
            "The first page to render (default '1')", 1
        },{
            "lim", {"-l", "--lim"},
            "Pdf render pages limit (-1: no limits)", 1
        },{
            "xres", {"-x", "--xres"},
            "X resolution file", 1
        },{
            "yres", {"-y", "--yres"},
            "Y resolution", 1
        },{
            "dpi", {"-d", "--dpi"},
            "Pdf render dpi out (-1: system)", 1
        },{
            "bw", {"-g","--bw", "--gray"},
            "Make black and white render (default: off)", 0
        }
    }};

    argagg::parser_results args;
      
    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception& e) {
        argagg::fmt_ostream fmt(std::cerr);
        std::cerr << argparser << std::endl;
        std::cerr << "Encountered exception while parsing arguments: " << e.what() << std::endl;
        return;
    }
    if (args["help"]) {
        std::cerr << args.program << " [options]" << std::endl;
        std::cerr << argparser << std::endl;
        return;
    }
    if (!args["inp"]) {
        std::cerr << argparser << std::endl;
        std::cerr << args.program << ": '--inp' option is required" << std::endl;
        return;
    }

    inp_file = args["inp"].as<std::string>();
    if(inp_file.empty()) {
        std::cerr << "Input file name is empty." <<  std::endl; 
        return;
    }
    if (args["out"]) {
        out_dir = args["out"].as<std::string>();
        if(out_dir.empty()) {
            std::cerr << "Output directory name is empty." <<  std::endl; 
            return;
        }
        if(out_dir.back() != '/') {
            out_dir += '/';
        }
    }

    bw = !!args["bw"];

    if(!!args["ext"]) {
        pdf_render_fmt = args["ext"].as<std::string>();
    }
    if(!!args["from"]) {
        pdf_render_pages_from = args["from"].as<int>();
    }
    if(!!args["lim"]) {
        pdf_render_pages_limit = args["lim"].as<int>();
    }
    if(!!args["xres"]) {
        pdf_render_xres = args["xres"].as<uint>();
    }
    if(!!args["yres"]) {
        pdf_render_yres = args["yres"].as<uint>();
    }
    if(!!args["dpi"]) {
        pdf_render_dpi = args["dpi"].as<int>();
    }


    std::cout << "inp_file :" << inp_file << std::endl;
    std::cout << "out_dir :" << out_dir << std::endl;
    std::cout << "pdf_render_fmt :" << pdf_render_fmt << std::endl;
    std::cout << "pdf_render_pages_limit :" << pdf_render_pages_limit << std::endl;
    std::cout << "pdf_render_pages_from :" << pdf_render_pages_from << std::endl;
    std::cout << "pdf_render_xres :" << pdf_render_xres << std::endl;
    std::cout << "pdf_render_yres :" << pdf_render_yres << std::endl;
    std::cout << "pdf_render_dpi :" << pdf_render_dpi << std::endl;
    std::cout << "bw :" << bw << std::endl;

    
    _valid = true;
}