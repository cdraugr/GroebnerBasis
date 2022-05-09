#include "Tests.hpp"

void test_term() {
    std::cout << "Test Term:\n";
    gb::Term term1({1, 4, 0, 0, 0, 0, 1, 0, 0, 12});  // by std::vector
    asserts::assert_term_(term1, {1, 4, 0, 0, 0, 0, 1, 0, 0, 12});
    gb::Term term2 = gb::Term::term_from_map({{0, 2}, {2, 1}, {6, 1}, {9, 17}});  // by std::map
    asserts::assert_term_(term2, {2, 0, 1, 0, 0, 0, 1, 0, 0, 17});

    std::cout << "t1 = " << term1 << '\n' << "t2 = " << term2 << '\n';
    std::cout << "lcm(t1, t2) = " << lcm(term1, term2) << '\n';
    std::cout << "lcm(t1, t2) = " << gb::Term({2, 4, 1, 0, 0, 0, 1, 0, 0, 17}) << '\n';
    asserts::assert_term_(lcm(term1, term2), {2, 4, 1, 0, 0, 0, 1, 0, 0, 17});

    std::cout << "gcd(t1, t2) = " << gcd(term1, term2) << '\n';
    asserts::assert_term_(gcd(term1, term2), {1, 0, 0, 0, 0, 0, 1, 0, 0, 12});

    std::cout << "deg(t1) = " << deg(term1) << '\n';
    assert(deg(term1) == 18);

    std::cout << "deg(t2) = " << deg(term2) << '\n';
    assert(deg(term2) == 21);

    utils::print_line();

    gb::Term term3 = gb::Term::term_from_map({{2, 5}, {4, 2}});  // = {0, 0, 5, 0, 2}
    gb::Term term4 = gb::Term::term_from_map({{2, 12}, {3, 1}});  // = {0, 0, 12, 1}
    std::cout << "t3 = " << term3 << '\n' << "t4 = " << term4 << "\n\n";
    std::cout << "t3 * t4 =\t" << term3 * term4 << '\n';
    asserts::assert_term_(term3 * term4, {0, 0, 17, 1, 2});

    std::cout << "t3 =\t\t" << term3 << '\n';
    std::cout << "t3 *= t4 =\t" << (term3 *= term4) << '\n';
    std::cout << "t3 =\t\t" << term3 << '\n';
    asserts::assert_term_(term3, {0, 0, 17, 1, 2});

    std::cout << "t3 /= t4 = \t" << (term3 /= term4) << '\n';
    std::cout << "t3 =\t\t" << term3 << '\n';
    asserts::assert_term_(term3, {0, 0, 5, 0, 2});

    utils::print_line();

    gb::Term term5({3, 0, 4});
    gb::Term term6({3, 0, 4});
    std::cout << "t5 = " << term5 << '\n' << "t6 = " << term6 << "\n\n";
    std::cout << std::boolalpha << "t5 == t6\t\tis " << (term5 == term6) << '\n';
    assert(term5 == term6 == true);

    std::cout << "t5 / t6 =\t\t" << term5 / term6 << '\n';
    asserts::assert_term_(term5 / term6, {});

    std::cout << std::boolalpha << "t5 divided by t6\tis " << term5.IsDivisibleBy(term6) << "\n\n";
    assert(term5 == term6 == true);
    utils::print_line();

    gb::Term term7({1, 2, 5});
    gb::Term term8({1, 3, 5});
    std::cout << "t7 = " << term7 << '\n' << "t8 = " << term8 << "\n\n";
    std::cout << "t8 / t7 = " << term8 / term7 << '\n';
    asserts::assert_term_(term8 / term7, {0, 1});

    std::cout << "t7 * t8 / t8 = " << term7 * term8 / term8 << '\n';
    asserts::assert_term_(term7 * term8 / term8, {1, 2, 5});

    std::cout << "t7 / t8 = ";
    try {
        std::cout << term7 / term8;
        assert(false);
    } catch (const std::runtime_error& exception) {
        std::cout << exception.what() << '\n';
    }
    utils::print_line();

    gb::Term term9({0, 2, 3, 0, 2, 0});
    auto divisors = gb::GetAllDivisors(term9);
    assert(divisors.size() == 3 * 4 * 3);
    for (auto it = divisors.begin(); it != divisors.end(); ++it) {
        std::cout << *it << '\n';
        assert(term9.IsDivisibleBy(*it));
        for (auto jt = divisors.begin(); jt != divisors.end(); ++jt) {
            if (it != jt) {
                assert(*it != *jt);
            }
        }
    }
    utils::print_line(2);
}
