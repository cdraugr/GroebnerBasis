#include "../includes/Tests.h"

void test_Monomial() {
    std::cout << "Test Monomial:\n";
    gb::Monomial monom1({1, 4, 0, 0, 0, 0, 1, 0, 0, 12}, 14);  // by std::vector
    gb::Monomial monom2({{0, 2}, {2, 1}, {6, 1}, {9, 17}}, 7);  // by std::map
    std::cout << "m1 = " << monom1 << '\n' << "m2 = " << monom2 << '\n';

    std::cout << "lcm(m1, m2) = " << lcm(monom1, monom2) << '\n';
    std::cout << "gcd(m1, m2) = " << (monom1, monom2) << '\n';
    std::cout << "deg(m1) = " << deg(monom1) << '\n';
    std::cout << "deg(m2) = " << deg(monom2) << '\n';
    PrintLine();

    gb::Monomial monom3({{2, 5}, {4, 2}}, {2, 3});  // = ({0, 0, 5, 0, 2}, {2, 3})
    gb::Monomial monom4({{2, 12}, {3, 1}}, {-8, 5});  // = ({0, 0, 12, 1}, {-8, 5})
    std::cout << "m3 = " << monom3 << '\n' << "m4 = " << monom4 << "\n\n";
    std::cout << "m3 * m4 =\t" << monom3 * monom4 << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "m3 *= m4 =\t" << (monom3 *= monom4) << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "m3 /= m4 = \t" << (monom3 /= monom4) << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    PrintLine();

    gb::Monomial monom5({3, 0, 4}, 2);
    gb::Monomial monom6({3, 0, 4}, 1);
    std::cout << "m5 = " << monom5 << '\n' << "m6 = " << monom6 << "\n\n";
    std::cout << "m5 == m6\t\tis " << TrueFalse(monom5 == monom6) << '\n';
    std::cout << "m5 == 2 * m6\t\tis " << TrueFalse(monom5 == 2 * monom6) << '\n';
    std::cout << "3 * m5 == m6 * 6\tis " << TrueFalse(3 * monom5 == monom6 * 6) << '\n';
    std::cout << "m5 / m6 =\t\t" << monom5 / monom6 << '\n';
    std::cout << "m5 divided by m6\tis " << TrueFalse(monom5.IsDividedBy(monom6)) << "\n\n";
    std::cout << "(1) * " << monom6 << " = " << +monom6 << '\n';
    std::cout << "(-1) * " << monom5 << " = " << -monom5 << '\n';

    PrintLine();
    gb::Monomial monom7({1, 2, 5});
    gb::Monomial monom8({1, 3, 5});
    std::cout << "m7 = " << monom7 << '\n' << "m8 = " << monom8 << "\n\n";
    std::cout << "m7 / m8 = " << monom7 / monom8 << '\n';    
    std::cout << "m8 / m7 = " << monom8 / monom7 << '\n';
    std::cout << "m7 / m8 * m8 = " << monom7 / monom8 * monom8 << '\n';
    std::cout << "m7 * m8 / m8 = " << monom7 * monom8 / monom8 << '\n';
    PrintLine(2);
}