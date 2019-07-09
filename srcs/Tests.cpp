#include <set>
#include <string>
#include "../includes/Tests.h"

void PrintLine() {
    std::cout << "-----------------------------------------------\n";
}

void test_Monomials() {
    Monomial monom1({1, 4, 0, 0, 0, 0, 1, 0, 0, 12}, 15);
    Monomial monom2({{0, 2}, {2, 1}, {6, 1}, {9, 17}}, 7);
    std::cout << "m1 = " << monom1 << '\n' << "m2 = " << monom2 << '\n';

    std::cout << "lcm(m1, m2) = " << lcm(monom1, monom2) << '\n';
    std::cout << "gcd(m1, m2) = " << (monom1, monom2) << '\n';
    std::cout << "deg(m1) = " << deg(monom1) << '\n';
    std::cout << "deg(m2) = " << deg(monom2) << '\n';
    PrintLine();

    Monomial monom3({{2, 5}, {4, 2}}, 2);
    Monomial monom4({{2, 12}, {3, 1}}, -1);
    std::cout << "m3 = " << monom3 << '\n' << "m4 = " << monom4 << "\n\n";
    std::cout << "m3 * m4 =\t" << monom3 * monom4 << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "m3 *= m4 =\t" << (monom3 *= monom4) << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    PrintLine();

    Monomial monom5({3, 0, 4}, 2);
    Monomial monom6({3, 0, 4}, 1);
    std::cout << (monom5 == monom6) << '\t'
            << (monom5 == 2 * monom6) << '\t'
            << (3 * monom5 == monom6 * 6) << '\n';
    PrintLine();
}

std::string TrueFalse(bool value) {
    return value ? "true" : "false";
}

template <typename Comp>
void test_comp(const std::vector<Monomial>& monoms) {
    Comp comparator;
    for (size_t i = 0; i != monoms.size(); ++i) {
        for (size_t j = 0; j != monoms.size(); ++j) {
            if (i != j) {
                std::cout << 'm' << i + 1 << " < m" << j + 1 << " is "
                        << TrueFalse(comparator(monoms[i], monoms[j])) << '\n';
            }
        }
    }

    std::set<Monomial, Comp> mon_set(monoms.begin(), monoms.end());
    std::cout << "\nset:\n";
    for (const auto& monom : mon_set) {
        std::cout << monom << '\n';
    }
    PrintLine();
}

void test_MonomialOrder() {
    std::vector<Monomial> monoms({
        {std::vector<i32>({1, 2, 31})},  // 0
        {std::vector<i32>({2, 3, 7, 3, 7}), 1},
        {std::vector<i32>({4, 1, 7, 10, 0}), 1},
        {std::vector<i32>({2, 3, 7, 0, 11}), 1}
    });

    for (size_t i = 0; i != monoms.size(); ++i) {
        std::cout << 'm' << i + 1 << " = " << monoms[i] << '\n';
    }
    PrintLine();

    std::cout << "deg comp:\n";
    test_comp<DegComp>(monoms);

    std::cout << "lex comp:\n";
    test_comp<LexComp>(monoms);

    std::cout << "re_lex comp:\n";
    test_comp<ReLexComp>(monoms);

    std::cout << "deg-lex comp:\n";
    test_comp<CombineComp<DegComp, LexComp>>(monoms);
}
