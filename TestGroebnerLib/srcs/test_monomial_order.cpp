#include "Tests.hpp"

void test_monomial_order() {
    std::cout << "Test MonomialOrder:\n";
    std::vector<gb::Monomial<gb::fields::Rational>> monomials({
        {0},
        {{{2, 3, 7, 3, 7}}, 1},
        {{{4, 1, 7, 10}}, 1},
        {{{2, 3, 7, 0, 11}}, 1}
    });
    std::vector<std::vector<bool>> expected_comparations({
        {false, true, true, true, false, false, false, true, false, false, false, true, false, false, false, false},
        {false, true, true, true, false, false, true, false, false, false, false, false, false, true, true, false},
        {false, false, false, false, true, false, false, true, true, true, false, true, true, false, false, false},
        {false, true, true, true, false, false, true, true, false, false, false, true, false, false, false, false},
    });
    for (size_t i = 0; i != monomials.size(); ++i) {
        std::cout << "monomial" << i + 1 << " = " << monomials[i] << '\n';
    }
    print_line();

    std::cout << "deg comp:\n";
    test_monomial_comp_<gb::DegComp>(monomials, expected_comparations[0]);

    std::cout << "lex comp:\n";
    test_monomial_comp_<gb::LexComp>(monomials, expected_comparations[1]);

    std::cout << "re-lex comp:\n";
    test_monomial_comp_<gb::ReLexComp>(monomials, expected_comparations[2]);

    std::cout << "deg-lex comp:\n";
    test_monomial_comp_<gb::DegLexComp>(monomials, expected_comparations[3]);
    print_line();
}
