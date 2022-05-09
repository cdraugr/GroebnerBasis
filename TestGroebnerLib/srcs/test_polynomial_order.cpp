#include "Tests.hpp"

void test_polynomial_order() {
    std::cout << "Test PolynomialOrder:\n";
    gb::PolynomialOrder<gb::LexComp> comparator;
    std::cout << "ReLexComp\n";
    gb::Polynomial<gb::fields::Rational, gb::LexComp> f({
        {{{1, 1, 1}}, 1},
        {{{1, 1}}, 1},
        {{{0, 1, 1}}, 1},
    });
    gb::Polynomial<gb::fields::Rational, gb::LexComp> g({
        {{{1, 1, 1}}, 1},
        {{{1, 1}}, 1},
        {{{0, 2, 1}}, 1},
    });
    gb::Polynomial<gb::fields::Rational, gb::LexComp> k({
        {{{2, 1, 1}}, 1},
        {{{1, 1}}, 1},
    });

    std::cout << "f = " << f << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "k = " << k << "\n\n";
    std::cout << std::boolalpha << "f < g is " << comparator(f, g) << '\n';
    assert(comparator(f, g) == true);
    std::cout << std::boolalpha << "g < f is " << comparator(g, f) << "\n\n";
    assert(comparator(g, f) == false);

    std::cout << std::boolalpha << "k < g is " << comparator(k, g) << '\n';
    assert(comparator(k, g) == false);
    std::cout << std::boolalpha << "g < k is " << comparator(g, k) << "\n\n";
    assert(comparator(g, k) == true);

    std::cout << std::boolalpha << "k < f is " << comparator(k, f) << '\n';
    assert(comparator(k, f) == false);
    std::cout << std::boolalpha << "f < k is " << comparator(f, k) << "\n\n";
    assert(comparator(f, k) == true);

    std::cout << std::boolalpha << "f < f is " << comparator(f, f) << '\n';
    assert(comparator(f, f) == false);

    std::cout << std::boolalpha << "g < g is " << comparator(g, g) << '\n';
    assert(comparator(g, g) == false);

    std::cout << std::boolalpha << "k < k is " << comparator(k, k) << '\n';
    assert(comparator(k, k) == false);

    utils::print_line();

    std::set<gb::Polynomial<gb::fields::Rational, gb::LexComp>, gb::PolynomialOrder<gb::LexComp>> polynomials({f, g, k});
    std::cout << "set:\n";
    for (const auto& polynomial : polynomials) {
        std::cout << polynomial << '\n';
    }
    utils::print_line(2);
}
