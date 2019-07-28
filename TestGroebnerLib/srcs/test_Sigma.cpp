#include "../includes/Tests.h"

void test_Sigma(i32 variable_count) {
    std::cout << "Test \\sigma with " << variable_count << " variables:\n";
    std::cout << gb::GiveGroebnerSigmaSet<Rational, gb::LexComp>(variable_count) << '\n';
    PrintLine();
}
