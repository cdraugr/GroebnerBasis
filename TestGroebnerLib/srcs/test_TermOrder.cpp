#include "Tests.h"

template <typename Comp>
void test_comp(const std::vector<gb::Term<Rational>>& monoms) {
    Comp comparator;
    for (size_t i = 0; i != monoms.size(); ++i) {
        for (size_t j = 0; j != monoms.size(); ++j) {
            std::cout << std::boolalpha << 't' << i + 1 << " < t" << j + 1 << " is "
                    << comparator(monoms[i], monoms[j]) << '\n';
        }
    }

    std::set<gb::Term<Rational>, Comp> mon_set(monoms.begin(), monoms.end());
    std::cout << "\nset:\n";
    for (const auto& monom : mon_set) {
        std::cout << monom << '\n';
    }
    PrintLine();
}

void test_TermOrder() {
    std::cout << "Test TermOrder:\n";
    std::vector<gb::Term<Rational>> monoms({
        {0},
        {gb::Monomial({2, 3, 7, 3, 7}), 1},
        {gb::Monomial({4, 1, 7, 10}), 1},
        {gb::Monomial({2, 3, 7, 0, 11}), 1}
    });
    for (size_t i = 0; i != monoms.size(); ++i) {
        std::cout << "term" << i + 1 << " = " << monoms[i] << '\n';
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
