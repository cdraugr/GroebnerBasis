#include "Tests.hpp"

gb::PolynomialSet<gb::fields::Rational, gb::LexCoefComp> LexGroebnerSystem;

void test_time_deg_rev_lex_(u32 variable_count) {
    auto DegReLexGroebnerSystem = gb::GiveGroebnerRootSet<gb::fields::Rational, gb::DegReLexCoefComp>(variable_count);
    LexGroebnerSystem = DegReLexGroebnerSystem;
    LexGroebnerSystem.MakeGroebnerBasis().ReduceBasis();
}

void test_time_lex_(u32 variable_count) {
    LexGroebnerSystem = gb::GiveGroebnerRootSet<gb::fields::Rational, gb::LexComp>(variable_count);
}

void test_root_time(u32 maximum_variables) {
    for (u32 i = 1; i <= maximum_variables; ++i) {
        std::cout << "Test Root with " << i << (i > 1 ? " variables" : " variable") << ":\n";

        std::string text = "Time spended for calculate Root ";
        text.push_back('0' + i);
        test_time(test_time_deg_rev_lex_, text + " using DegRevLex = ")(i);

        text = "Time spended for calculate Root ";
        text.push_back('0' + i);
        test_time(test_time_lex_, text + " using only Lex = ")(i);
        std::cout << "Result System: {\n" << LexGroebnerSystem << "\n}\n";
        print_line(2);
    }
}
