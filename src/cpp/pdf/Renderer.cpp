#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Renderer.h"
#include <poppler-page-renderer.h>

namespace pdf {

    Renderer::Renderer(Renderer::img_formats img_format) :
        _renderer(new poppler::page_renderer())
    {
        _renderer->set_render_hint(poppler::page_renderer::antialiasing,      true);
        _renderer->set_render_hint(poppler::page_renderer::text_antialiasing, true);
        _renderer->set_image_format(static_cast<poppler::image::format_enum>(img_format));
    }

    Renderer::~Renderer()
    {
        delete _renderer;
    }

    std::vector<std::string> Renderer::supported_image_formats() noexcept
    {
        return poppler::image::supported_image_formats();
    }

    void Renderer::renderer(const poppler::page* page,
        const std::string& to_file,
        const std::string& img_format,
        double xres,
        double yres,
        int dpi,
        int x,
        int y,
        int w,
        int h,
        Renderer::rotations rotate) const
    {
        poppler::image img = _renderer->render_page(page, xres, yres, x, y, w, h, static_cast<poppler::rotation_enum>(rotate));

        if (!img.is_valid()) {
            throw Error("rendering failed");
        }

        if (!img.save(to_file, img_format, dpi)) {
            throw Error("rendering: saving to file failed");
        }
    }


}