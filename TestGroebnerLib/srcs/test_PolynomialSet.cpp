#include "Tests.h"

void test_PolynomialSet() {
    std::cout << "Test PolynomialSet:\n";
    gb::Polynomial<Rational> f1({  // HW 06, ex 03
        gb::Term<Rational>(gb::Monomial({1, 1, 0}), 2),
        gb::Term<Rational>(gb::Monomial({1, 0, 1}), 4),
        gb::Term<Rational>(gb::Monomial({0, 1, 2}), 1),
    });
    gb::Polynomial<Rational> f2({
        gb::Term<Rational>(gb::Monomial({1, 0, 2}), 4),
        gb::Term<Rational>(gb::Monomial({0, 1, 3}), 1),
        gb::Term<Rational>(gb::Monomial({0, 0, 0}), 4),
    });
    gb::Polynomial<Rational> f3({
        gb::Term<Rational>(gb::Monomial({0, 2, 3}), 1),
        gb::Term<Rational>(gb::Monomial({0, 1, 0}), 4),
        gb::Term<Rational>(gb::Monomial({0, 0, 1}), 8),
    });
    gb::PolynomialSet<Rational> F({f1, f2, f3});
    std::cout << "System F = {\n" << F << "\n}\n";
    std::cout << std::boolalpha << "Statement that F is Groebner Basis is " << gb::IsGroebnerBasis(F) << '\n';
    PrintLine();

    gb::Polynomial<Rational> i1({  // HW 07, ex 01
        gb::Term<Rational>(gb::Monomial({2, 1, 0}), 1),
        gb::Term<Rational>(gb::Monomial({1, 0, 1}), -1),
    });
    gb::Polynomial<Rational> i2({
        gb::Term<Rational>(gb::Monomial({0, 2, 0}), 1),
        gb::Term<Rational>(gb::Monomial({0, 1, 1}), 2),
    });
    gb::PolynomialSet<Rational> I({i1, i2});
    std::cout << "Ideal I = {\n" << I << "\n}\n";
    I.MakeGroebnerBasis();
    std::cout << "Groebner Basis of ideal I = {\n" << I << "\n}\n";
    gb::Polynomial<Rational> polynom({
        gb::Term<Rational>(gb::Monomial({2, 0, 4}), 5),
        gb::Term<Rational>(gb::Monomial({1, 1, 3}), -1),
    });
    std::cout << std::boolalpha << "Statement that " << polynom << " belongs ideal I is " << I.IsPolynomialInMyIdeal(polynom) << '\n';
    PrintLine();

    gb::Polynomial<Rational> polynom_i1({  // Test 01, Variant 01, ex 04
        gb::Term<Rational>(gb::Monomial({1, 0, 1}), 2),
        gb::Term<Rational>(gb::Monomial({0, 1, 0}), -1),
    });
    gb::Polynomial<Rational> polynom_i2({
        gb::Term<Rational>(gb::Monomial({2, 0, 0}), 1),
        gb::Term<Rational>(gb::Monomial({0, 0, 1}), 2),
    });
    gb::PolynomialSet<Rational> ideal_I({polynom_i1, polynom_i2});
    std::cout << "Ideal I = {\n" << ideal_I << "\n}\n";
    ideal_I.MakeGroebnerBasis();
    std::cout << "Groebner Basis of ideal I = {\n" << ideal_I << "\n}\n";
    gb::Polynomial<Rational> polynom_f({
        gb::Term<Rational>(gb::Monomial({1, 0, 4}), 16),
        gb::Term<Rational>(gb::Monomial({0, 3, 0}), 1),
    });
    std::cout << std::boolalpha << "Statement that " << polynom_f << " belongs ideal I is " << ideal_I.IsPolynomialInMyIdeal(polynom_f) << '\n';
    PrintLine(2);
}
