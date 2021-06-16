#include "Tests.h"

void test_Root(u32 variable_count) {
    std::cout << "Test Root with " << variable_count << " variables:\n";
    std::cout << gb::GiveGroebnerRootSet<Rational, gb::LexComp>(variable_count) << '\n';
    PrintLine();
}
