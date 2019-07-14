#include <set>
#include <string>
#include "../includes/Tests.h"

void PrintLine() {
    for (size_t i = 0; i != 50; ++i) {
        std::cout << '-';
    }
    std::cout << '\n';
}

void test_Monomials() {
    std::cout << "Test Monomials:\n";
    bg::Monomial monom1({1, 4, 0, 0, 0, 0, 1, 0, 0, 12}, 15);
    bg::Monomial monom2({{0, 2}, {2, 1}, {6, 1}, {9, 17}}, 7);
    std::cout << "m1 = " << monom1 << '\n' << "m2 = " << monom2 << '\n';

    std::cout << "lcm(m1, m2) = " << lcm(monom1, monom2) << '\n';
    std::cout << "gcd(m1, m2) = " << (monom1, monom2) << '\n';
    std::cout << "deg(m1) = " << deg(monom1) << '\n';
    std::cout << "deg(m2) = " << deg(monom2) << '\n';
    PrintLine();

    bg::Monomial monom3({{2, 5}, {4, 2}}, {2, 3});
    bg::Monomial monom4({{2, 12}, {3, 1}}, -1);
    std::cout << "m3 = " << monom3 << '\n' << "m4 = " << monom4 << "\n\n";
    std::cout << "m3 * m4 =\t" << monom3 * monom4 << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "m3 *= m4 =\t" << (monom3 *= monom4) << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    PrintLine();

    bg::Monomial monom5({3, 0, 4}, 2);
    bg::Monomial monom6({3, 0, 4}, 1);
    std::cout << (monom5 == monom6) << '\t'
            << (monom5 == 2 * monom6) << '\t'
            << (3 * monom5 == monom6 * 6) << '\n';
    PrintLine();

    std::cout << "(-1) * " << monom5 << " = " << -monom5 << '\n';
    std::cout << "(1) * " << monom6 << " = " << +monom6 << '\n';

    monom5.coefficient() += 10;
    std::cout << monom5 << '\n';
    PrintLine();
}

std::string TrueFalse(bool value) {
    return value ? "true" : "false";
}

template <typename Comp>
void test_comp(const std::vector<bg::Monomial>& monoms) {
    Comp comparator;
    for (size_t i = 0; i != monoms.size(); ++i) {
        for (size_t j = 0; j != monoms.size(); ++j) {
            if (i != j) {
                std::cout << 'm' << i + 1 << " < m" << j + 1 << " is "
                        << TrueFalse(comparator(monoms[i], monoms[j])) << '\n';
            }
        }
    }

    std::set<bg::Monomial, Comp> mon_set(monoms.begin(), monoms.end());
    std::cout << "\nset:\n";
    for (const auto& monom : mon_set) {
        std::cout << monom << '\n';
    }
    PrintLine();
}

void test_MonomialOrder() {
    std::cout << "Test MonomialOrder:\n";
    std::vector<bg::Monomial> monoms({
        {std::vector<i32>({1, 2, 31}), 0},  // 0
        {std::vector<i32>({2, 3, 7, 3, 7})},
        {std::vector<i32>({4, 1, 7, 10, 0})},
        {std::vector<i32>({2, 3, 7, 0, 11})}
    });

    for (size_t i = 0; i != monoms.size(); ++i) {
        std::cout << 'm' << i + 1 << " = " << monoms[i] << '\n';
    }
    PrintLine();

    std::cout << "deg comp:\n";
    test_comp<bg::DegComp>(monoms);

    std::cout << "lex comp:\n";
    test_comp<bg::LexComp>(monoms);

    std::cout << "re_lex comp:\n";
    test_comp<bg::ReLexComp>(monoms);

    std::cout << "deg-lex comp:\n";
    test_comp<bg::DegLexComp>(monoms);
}

void test_Polynomial() {
    std::cout << "Test Polynomial:\n";
    bg::Polynomial<bg::ReLexComp> f({{{7, 0, 4}, 2}, {-5}});
    bg::Polynomial<bg::ReLexComp> g({
        {{2, 2, 0}},
        {{3, 0, 4}, 3},
    });
    bg::Polynomial<bg::ReLexComp> k;

    std::cout << "f = " << f << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "k = " << k << '\n';
    PrintLine();
    std::cout << "g + f =\t\t" << (g + f) << '\n';
    std::cout << "g - f =\t\t" << (g - f) << '\n';
    std::cout << "g += f =\t" << (g += f) << '\n';
    std::cout << "g =\t\t" << g << '\n';
    std::cout << "g -= f =\t" << (g -= f) << '\n';
    std::cout << "g =\t\t" << g << '\n';
    PrintLine();
    std::cout << '(' << g << ") * (" << f << ") =\n" << (g * f) << '\n';
    PrintLine();    
    std::cout << "S(f, g) = " << bg::SPolynomial(f, g) << '\n';
    std::cout << "S(g, f) = " << bg::SPolynomial(g, f) << '\n';
    std::cout << "S(f, f) = " << bg::SPolynomial(f, f) << '\n';
    std::cout << "S(f, k) = " << bg::SPolynomial(f, k) << '\n';
    std::cout << "S(k, f) = " << bg::SPolynomial(k, f) << '\n';
    std::cout << "S(k, k) = " << bg::SPolynomial(k, k) << '\n';
    PrintLine();
    f.ReductionBy(g);
    std::cout << "f -> (g) = " << f << '\n';
    f.ReductionBy(f);
    std::cout << "f -> (f) = " << f << '\n';
    PrintLine();
    {  // HW 06, ex 02
        bg::Polynomial<bg::ReLexComp> poly_g({
            {{0, 4, 6}},
            {{1, 4, 1}, {2}},
            {{2, 2, 0}}
        });
        bg::Polynomial<bg::ReLexComp> poly_f({
            {{0, 4, 1}},
            {{1, 1, 2}, {-1}},
            {{1, 2, 0}}
        });
        std::cout << "f = " << poly_f << '\n';
        std::cout << "g = " << poly_g << "\n\n";
        while (poly_g.ReductionBy(poly_f)) {
            std::cout << poly_g << '\n';
        }
    }
    PrintLine();
}

void test_PolynomialOrder() {
    std::cout << "Test PolynomialOrder:\n";
    bg::PolynomialOrder<bg::LexComp> comparator;
    std::cout << "LexComp\n";
    bg::Polynomial<bg::ReLexComp> f({
        {{1, 1, 1}},
        {{1, 1, 0}},
        {{0, 1, 1}}
    });
    bg::Polynomial<bg::ReLexComp> g({
        {{1, 1, 1}},
        {{1, 1, 0}},
        {{0, 2, 1}}
    });
    bg::Polynomial<bg::ReLexComp> k({
        {{2, 1, 1}},
        {{1, 1, 0}},
    });

    std::cout << "f = " << f << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "k = " << k << "\n\n";
    std::cout << "f < g is " << TrueFalse(comparator(f, g)) << '\n';
    std::cout << "g < f is " << TrueFalse(comparator(g, f)) << "\n\n";

    std::cout << "k < g is " << TrueFalse(comparator(k, g)) << '\n';
    std::cout << "g < k is " << TrueFalse(comparator(g, k)) << "\n\n";

    std::cout << "k < f is " << TrueFalse(comparator(k, f)) << '\n';
    std::cout << "f < k is " << TrueFalse(comparator(f, k)) << "\n\n";

    std::cout << "f < f is " << TrueFalse(comparator(f, f)) << '\n';
    std::cout << "g < g is " << TrueFalse(comparator(g, g)) << '\n';
    std::cout << "k < k is " << TrueFalse(comparator(k, k)) << '\n';
    PrintLine();

    std::set<bg::Polynomial<bg::ReLexComp>, bg::PolynomialOrder<bg::LexComp>> polynoms({f, g, k});
    std::cout << "set:\n";
    for (const auto& polynom : polynoms) {
        std::cout << polynom << '\n';
    }
    PrintLine();
}

void test_PolynomialSet() {
    std::cout << "Test PolynomialSet:\n";
    bg::Polynomial<bg::ReLexComp> f1({  // HW 06, ex 03
        {{1, 1, 0}, 2},
        {{1, 0, 1}, 4},
        {{0, 1, 2}, 1}
    });
    bg::Polynomial<bg::ReLexComp> f2({
        {{1, 0, 2}, 4},
        {{0, 1, 3}, 1},
        {{0, 0, 0}, 4}
    });
    bg::Polynomial<bg::ReLexComp> f3({
        {{0, 2, 3}, 1},
        {{0, 1, 0}, 4},
        {{0, 0, 1}, 8}
    });
    bg::PolynomialSet<bg::ReLexComp> F({f1, f2, f3});
    std::cout << "System F = {\n" << F << "\n}\n";
    std::cout << "Statement that F is Groebner Basis is " << TrueFalse(bg::IsGroebnerBasis(F)) << '\n';

    PrintLine();
    bg::Polynomial<bg::ReLexComp> i1({  // HW 07, ex 01
        {{2, 1, 0}, 1},
        {{1, 0, 1}, -1}
    });
    bg::Polynomial<bg::ReLexComp> i2({
        {{0, 2, 0}, 1},
        {{0, 1, 1}, 2}
    });
    bg::PolynomialSet<bg::ReLexComp> I({i1, i2});
    std::cout << "Ideal I = {\n" << I << "\n}\n";
    I.MakeGroebnerBasis();
    std::cout << "Groebner Basis of ideal I = {\n" << I << "\n}\n";
    bg::Polynomial<bg::ReLexComp> polynom({
        {{2, 0, 4}, 5},
        {{1, 1, 3}, -1}
    });
    std::cout << "Statement that " << polynom << " belongs ideal I is " << TrueFalse(I.IsPolynomialInMe(polynom)) << '\n';
    PrintLine();
    bg::Polynomial<bg::ReLexComp> polynom_i1({  // Test 01, Variant 01, ex 04
        {{1, 0, 1}, 2},
        {{0, 1, 0}, -1}
    });
    bg::Polynomial<bg::ReLexComp> polynom_i2({
        {{2, 0, 0}, 1},
        {{0, 0, 1}, 2}
    });
    bg::PolynomialSet<bg::ReLexComp> ideal_I({polynom_i1, polynom_i2});
    std::cout << "Ideal I = {\n" << ideal_I << "\n}\n";
    ideal_I.MakeGroebnerBasis();
    std::cout << "Groebner Basis of ideal I = {\n" << ideal_I << "\n}\n";
    bg::Polynomial<bg::ReLexComp> polynom_f({
        {{1, 0, 4}, 16},
        {{0, 3, 0}, 1}
    });
    std::cout << "Statement that " << polynom_f << " belongs ideal I is " << TrueFalse(ideal_I.IsPolynomialInMe(polynom_f)) << '\n';
    PrintLine();
}
