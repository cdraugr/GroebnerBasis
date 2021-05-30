#include "Tests.h"

void test_Monomial() {
    std::cout << "Test Monomial:\n";
    gb::Monomial monom1({1, 4, 0, 0, 0, 0, 1, 0, 0, 12});  // by std::vector
    gb::Monomial monom2({{0, 2}, {2, 1}, {6, 1}, {9, 17}});  // by std::map
    std::cout << "m1 = " << monom1 << '\n' << "m2 = " << monom2 << '\n';
    std::cout << "lcm(m1, m2) = " << lcm(monom1, monom2) << '\n';
    std::cout << "gcd(m1, m2) = " << gcd(monom1, monom2) << '\n';
    std::cout << "deg(m1) = " << deg(monom1) << '\n';
    std::cout << "deg(m2) = " << deg(monom2) << '\n';
    PrintLine();

    gb::Monomial monom3({{2, 5}, {4, 2}});  // = ({0, 0, 5, 0, 2})
    gb::Monomial monom4({{2, 12}, {3, 1}});  // = ({0, 0, 12, 1})
    std::cout << "m3 = " << monom3 << '\n' << "m4 = " << monom4 << "\n\n";
    std::cout << "m3 * m4 =\t" << monom3 * monom4 << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "m3 *= m4 =\t" << (monom3 *= monom4) << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "m3 /= m4 = \t" << (monom3 /= monom4) << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    PrintLine();

    gb::Monomial monom5({3, 0, 4});
    gb::Monomial monom6({3, 0, 4});
    std::cout << "m5 = " << monom5 << '\n' << "m6 = " << monom6 << "\n\n";
    std::cout << std::boolalpha << "m5 == m6\t\tis " << (monom5 == monom6) << '\n';
    std::cout << "m5 / m6 =\t\t" << monom5 / monom6 << '\n';
    std::cout << std::boolalpha << "m5 divided by m6\tis " << monom5.IsDivisibleBy(monom6) << "\n\n";
    PrintLine();

    gb::Monomial monom7({1, 2, 5});
    gb::Monomial monom8({1, 3, 5});
    std::cout << "m7 = " << monom7 << '\n' << "m8 = " << monom8 << "\n\n";
    std::cout << "m8 / m7 = " << monom8 / monom7 << '\n';
    std::cout << "m7 * m8 / m8 = " << monom7 * monom8 / monom8 << '\n';
    std::cout << "m7 / m8 = ";
    try {
        std::cout << monom7 / monom8;
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << '\n';
    }
    PrintLine();

    gb::Monomial monom9({0, 2, 3, 0, 2, 0});
    auto divisors = GetAllDivisors(monom9);
    assert(divisors.size() == 3 * 4 * 3);
    for (auto it = divisors.begin(); it != divisors.end(); ++it) {
        assert(monom9.IsDivisibleBy(*it));
        for (auto jt = divisors.begin(); jt != divisors.end(); ++jt) {
            if (it != jt) {
                assert(*it != *jt);
            }
        }
    }
    for (const auto& monomial : divisors) {
        std::cout << monomial << '\n';
    }
    PrintLine(2);
}
