#pragma once

struct Configs
{
    std::string inp_file;
    std::string out_dir = "./";
    std::string out_file_prefix;

    // Pdf render images format
    std::string pdf_render_fmt = "png";
    // Pdf render pages limit (-1: no limits)
    int pdf_render_pages_limit = -1;
    // Pdf render the first page
    int pdf_render_pages_from = 1;
    // Pdf render xres
    uint pdf_render_xres = 150;
    // Pdf render yres
    uint pdf_render_yres = 150;
    // Pdf render dpi out (-1: system)
    int pdf_render_dpi = -1;

    bool bw = false;
    bool quiet = false;

    // is arg parsing valid
    bool valid() const 
    {
        return _valid;
    }
    operator bool() const 
    {
        return _valid;
    }

    Configs(int argc, char* argv[]) noexcept;

    Configs()                           = default;
    Configs(const Configs &)            = default;
    Configs(Configs &&)                 = default;
    Configs &operator=(const Configs &) = default;
    Configs &operator=(Configs &&)      = default;
    ~Configs()                          = default;
private:
    // is arg parsing valid
    bool _valid = false;
};
