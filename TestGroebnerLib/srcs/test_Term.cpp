#include "Tests.h"

void test_Term() {
    std::cout << "Test Term:\n";
    std::vector<gb::Term<Modular<7>>> vec;
    for (i64 i = -1; i != 9; ++i) {
        vec.push_back({gb::Monomial({1, 0, 0, 3}), i});
    }
    for (const auto& term : vec) {
        std::cout << term << '\n';
    }
    PrintLine();

    gb::Term<Modular<5>> term1(gb::Monomial({1, 2, 3}), 2);
    gb::Term<Modular<5>> term2(gb::Monomial({3, 2, 1}), -1);

    std::cout << "t1 = " << term1 << '\n';
    std::cout << "t2 = " << term2 << '\n';
    std::cout << "t1 * 2 = " << term1 * 2 << '\n';
    std::cout << "2 * t2 = " << 2 * term2 << '\n';
    std::cout << "gcd(t1, t2) = " << gcd(term1, term2) << '\n';
    std::cout << "lcm(t1, t2) = " << lcm(term1, term2) << '\n';
    PrintLine();

    gb::Term<Rational> term3(2);
    gb::Term<Rational> term4({3, 5});
    std::cout << "t3 = " << term3 << '\n';
    std::cout << "t4 = " << term4 << '\n';
    std::cout << std::boolalpha << "t3 == 2 is " << (term3 == 2) << '\n';
    std::cout << std::boolalpha << "2 == t4 is " << (2 == term4) << '\n';
    std::cout << "t4 * 25 = " << term4 * 25 << '\n';
    PrintLine(2);
}
