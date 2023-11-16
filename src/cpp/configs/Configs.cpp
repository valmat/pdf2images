#include <iostream>
#include "Configs.h"
#include "argagg/argagg.hpp"

Configs::Configs(int argc, char* argv[]) noexcept
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
            "Pdf render images format (default 'png'. Use 'png', 'jpg', 'tiff' etc)", 1
        },{
            "pref", {"-p", "--pref"},
            "Output files prefix", 1
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
        },{
            "quiet", {"-q","--quiet"},
            "Quiet mode", 0
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
        std::cerr << args.program << " -i <input_file.pdf> [options]" << std::endl;
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

    bw    = !!args["bw"];
    quiet = !!args["quiet"];

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
    if(!!args["pref"]) {
        out_file_prefix = args["pref"].as<std::string>();
    }

    _valid = true;
}