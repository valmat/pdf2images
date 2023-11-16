#pragma once

struct AppConfigs
{
    std::string inp_file;
    std::string out_dir = ".";

    // Pdf render images format
    std::string pdf_render_fmt = "png";
    // Pdf render pages limit (-1: no limits)
    int pdf_render_pages_limit = 30;
    // Pdf render the first page
    int pdf_render_pages_from = 1;
    // Pdf render xres
    uint pdf_render_xres = 150;
    // Pdf render yres
    uint pdf_render_yres = 150;
    // Pdf render dpi out (-1: system)
    int pdf_render_dpi = 600;

    bool bw = false;

    // is arg parsing valid
    bool valid() const 
    {
        return _valid;
    }
    operator bool() const 
    {
        return _valid;
    }

    AppConfigs(int argc, char* argv[]) noexcept;

    AppConfigs()                              = default;
    AppConfigs(const AppConfigs &)            = default;
    AppConfigs(AppConfigs &&)                 = default;
    AppConfigs &operator=(const AppConfigs &) = default;
    AppConfigs &operator=(AppConfigs &&)      = default;
    ~AppConfigs()                             = default;
private:
    // is arg parsing valid
    bool _valid = false;
};
