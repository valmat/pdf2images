#pragma once

struct ConfigsTxt final
{
    // Input PDF file
    std::string inp_file{};

    // Directory to save output files
    std::string out_dir{"./"};
    std::string out_file_prefix{""};
    std::string out_file_postfix{".txt"};

    // Output file. If this is set, options for saving to a directory are ignored
    std::string out_file{};

    // PDF: extract from this page number
    int pdf_pages_from = 1;
    // PDF: limit of pages to extract (-1 means no limit)
    int pdf_pages_limit = -1;

    // Mode without debug information
    bool quiet = false;

    // Do not add a separator between pages.
    // Works only when output is in a single file
    bool nopagebreak = false;

    // Is argument parsing valid
    bool valid() const 
    {
        return _valid;
    }
    operator bool() const 
    {
        return _valid;
    }

    ConfigsTxt(int argc, char* argv[]) noexcept;

private:
    // Is argument parsing valid
    bool _valid = false;
};
