#include "F4GB.hpp"
#include "TimerWrapper.hpp"

#include <string>
#include <ios>

using u64 = std::uint64_t;
using i64 = std::int64_t;

namespace constants {
    const u64 DIVIDING_LINE_LENGHT = 50;
    const char DIVIDING_LINE_SYMBOL = '-';
    const std::string DIVIDING_LINE(constants::DIVIDING_LINE_LENGHT, constants::DIVIDING_LINE_SYMBOL);
}  // namespace constants

void print_line(u32 = 1);

void test_fields();
void assert_rational_(const gb::fields::Rational&, const i64& = 0, const i64& = 1);
void test_rational();

template <u64 TBase>
void assert_modular_(const gb::fields::Modular<TBase>&, const i64&);
void test_modular();

void assert_term_(const gb::Term&, const std::vector<i64>&);
void test_term();
void assert_rational_monomial_(const gb::Monomial<gb::fields::Rational>&, const std::vector<i64>&, const i64& = 0, const i64& = 1);
void test_monomial();

template <typename Comp>
void test_monomial_comp_(const std::vector<gb::Monomial<gb::fields::Rational>>&, const std::vector<std::vector<bool>>&);
void test_monomial_order();

void test_polynomial();
void test_polynomial_order();
void test_polynomial_set();

void test_root(u32);
void test_time_deg_rev_lex_(u32);
void test_time_lex_(u32);
void test_root_time(u32);

void test_critical_pair();
void test_f4_gb_time_(gb::PolynomialSet<gb::fields::Rational, gb::LexComp>&);
void test_f4_gb(u32);

template <u64 TBase>
void assert_modular_(const gb::fields::Modular<TBase>& value, const i64& number) {
    assert(value.GetNumber() == number);
}

template <typename Comp>
void test_monomial_comp_(
    const std::vector<gb::Monomial<gb::fields::Rational>>& monomials,
    const std::vector<bool>& expected_comparations
) {
    Comp comparator;
    for (size_t i = 0; i != monomials.size(); ++i) {
        for (size_t j = 0; j != monomials.size(); ++j) {
            std::cout << std::boolalpha << 't' << i + 1 << " < t" << j + 1 << " is "
                    << comparator(monomials[i], monomials[j]) << '\n';
            assert(comparator(monomials[i], monomials[j]) == expected_comparations[i * monomials.size() + j]);
        }
    }

    std::set<gb::Monomial<gb::fields::Rational>, Comp> monomial_set(monomials.begin(), monomials.end());
    std::cout << "\nset:\n";
    for (const auto& monomial : monomial_set) {
        std::cout << monomial << '\n';
    }
    print_line();
}