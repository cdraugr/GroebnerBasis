#include "Tests.hpp"

namespace utils {

void print_line(u32 count) {
    while (count--) {
        std::cout << constants::DIVIDING_LINE << '\n';
    }
}

}  // namespace utils

namespace asserts {

void assert_rational_(const gb::fields::Rational& value, const i64& numerator, const i64& denominator) {
    assert(value.GetNumerator() == numerator);
    assert(value.GetDenominator() == denominator);
}

void assert_term_(const gb::Term& term, const std::vector<i64>& degrees) {
    std::map<gb::i64, gb::i64> map_degrees;
    for (size_t i = 0; i != degrees.size(); ++i) {
        if (degrees[i] != 0) {
            map_degrees[static_cast<gb::i64>(i)] = degrees[i];
        }
    }

    assert(term.GetDegrees() == map_degrees);
}

void assert_rational_monomial_(
    const gb::Monomial<gb::fields::Rational>& monomial,
    const std::vector<i64>& degrees,
    const i64& numerator,
    const i64& denominator
) {
    asserts::assert_term_(monomial.GetTerm(), degrees);
    asserts::assert_rational_(monomial.GetCoefficient(), numerator, denominator);
}

}  // namespace asserts

namespace times {

gb::PolynomialSet<gb::fields::Rational, gb::LexCoefComp> LexGroebnerSystem;

void test_time_deg_rev_lex_(u32 variable_count) {
    auto DegReLexGroebnerSystem = gb::GiveGroebnerRootSet<gb::fields::Rational, gb::DegReLexCoefComp>(variable_count);
    LexGroebnerSystem = DegReLexGroebnerSystem;
    LexGroebnerSystem.MakeGroebnerBasis().ReduceBasis();
}

void test_time_lex_(u32 variable_count) {
    LexGroebnerSystem = gb::GiveGroebnerRootSet<gb::fields::Rational, gb::LexComp>(variable_count);
}

void test_f4_gb_time_(gb::PolynomialSet<gb::fields::Rational, gb::LexComp>& ideal) {
    gb::inplace_calculate_f4_gb(ideal);
}

void test_f5_gb_time_(gb::PolynomialSet<gb::fields::Rational, gb::LexComp>& ideal) {
    gb::inplace_calculate_f5_gb(ideal);
}

}  // namespace times
