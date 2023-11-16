#pragma once

namespace pdf {
    struct Error : public std::runtime_error
    {
        Error(const char* msg) : std::runtime_error(msg) {}
    };    
}