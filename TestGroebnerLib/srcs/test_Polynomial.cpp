#include "../includes/Tests.h"

void test_Polynomial() {
    std::cout << "Test Polynomial:\n";
    gb::Polynomial<Rational> f({
        gb::Term<Rational>(gb::Monomial({7, 0, 4}), 2),
        gb::Term<Rational>(-5),
    });
    gb::Polynomial<Rational> g({
        gb::Term<Rational>(gb::Monomial({2, 2, 0}), 1),
        gb::Term<Rational>(gb::Monomial({3, 0, 4}), 3),
    });
    gb::Polynomial<Rational> k;

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
    std::cout << "S(f, g) = " << gb::SPolynomial(f, g) << '\n';
    std::cout << "S(g, f) = " << gb::SPolynomial(g, f) << '\n';
    std::cout << "S(f, f) = " << gb::SPolynomial(f, f) << '\n';
    PrintLine();
    f.TryReduceOnceBy(g);
    std::cout << "f -> (g) = " << f << '\n';
    f.TryReduceOnceBy(f);
    std::cout << "f -> (f) = " << f << '\n';
    PrintLine();
    {  // HW 06, ex 02
        gb::Polynomial<Rational> poly_g({
            gb::Term<Rational>(gb::Monomial({0, 4, 6}), 1),
            gb::Term<Rational>(gb::Monomial({1, 4, 1}), 2),
            gb::Term<Rational>(gb::Monomial({2, 2, 0}), 1)
        });
        gb::Polynomial<Rational> poly_f({
            gb::Term<Rational>(gb::Monomial({0, 4, 1}), 1),
            gb::Term<Rational>(gb::Monomial({1, 1, 2}), -1),
            gb::Term<Rational>(gb::Monomial({1, 2, 0}), 1),
        });
        std::cout << "f = " << poly_f << '\n';
        std::cout << "g = " << poly_g << "\n\n";
        std::cout << "Reductions g fo res by f:\n";
        while (poly_g.TryReduceOnceBy(poly_f)) {
            std::cout << poly_g << '\n';
        }
    }
    PrintLine(2);
}