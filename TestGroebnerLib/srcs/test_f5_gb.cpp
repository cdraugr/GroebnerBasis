#include "Tests.hpp"

void test_f5_gb(u32 maximum_variables) {
    auto ideal = gb::GiveRootSet<gb::fields::Rational, gb::LexComp>(maximum_variables);
    std::cout << "{\n" << gb::inplace_calculate_f5_gb(ideal) << "\n}\n";
    std::cout << std::boolalpha << gb::fast_is_gb(ideal) << '\n';

    utils::print_line(2);
}
