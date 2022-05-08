#include "Tests.hpp"

void test_polynomial_set() {
    std::cout << "Test PolynomialSet:\n";
    gb::Polynomial<gb::fields::Rational> f1({  // HW 06, ex 03
        {{{1, 1}}, 2},
        {{{1, 0, 1}}, 4},
        {{{0, 1, 2}}, 1},
    });
    gb::Polynomial<gb::fields::Rational> f2({
        {{{1, 0, 2}}, 4},
        {{{0, 1, 3}}, 1},
        {4},
    });
    gb::Polynomial<gb::fields::Rational> f3({
        {{{0, 2, 3}}, 1},
        {{{0, 1}}, 4},
        {{{0, 0, 1}}, 8},
    });
    gb::PolynomialSet<gb::fields::Rational> F({f1, f2, f3});
    std::cout << "System F = {\n" << F << "\n}\n";
    std::cout << std::boolalpha << "Statement that F is Groebner Basis is " << gb::IsGroebnerBasis(F) << '\n';
    assert(gb::IsGroebnerBasis(F) == true);
    print_line();

    {
        gb::Polynomial<gb::fields::Rational> i1({  // HW 07, ex 01
            {{{2, 1}}, 1},
            {{{1, 0, 1}}, -1},
        });
        gb::Polynomial<gb::fields::Rational> i2({
            {{{0, 2}}, 1},
            {{{0, 1, 1}}, 2},
        });
        gb::PolynomialSet<gb::fields::Rational> I({i1, i2});
        std::cout << "Ideal I = {\n" << I << "\n}\n";
        I.MakeGroebnerBasis();
        std::cout << "Groebner Basis of ideal I = {\n" << I << "\n}\n";
        gb::Polynomial<gb::fields::Rational> g({
            {{{2, 0, 4}}, 5},
            {{{1, 1, 3}}, -1},
        });
        std::cout << std::boolalpha << "Statement that " << g << " belongs ideal I is " << I.IsPolynomialInMyIdeal(g) << '\n';
        assert(I.IsPolynomialInMyIdeal(g) == false);
        print_line();
    }
    {
        gb::Polynomial<gb::fields::Rational> i1({  // Test 01, Variant 01, ex 04
            {{{1, 0, 1}}, 2},
            {{{0, 1}}, -1},
        });
        gb::Polynomial<gb::fields::Rational> i2({
            {{{2}}, 1},
            {{{0, 0, 1}}, 2},
        });
        gb::PolynomialSet<gb::fields::Rational> I({i1, i2});
        std::cout << "Ideal I = {\n" << I << "\n}\n";
        I.MakeGroebnerBasis();
        std::cout << "Groebner Basis of ideal I = {\n" << I << "\n}\n";
        gb::Polynomial<gb::fields::Rational> g({
            {{{1, 0, 4}}, 16},
            {{{0, 3}}, 1},
        });
        std::cout << std::boolalpha << "Statement that " << g << " belongs ideal I is " << I.IsPolynomialInMyIdeal(g) << '\n';
        assert(I.IsPolynomialInMyIdeal(g) == true);
        print_line();
    }
    print_line();
}
