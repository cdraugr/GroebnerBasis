#include "Tests.hpp"

int main() {
    test_fields();

    test_term();
    test_monomial();
    test_monomial_order();

    test_polynomial();
    test_polynomial_order();
    test_polynomial_set();

    test_root(3);
    test_root_time(3);

    test_critical_pair();
    test_f4_gb(7);
}
