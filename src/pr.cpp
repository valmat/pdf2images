#include <iostream>
#include <string>
#include "utils/progress_bar.h"

class ProgressBar {
    private: 
        unsigned int start;
        unsigned int end;
        static const unsigned int bar_width = 70;

    public:
        ProgressBar(unsigned int start, unsigned int end) : start(start), end(end) {}
                
        void update(unsigned int current)
        {
            std::cout << "\r" << std::flush;
            double progress = static_cast<double>(current - start) / (end - start);

            unsigned int pos = static_cast<unsigned int>(bar_width * progress);
            for (unsigned int i = 0; i < bar_width; ++i) {
                if (i < pos) std::cout << "\033[32m\033[1m#\033[0m";
                else if (i == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << " \033[1m\033[32m" << int(progress * 100.0) << "\033[0m%"
                      << " (\033[1m\033[34m" << current << "\033[37m / \033[36m" << start << "-" << end << "\033[0m)";
            std::flush(std::cout);
        }
};



                
// constexpr static unsigned int progress_bar_width = 70;
// void progress_bar_update(uint current, uint first, uint last)
// {
//     std::cout << "\r" << std::flush;
//     double progress = static_cast<double>(current - first) / (last - first);

//     unsigned int pos = static_cast<unsigned int>(progress_bar_width * progress);
//     for (unsigned int i = 0; i < progress_bar_width; ++i) {
//         if (i < pos) std::cout << "\033[32m\033[1m#\033[0m";
//         else if (i == pos) std::cout << ">";
//         else std::cout << " ";
//     }
//     std::cout << " \033[1m\033[32m" << int(progress * 100.0) << "\033[0m%"
//               << " (\033[1m\033[34m" << current << "\033[37m / \033[36m" << first << "-" << last << "\033[0m)";
//     std::flush(std::cout);
// }



#include <unistd.h> // Для sleep()

int main(){
    unsigned int start = 88;
    unsigned int end = 220;
    
    ProgressBar pb(start, end);
    
    for(unsigned int i=start; i<=end; i++){
        // pb.update(i);
        progress_bar_update(i, start, end);
        usleep(100000); // Пауза для демонстрации
    }

    std::cout << "\n"; // Переход на новую строку после завершения
    return 0;
}
