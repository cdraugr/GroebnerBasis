#include "Tests.h"

void test_CriticalPair() {
    gb::Polynomial<Rational> f({
        gb::Term<Rational>(gb::Monomial({2, 1, 0}), 1),
        gb::Term<Rational>(1)
    });
    gb::Polynomial<Rational> g({
        gb::Term<Rational>(gb::Monomial({1, 0, 2}), 1),
        gb::Term<Rational>(gb::Monomial({0, 1, 0}), 1)
    });
    std::cout << "Polynomial f = " << f << '\n';
    std::cout << "Polynomial g = " << g << "\n\n";

    const gb::CriticalPair cPair(f, g);
    std::cout << "Pair(f, g) = {\n";
    std::cout << "    lcm = " << cPair.Getlcm() << '\n';
    std::cout << "    m_1 = " << cPair.leftMonomial() << '\n';
    std::cout << "    p_1 = " << cPair.leftPolynomial() << '\n';
    std::cout << "    m_2 = " << cPair.rightMonomial() << '\n';
    std::cout << "    p_2 = " << cPair.rightPolynomial() << '\n';
    std::cout << "}\n";

    std::cout << "\nTotal degree: deg(Pair(f, g)) = " << cPair.GetDegree() << '\n';

    gb::Polynomial<Rational> left1({
        gb::Term<Rational>(gb::Monomial({0, 0, 3, 0}), 1),
        gb::Term<Rational>(gb::Monomial({0, 0, 2, 1}), 1),
        gb::Term<Rational>(gb::Monomial({0, 0, 1, 2}), 1),
        gb::Term<Rational>(gb::Monomial({0, 0, 0, 3}), 1)
    });
    gb::Polynomial<Rational> right1({
        gb::Term<Rational>(gb::Monomial({1, 1, 1, 1}), 1),
        gb::Term<Rational>(1)
    });
    gb::Polynomial<Rational> left2({
        gb::Term<Rational>(gb::Monomial({0, 0, 0, 4}), 1),
        gb::Term<Rational>(-1)
    });
    gb::Polynomial<Rational> right2({
        gb::Term<Rational>(gb::Monomial({1, 1, 1, 1}), 1),
        gb::Term<Rational>(1)
    });
    const gb::CriticalPair cp1(left1, right1), cp2(left2, right2);

    std::cout << cp1 << '\n' << cp2 << '\n';
}
