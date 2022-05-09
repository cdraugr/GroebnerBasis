#include "Tests.hpp"

void test_f4_gb(u32 maximum_variables) {
    gb::Polynomial<gb::fields::Rational> i1({  // HW 07, ex 01
        {{{2, 1}}, 1},
        {{{1, 0, 1}}, -1},
    });
    gb::Polynomial<gb::fields::Rational> i2({
        {{{0, 2}}, 1},
        {{{0, 1, 1}}, 2},
    });
    gb::PolynomialSet<gb::fields::Rational> ideal({i1, i2});

    std::cout << "Before F4 {\n" << ideal << "\n}\n";
    gb::inplace_calculate_f4_gb(ideal);
    std::cout << "After F4  {\n" << ideal.ReduceBasis() << "\n}\n\n";
    assert(gb::IsGroebnerBasis(ideal) == true);

    for (u32 i = 1; i <= maximum_variables ; ++i) {
        auto ideal = gb::GiveRootSet<gb::fields::Rational, gb::LexComp>(i);

        test_time(times::test_f4_gb_time_, "Time spent for calculate Root " +  std::to_string(i) + " Groebner Basis is ")(ideal);

        if (gb::fast_is_gb(ideal) != true) {
            std::cout << "F4 Tests status: \033[1;31mFAIL\033[0m.\n\n";
            return;
        }
    }

    std::cout << "\nF4 Tests status: \033[1;32mOK\033[0m.\n";
    utils::print_line(2);
}
