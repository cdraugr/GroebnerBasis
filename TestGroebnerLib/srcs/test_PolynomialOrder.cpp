#include "../includes/Tests.h"

void test_PolynomialOrder() {
    std::cout << "Test PolynomialOrder:\n";
    gb::PolynomialOrder<gb::LexComp> comparator;
    std::cout << "ReLexComp\n";
    gb::Polynomial<Rational, gb::LexComp> f({
        gb::Term<Rational>(gb::Monomial({1, 1, 1}), 1),
        gb::Term<Rational>(gb::Monomial({1, 1, 0}), 1),
        gb::Term<Rational>(gb::Monomial({0, 1, 1}), 1)
    });
    gb::Polynomial<Rational, gb::LexComp> g({
        gb::Term<Rational>(gb::Monomial({1, 1, 1}), 1),
        gb::Term<Rational>(gb::Monomial({1, 1, 0}), 1),
        gb::Term<Rational>(gb::Monomial({0, 2, 1}), 1)
    });
    gb::Polynomial<Rational, gb::LexComp> k({
        gb::Term<Rational>(gb::Monomial({2, 1, 1}), 1),
        gb::Term<Rational>(gb::Monomial({1, 1, 0}), 1)
    });

    std::cout << "f = " << f << '\n';
    std::cout << "g = " << g << '\n';
    std::cout << "k = " << k << "\n\n";
    std::cout << std::boolalpha << "f < g is " << comparator(f, g) << '\n';
    std::cout << std::boolalpha << "g < f is " << comparator(g, f) << "\n\n";

    std::cout << std::boolalpha << "k < g is " << comparator(k, g) << '\n';
    std::cout << std::boolalpha << "g < k is " << comparator(g, k) << "\n\n";

    std::cout << std::boolalpha << "k < f is " << comparator(k, f) << '\n';
    std::cout << std::boolalpha << "f < k is " << comparator(f, k) << "\n\n";

    std::cout << std::boolalpha << "f < f is " << comparator(f, f) << '\n';
    std::cout << std::boolalpha << "g < g is " << comparator(g, g) << '\n';
    std::cout << std::boolalpha << "k < k is " << comparator(k, k) << '\n';
    PrintLine();

    std::set<gb::Polynomial<Rational, gb::LexComp>, gb::PolynomialOrder<gb::LexComp>> polynoms({f, g, k});
    std::cout << "set:\n";
    for (const auto& polynom : polynoms) {
        std::cout << polynom << '\n';
    }
    PrintLine(2);
}
