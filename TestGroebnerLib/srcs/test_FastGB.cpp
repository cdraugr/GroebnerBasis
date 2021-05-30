#include "Tests.h"

static void test_FastGBTime(gb::PolynomialSet<Rational, gb::LexComp>& ideal) {
    gb::calculated_fast_gb(ideal);
}

void test_FastGB(u32 maximum_variables) {
    gb::Polynomial<Rational> i1({  // HW 07, ex 01
        gb::Term<Rational>(gb::Monomial({2, 1, 0}), 1),
        gb::Term<Rational>(gb::Monomial({1, 0, 1}), -1),
    });
    gb::Polynomial<Rational> i2({
        gb::Term<Rational>(gb::Monomial({0, 2, 0}), 1),
        gb::Term<Rational>(gb::Monomial({0, 1, 1}), 2),
    });
    gb::PolynomialSet<Rational> ideal({i1, i2});

    std::cout << "Before F4 {\n" << ideal << "\n}\n";
    gb::calculated_fast_gb(ideal);
    std::cout << "After F4  {\n" << ideal.ReduceBasis() << "\n}\n\n";
    assert(gb::IsGroebnerBasis(ideal) == true);

    for (u32 i = 1; i <= maximum_variables ; ++i) {
        auto ideal = gb::GiveRootSet<Rational, gb::LexComp>(i);

        test_time(test_FastGBTime, "Time spent for calculate Root " +  std::to_string(i) + " Groebner Basis is ")(ideal);

        if (gb::IsGroebnerBasis(ideal.ReduceBasis()) != true) {
            std::cout << "F4 Tests status: \033[1;31mFAIL\033[0m.\n\n";
            return;
        }
    }

    std::cout << "\nF4 Tests status: \033[1;32mOK\033[0m.\n";
}
