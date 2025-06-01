#pragma once

#include <string>
#include <vector>

namespace pdf {
    
    struct TxtPos final
    {
        float left, top, right, bottom;
        int rotation;
    };    
    struct TxtWord final
    {
        TxtPos pos;
        std::string word;
    };    

    struct PdfPage final
    {
        std::string text;
        std::vector<TxtWord> words;
    };

    struct PdfResult final
    {
        std::vector<PdfPage> pages;
        std::string layout;
        std::string mode;
    };
}
