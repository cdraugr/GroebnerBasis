#include "Tests.hpp"

void test_polynomial() {
    std::cout << "Test Polynomial:\n";
    gb::Polynomial<gb::fields::Rational> f({
        {{{7, 0, 4}}, 2},
        {-5},
    });
    gb::Polynomial<gb::fields::Rational> g({
        {{{2, 2}}, 1},
        {{{3, 0, 4}}, 3},
    });
    gb::Polynomial<gb::fields::Rational> k;

    std::cout << "f = " << f << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "k = " << k << '\n';
    print_line();

    std::cout << "g + f =\t\t" << (g + f) << '\n';
    std::cout << "g - f =\t\t" << (g - f) << '\n';
    std::cout << "g += f =\t" << (g += f) << '\n';
    std::cout << "g =\t\t" << g << '\n';
    std::cout << "g -= f =\t" << (g -= f) << '\n';
    std::cout << "g =\t\t" << g << '\n';
    print_line();

    std::cout << '(' << g << ") * (" << f << ") =\n" << (g * f) << '\n';
    print_line();

    std::cout << "S(f, g) = " << gb::SPolynomial(f, g) << '\n';
    std::cout << "S(g, f) = " << gb::SPolynomial(g, f) << '\n';
    std::cout << "S(f, f) = " << gb::SPolynomial(f, f) << '\n';
    print_line();

    f.TryReduceOnceBy(g);
    std::cout << "f -> (g) = " << f << '\n';
    f.TryReduceOnceBy(f);
    std::cout << "f -> (f) = " << f << '\n';
    print_line();

    {  // HW 06, ex 02
        gb::Polynomial<gb::fields::Rational> f({
            {{{0, 4, 1}}, 1},   //               x_2^4 * x_3
            {{{1, 1, 2}}, -1},  // -     x_1   * x_2   * x_3^2
            {{{1, 2}}, 1},      // +     x_1   * x_2^2
        });
        gb::Polynomial<gb::fields::Rational> g({
            {{{0, 4, 6}}, 1},  //               x_2^4 * x_3^6
            {{{1, 4, 1}}, 2},  // + 2 * x_1   * x_2^4 * x_3
            {{{2, 2}}, 1},     // +     x_1^2 * x_2^2
        });
        std::cout << "f = " << f << '\n';
        std::cout << "g = " << g << "\n\n";
        std::cout << "Reductions g to res by f:\n";
        while (g.TryReduceOnceBy(f)) {
            std::cout << g << '\n';
        }
    }
    print_line(2);
}
