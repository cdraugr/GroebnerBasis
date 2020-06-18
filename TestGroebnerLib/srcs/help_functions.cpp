#include "Tests.h"

void PrintLine(u32 count) {
    while (count--) {
        for (u32 i = 0; i != 50; ++i) {
            std::cout << '-';
        }
        std::cout << '\n';
    }
}
