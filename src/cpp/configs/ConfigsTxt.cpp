#include <iostream>
#include "ConfigsTxt.h"
#include "argagg/argagg.hpp"

ConfigsTxt::ConfigsTxt(int argc, char* argv[]) noexcept
{
    argagg::parser argparser {{
        {
            "help", {"-h", "--help"},
            "Print help and exit", 0
        },{
            "inp", {"-i", "--inp", "--input"},
            "Input PDF file (required)", 1
        },{
            "out-dir", {"-o", "--out-dir"},
            "Output directory (default './')", 1
        },{
            "out-file", {"-O", "--out-file"},
            "Output file name (if set, directory options are ignored)", 1
        },{
            "prefix", {"-p", "--prefix"},
            "Output file name prefix", 1
        },{
            "postfix", {"-P", "--postfix"},
            "Output file name postfix", 1
        },{
            "from", {"-f", "--from"},
            "PDF: first page to extract (default '1')", 1
        },{
            "limit", {"-l", "--limit"},
            "PDF: limit number of pages to extract (-1 means no limit)", 1
        },{
            "quiet", {"-q", "--quiet"},
            "Quiet mode (no debug output)", 0
        },{
            "nopagebreak", {"-n", "--nopagebreak"},
            "Do not add separator between pages (works only with single output file)", 0
        }
    }};

    argagg::parser_results args;
      
    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing arguments: " << e.what() << std::endl;
        std::cerr << argparser << std::endl;
        return;
    }

    if (args["help"]) {
        std::cerr << args.program << " -i <input_file.pdf> [options]" << std::endl;
        std::cerr << argparser << std::endl;
        return;
    }

    if (!args["inp"]) {
        std::cerr << "Error: '--inp' option is required." << std::endl;
        std::cerr << argparser << std::endl;
        return;
    }

    inp_file = args["inp"].as<std::string>();
    if (inp_file.empty()) {
        std::cerr << "Error: Input file name is empty." << std::endl; 
        return;
    }

    if (args["out-file"]) {
        out_file = args["out-file"].as<std::string>();
        if(out_file.empty()) {
            std::cerr << "Error: Output file name is empty." << std::endl; 
            return;
        }
    } else if (args["out-dir"]) {
        out_dir = args["out-dir"].as<std::string>();
        if(out_dir.empty()) {
            std::cerr << "Error: Output directory name is empty." << std::endl; 
            return;
        }
        if(out_dir.back() != '/') {
            out_dir += '/';
        }
    }

    if (args["prefix"]) {
        out_file_prefix = args["prefix"].as<std::string>();
    }

    if (args["postfix"]) {
        out_file_postfix = args["postfix"].as<std::string>();
    }

    if (args["from"]) {
        pdf_pages_from = args["from"].as<int>();
        if (pdf_pages_from < 1) {
            std::cerr << "Error: '--from' must be >= 1." << std::endl;
            return;
        }
    }

    if (args["limit"]) {
        pdf_pages_limit = args["limit"].as<int>();
        if (pdf_pages_limit == 0 || pdf_pages_limit < -1) {
            std::cerr << "Error: '--limit' must be -1 (no limit) or positive integer." << std::endl;
            return;
        }
    }

    quiet = args["quiet"];
    nopagebreak = args["nopagebreak"];

    _valid = true;
}
