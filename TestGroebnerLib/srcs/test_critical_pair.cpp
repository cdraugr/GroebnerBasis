#include "Tests.hpp"

void test_critical_pair() {
    gb::Polynomial<gb::fields::Rational> f({
        {{{2, 1}}, 1},
        {1},
    });
    gb::Polynomial<gb::fields::Rational> g({
        {{{1, 0, 2}}, 1},
        {{{0, 1}}, 1},
    });
    std::cout << "Polynomial f = " << f << '\n';
    std::cout << "Polynomial g = " << g << "\n\n";

    const gb::CriticalPair critical_pair(f, g);
    std::cout << "Pair(f, g) = {\n";
    std::cout << "    lcm = " << critical_pair.GetLcm() << '\n';
    assert_term_(critical_pair.GetLcm(), {2, 1, 2});

    std::cout << "    t_1 = " << critical_pair.GetLeftTerm() << '\n';
    assert_term_(critical_pair.GetLeftTerm(), {0, 0, 2});

    std::cout << "    p_1 = " << critical_pair.GetLeftPolynomial() << '\n';
    assert(critical_pair.GetLeftPolynomial() == f);

    std::cout << "    t_2 = " << critical_pair.GetRightTerm() << '\n';
    assert_term_(critical_pair.GetRightTerm(), {1, 1});

    std::cout << "    p_2 = " << critical_pair.GetRightPolynomial() << '\n';
    assert(critical_pair.GetRightPolynomial() == g);
    std::cout << "}\n";

    std::cout << "\nTotal degree: deg(Pair(f, g)) = " << critical_pair.GetDegree() << '\n';
    assert(critical_pair.GetDegree() == 5);
    print_line();

    gb::Polynomial<gb::fields::Rational> left1({
        {{{0, 0, 3}}, 1},
        {{{0, 0, 2, 1}}, 1},
        {{{0, 0, 1, 2}}, 1},
        {{{0, 0, 0, 3}}, 1},
    });
    gb::Polynomial<gb::fields::Rational> right1({
        {{{1, 1, 1, 1}}, 1},
        {1},
    });
    gb::Polynomial<gb::fields::Rational> left2({
        {{{0, 0, 0, 4}}, 1},
        {-1},
    });
    gb::Polynomial<gb::fields::Rational> right2({
        {{{1, 1, 1, 1}}, 1},
        {1},
    });
    const gb::CriticalPair cp1(left1, right1), cp2(left2, right2);

    std::cout << cp1 << '\n' << cp2 << '\n';
}
