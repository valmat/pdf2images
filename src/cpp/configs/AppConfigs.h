#pragma once

// #include <vector>


struct AppConfigs
{
    // Pdf render images format
    std::string pdf_render_fmt = "png";
    // Pdf render pages limit (-1: no limits)
    int pdf_render_pages_limit = 30;
    // Pdf render xres
    double pdf_render_xres = 150;
    // Pdf render yres
    double pdf_render_yres = 150;
    // Pdf render dpi out (-1: system)
    int pdf_render_dpi = 600;

    // is arg parsing valid
    bool valid() const 
    {
        return _valid;
    }

    // is arg parsing valid
    operator bool() const 
    {
        return _valid;
    }

    std::string msg() const 
    {
        return _msg;
    }

    AppConfigs(const std::string& ini_file) noexcept;

    AppConfigs()                              = default;

    AppConfigs(const AppConfigs &)            = default;
    AppConfigs(AppConfigs &&)                 = default;

    AppConfigs &operator=(const AppConfigs &) = default;
    AppConfigs &operator=(AppConfigs &&)      = default;

    ~AppConfigs()                             = default;
private:
    // Usage string
    std::string _msg;

    // is arg parsing valid
    bool _valid = true;

};
