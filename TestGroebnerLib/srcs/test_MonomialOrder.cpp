#include "../includes/Tests.h"

template <typename Comp>
void test_comp(const std::vector<gb::Monomial>& monoms) {
    Comp comparator;
    for (size_t i = 0; i != monoms.size(); ++i) {
        for (size_t j = 0; j != monoms.size(); ++j) {
            std::cout << 'm' << i + 1 << " < m" << j + 1 << " is "
                    << TrueFalse(comparator(monoms[i], monoms[j])) << '\n';
        }
    }

    std::set<gb::Monomial, Comp> mon_set(monoms.begin(), monoms.end());
    std::cout << "\nset:\n";
    for (const auto& monom : mon_set) {
        std::cout << monom << '\n';
    }
    PrintLine();
}

void test_MonomialOrder() {
    std::cout << "Test MonomialOrder:\n";
    std::vector<gb::Monomial> monoms({
        {std::vector<i32>(0)},
        {std::vector<i32>({2, 3, 7, 3, 7})},
        {std::vector<i32>({4, 1, 7, 10})},
        {std::vector<i32>({2, 3, 7, 0, 11})}
    });

    for (size_t i = 0; i != monoms.size(); ++i) {
        std::cout << 'm' << i + 1 << " = " << monoms[i] << '\n';
    }
    PrintLine();

    std::cout << "deg comp:\n";
    test_comp<gb::DegComp>(monoms);

    std::cout << "lex comp:\n";
    test_comp<gb::LexComp>(monoms);

    std::cout << "re_lex comp:\n";
    test_comp<gb::ReLexComp>(monoms);

    std::cout << "deg-lex comp:\n";
    test_comp<gb::DegLexComp>(monoms);
    PrintLine();
}