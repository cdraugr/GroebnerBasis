#include "Tests.hpp"

void test_root(u32 variable_count) {
    std::cout << "Test Root with " << variable_count << " variables:\n";
    std::cout << gb::GiveGroebnerRootSet<gb::fields::Rational, gb::LexComp>(variable_count) << '\n';
    utils::print_line();
}
