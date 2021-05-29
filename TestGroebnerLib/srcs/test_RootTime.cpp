#include "Tests.h"

gb::PolynomialSet<Rational, gb::LexCoefComp> LexGroebnerSystem;

static void test_Time_DegRevLex(u32 variable_count) {
    auto DegReLexGroebnerSystem = gb::GiveGroebnerRootSet<Rational, gb::DegReLexCoefComp>(variable_count);
    LexGroebnerSystem = DegReLexGroebnerSystem;
    LexGroebnerSystem.MakeGroebnerBasis().ReduceBasis();
}

static void test_Time_Lex(u32 variable_count) {
    LexGroebnerSystem = gb::GiveGroebnerRootSet<Rational, gb::LexComp>(variable_count);
}

void test_RootTime(u32 maximum_variables) {
    for (u32 i = 1; i <= maximum_variables; ++i) {
        std::cout << "Test Root with " << i << (i > 1 ? " variables" : " variable") << ":\n";

        std::string text = "Time spended for calculate Root ";
        text.push_back('0' + i);
        test_time(test_Time_DegRevLex, text + " using DegRevLex = ")(i);

        text = "Time spended for calculate Root ";
        text.push_back('0' + i);
        test_time(test_Time_Lex, text + " using only Lex = ")(i);
        std::cout << "Result System: {\n" << LexGroebnerSystem << "\n}\n";
        PrintLine(2);
    }
}
