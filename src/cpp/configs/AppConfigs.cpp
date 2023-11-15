#include <iostream>
#include <cstdlib>

// #include "IniConfigs.h"
#include "AppConfigs.h"

// Разрешаем создание неинициализированных объектов
AppConfigs::AppConfigs(const std::string& ini_file) noexcept
{
    // vlm::IniConfigs cfg(ini_file);
    // if(!cfg) {
    //     _valid = false;
    //     _msg = "Error with open configuration file " + ini_file;;
    //     return;
    // }
    
    // // Pdf render images format
    // pdf_render_fmt         = cfg.get("pdf_render_fmt",         pdf_render_fmt);
    // // Pdf render pages limit (-1: no limits)
    // pdf_render_pages_limit = cfg.get("pdf_render_pages_limit", pdf_render_pages_limit);
    // // Pdf render
    // pdf_render_xres        = cfg.get("pdf_render_xres",        pdf_render_xres);
    // // Pdf render
    // pdf_render_yres        = cfg.get("pdf_render_yres",        pdf_render_yres);
    // // Pdf render dpi out (-1: system)
    // pdf_render_dpi         = cfg.get("pdf_render_dpi",         pdf_render_dpi);


}