#include "Tests.hpp"

void assert_rational_monomial_(
    const gb::Monomial<gb::fields::Rational>& monomial,
    const std::vector<i64>& degrees,
    const i64& numerator,
    const i64& denominator
) {
    assert_term_(monomial.GetTerm(), degrees);
    assert_rational_(monomial.GetCoefficient(), numerator, denominator);
}


void test_monomial() {
    std::cout << "Test Monomial:\n";
    std::vector<gb::Monomial<gb::fields::Modular<7>>> vec;
    for (i64 i = -1; i != 9; ++i) {
        vec.push_back({{{1, 0, 0, 3}}, i});
    }
    for (const auto& monomial : vec) {
        std::cout << monomial << '\n';
    }
    print_line();

    gb::Monomial<gb::fields::Rational> monomial1({{1, 2, 3}}, 2);
    gb::Monomial<gb::fields::Rational> monomial2({{3, 2, 1}}, -1);

    std::cout << "m1 = " << monomial1 << '\n';
    assert_rational_monomial_(monomial1, {1, 2, 3}, 2, 1);

    std::cout << "m2 = " << monomial2 << '\n';
    assert_rational_monomial_(monomial2, {3, 2, 1}, -1, 1);

    std::cout << "m1 * 2 = " << monomial1 * 2 << '\n';
    assert_rational_monomial_(monomial1 * 2, {1, 2, 3}, 4, 1);

    std::cout << "2 * m2 = " << 2 * monomial2 << '\n';
    assert_rational_monomial_(2 * monomial2, {3, 2, 1}, -2, 1);

    std::cout << "gcd(m1, m2) = " << gcd(monomial1, monomial2) << '\n';
    assert_rational_monomial_(gcd(monomial1, monomial2), {1, 2, 1}, 1, 1);

    std::cout << "lcm(m1, m2) = " << lcm(monomial1, monomial2) << '\n';
    assert_rational_monomial_(lcm(monomial1, monomial2), {3, 2, 3}, -2, 1);
    print_line();

    gb::Monomial<gb::fields::Rational> monomial3(2);
    gb::Monomial<gb::fields::Rational> monomial4({3, 5});
    std::cout << "m3 = " << monomial3 << '\n';
    std::cout << "m4 = " << monomial4 << '\n';
    std::cout << std::boolalpha << "m3 == 2 is " << (monomial3 == 2) << '\n';
    assert(monomial3 == 2 == true);

    std::cout << std::boolalpha << "2 == m4 is " << (2 == monomial4) << '\n';
    assert(2 == monomial4 == false);

    std::cout << "m4 * 25 = " << monomial4 * 25 << '\n';
    assert(monomial4 * 25 == 15);

    print_line(2);
}
