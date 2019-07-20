#include "../includes/Tests.h"

void test_PolynomialOrder() {
    std::cout << "Test PolynomialOrder:\n";
    gb::PolynomialOrder<gb::LexComp> comparator;
    std::cout << "LexComp\n";
    gb::Polynomial<gb::ReLexComp> f({
        {{1, 1, 1}},
        {{1, 1, 0}},
        {{0, 1, 1}}
    });
    gb::Polynomial<gb::ReLexComp> g({
        {{1, 1, 1}},
        {{1, 1, 0}},
        {{0, 2, 1}}
    });
    gb::Polynomial<gb::ReLexComp> k({
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

    std::set<gb::Polynomial<gb::ReLexComp>, gb::PolynomialOrder<gb::LexComp>> polynoms({f, g, k});
    std::cout << "set:\n";
    for (const auto& polynom : polynoms) {
        std::cout << polynom << '\n';
    }
    PrintLine(2);
}
