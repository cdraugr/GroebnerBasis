#include "../includes/Tests.h"

void test_Polynomial() {
    std::cout << "Test Polynomial:\n";
    gb::Polynomial<gb::ReLexComp> f({{{7, 0, 4}, 2}, {-5}});
    gb::Polynomial<gb::ReLexComp> g({
        {{2, 2, 0}},
        {{3, 0, 4}, 3},
    });
    gb::Polynomial<gb::ReLexComp> k;

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
    std::cout << "S(f, k) = " << gb::SPolynomial(f, k) << '\n';
    std::cout << "S(k, f) = " << gb::SPolynomial(k, f) << '\n';
    std::cout << "S(k, k) = " << gb::SPolynomial(k, k) << '\n';
    PrintLine();
    f.ReductionBy(g);
    std::cout << "f -> (g) = " << f << '\n';
    f.ReductionBy(f);
    std::cout << "f -> (f) = " << f << '\n';
    PrintLine();
    {  // HW 06, ex 02
        gb::Polynomial<gb::ReLexComp> poly_g({
            {{0, 4, 6}},
            {{1, 4, 1}, {2}},
            {{2, 2, 0}}
        });
        gb::Polynomial<gb::ReLexComp> poly_f({
            {{0, 4, 1}},
            {{1, 1, 2}, {-1}},
            {{1, 2, 0}}
        });
        std::cout << "f = " << poly_f << '\n';
        std::cout << "g = " << poly_g << "\n\n";
        std::cout << "Reductions g fo res by f:\n";
        while (poly_g.ReductionBy(poly_f)) {
            std::cout << poly_g << '\n';
        }
    }
    PrintLine(2);
}