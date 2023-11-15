#pragma once

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "units.h"
#include "Renderer.h"
#include "err.h"

// Fiorward declaration
namespace poppler {
    class page_renderer;
    class page;
}

namespace pdf {

    class Renderer
    {
        poppler::page_renderer* _renderer = nullptr;

    public:
        enum rotations { rotate_0, rotate_90, rotate_180, rotate_270 };
        enum img_formats { img_rgb24 = 2, img_argb32, img_gray8, img_bgr24};

        Renderer(img_formats = img_gray8);
        ~Renderer();

        Renderer(Renderer &&)                 = delete;
        Renderer &operator=(Renderer &&)      = delete;
        Renderer(const Renderer &)            = delete;
        Renderer &operator=(const Renderer &) = delete;

        static std::vector<std::string> supported_image_formats() noexcept;

        void renderer(const poppler::page* page,
            const std::string& to_file,
            const std::string& img_format = "png",
            double xres = 144.0,
            double yres = 144.0,
            int dpi = -1,
            int x = -1,
            int y = -1,
            int w = -1,
            int h = -1,
            rotations rotate = rotate_0) const;
    };   
}