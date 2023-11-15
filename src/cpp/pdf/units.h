#pragma once

#include <string>
#include <vector>

namespace pdf {
    
    struct TxtPos
    {
        float left, top, right, bottom;
        int rotation;
    };    
    struct TxtWord
    {
        TxtPos pos;
        std::string word;
    };    

    struct PdfPage
    {
        std::string text;
        std::vector<TxtWord> words;
    };

    struct PdfResult
    {
        std::vector<PdfPage> pages;
        std::string layout;
        std::string mode;
    };
}
