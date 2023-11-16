#include <string>
#include <iostream>
#include "progress_bar.h"

constexpr static uint progress_bar_width = 70;
void progress_bar_update(uint current, uint first, uint last) noexcept
{
    std::cout << "\r" << std::flush;
    double progress = static_cast<double>(current - first) / (last - first);

    uint pos = static_cast<uint>(progress_bar_width * progress);
    for (uint i = 0; i < progress_bar_width; ++i) {
        if (i < pos) {
            std::cout << "\033[32m\033[1m#\033[0m";
        } else if (i == pos) {
            std::cout << ">";
        } else {
            std::cout << " ";
        }
    }
    std::cout << " \033[1m\033[32m" << int(progress * 100.0) << "\033[0m%"
              << " (\033[1m\033[34m" << current << "\033[37m / \033[36m"
              << first << "-" << last << "\033[0m)";

    if (current == last) {
        std::cout << std::endl;
    }
    std::cout << std::flush;
}