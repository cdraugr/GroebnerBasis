#include "../includes/Tests.h"

void PrintLine(i32 count) {
    while (count--) {
        for (i32 i = 0; i != 50; ++i) {
            std::cout << '-';
        }
        std::cout << '\n';
    }
}

std::string TrueFalse(bool value) {
    return value ? "true" : "false";
}
