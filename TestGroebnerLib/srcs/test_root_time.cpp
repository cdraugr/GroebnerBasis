#include "Tests.hpp"

void test_root_time(u32 maximum_variables) {
    for (u32 i = 1; i <= maximum_variables; ++i) {
        std::cout << "Test Root with " << i << (i > 1 ? " variables" : " variable") << ":\n";

        std::string text = "Time spended for calculate Root ";
        text.push_back('0' + i);
        test_time(times::test_time_deg_rev_lex_, text + " using DegRevLex = ")(i);

        text = "Time spended for calculate Root ";
        text.push_back('0' + i);
        test_time(times::test_time_lex_, text + " using only Lex = ")(i);
        std::cout << "Result System: {\n" << times::LexGroebnerSystem << "\n}\n";
        utils::print_line(2);
    }
}
