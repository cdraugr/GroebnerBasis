#include "../includes/Tests.h"

void test_PolynomialSet() {
    std::cout << "Test PolynomialSet:\n";
    gb::Polynomial<gb::ReLexComp> f1({  // HW 06, ex 03
        {{1, 1, 0}, 2},
        {{1, 0, 1}, 4},
        {{0, 1, 2}, 1}
    });
    gb::Polynomial<gb::ReLexComp> f2({
        {{1, 0, 2}, 4},
        {{0, 1, 3}, 1},
        {{0, 0, 0}, 4}
    });
    gb::Polynomial<gb::ReLexComp> f3({
        {{0, 2, 3}, 1},
        {{0, 1, 0}, 4},
        {{0, 0, 1}, 8}
    });
    gb::PolynomialSet<gb::ReLexComp> F({f1, f2, f3});
    std::cout << "System F = {\n" << F << "\n}\n";
    std::cout << "Statement that F is Groebner Basis is " << TrueFalse(gb::IsGroebnerBasis(F)) << '\n';

    PrintLine();
    gb::Polynomial<gb::ReLexComp> i1({  // HW 07, ex 01
        {{2, 1, 0}, 1},
        {{1, 0, 1}, -1}
    });
    gb::Polynomial<gb::ReLexComp> i2({
        {{0, 2, 0}, 1},
        {{0, 1, 1}, 2}
    });
    gb::PolynomialSet<gb::ReLexComp> I({i1, i2});
    std::cout << "Ideal I = {\n" << I << "\n}\n";
    I.MakeGroebnerBasis();
    std::cout << "Groebner Basis of ideal I = {\n" << I << "\n}\n";
    gb::Polynomial<gb::ReLexComp> polynom({
        {{2, 0, 4}, 5},
        {{1, 1, 3}, -1}
    });
    std::cout << "Statement that " << polynom << " belongs ideal I is " << TrueFalse(I.IsPolynomialInMe(polynom)) << '\n';
    PrintLine();
    gb::Polynomial<gb::ReLexComp> polynom_i1({  // Test 01, Variant 01, ex 04
        {{1, 0, 1}, 2},
        {{0, 1, 0}, -1}
    });
    gb::Polynomial<gb::ReLexComp> polynom_i2({
        {{2, 0, 0}, 1},
        {{0, 0, 1}, 2}
    });
    gb::PolynomialSet<gb::ReLexComp> ideal_I({polynom_i1, polynom_i2});
    std::cout << "Ideal I = {\n" << ideal_I << "\n}\n";
    ideal_I.MakeGroebnerBasis();
    std::cout << "Groebner Basis of ideal I = {\n" << ideal_I << "\n}\n";
    gb::Polynomial<gb::ReLexComp> polynom_f({
        {{1, 0, 4}, 16},
        {{0, 3, 0}, 1}
    });
    std::cout << "Statement that " << polynom_f << " belongs ideal I is " << TrueFalse(ideal_I.IsPolynomialInMe(polynom_f)) << '\n';
    PrintLine(2);
}
