#include "Tests.hpp"

void print_line(u32 count) {
    while (count--) {
        std::cout << constants::DIVIDING_LINE << '\n';
    }
}

void assert_term_(const gb::Term& term, const std::vector<i64>& degrees) {
    std::map<gb::i64, gb::i64> map_degrees;
    for (size_t i = 0; i != degrees.size(); ++i) {
        if (degrees[i] != 0) {
            map_degrees[static_cast<gb::i64>(i)] = degrees[i];
        }
    }

    assert(term.GetDegrees() == map_degrees);
}
