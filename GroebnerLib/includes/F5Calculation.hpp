#pragma once

#include "LabeledPolynomial.hpp"
#include "PolynomialSet.hpp"

namespace gb {

template <typename T, typename Comp>
class F5Calculation {
public:
    F5Calculation(const PolynomialSet<T, Comp>&);

    PolynomialSet<T, Comp> CalculateBasis();

    struct IndexCriticalPair {
        gb::i64 degree{};
        Term lcm;
        Term left_term;
        size_t left_polynomial_index;
        Term right_term;
        size_t right_polynomial_index;

        friend bool operator<(const IndexCriticalPair& lht, const IndexCriticalPair& rht) noexcept {
            return std::tie(lht.degree, lht.left_polynomial_index, lht.right_polynomial_index) <
                std::tie(rht.degree, rht.left_polynomial_index, rht.right_polynomial_index);
        }
    };

private:
    std::vector<Polynomial<T, Comp>> given_set_;  // F

    std::vector<std::set<size_t>> result_indexes_;  // G
    std::vector<LabeledPolynomial<T, Comp>> labeled_polynomials_;  // r
    std::vector<std::vector<typename LabeledPolynomial<T, Comp>::signature>> rules_;  // Rules

    void algorithm_f5_(const size_t&);
    std::optional<IndexCriticalPair> get_critical_pair_(size_t, size_t);
    std::set<size_t> reduction_(const std::vector<size_t>&, const size_t&);
    std::vector<size_t> get_s_polynomials_(const std::set<IndexCriticalPair>&);
    void add_rule_(const size_t&);
    bool is_rewritable_(const Term&, const size_t&);
    size_t rewrite_(const Term&, const size_t&);
};

template <typename T, typename Comp>
F5Calculation<T, Comp>::F5Calculation(const PolynomialSet<T, Comp>& given_set) {
    std::copy(given_set.GetPolynomials().begin(), given_set.GetPolynomials().end(), std::back_inserter(given_set_));

    result_indexes_.resize(given_set_.size());
    labeled_polynomials_.resize(given_set_.size());
    rules_.resize(given_set_.size());
}

template <typename T, typename Comp>
PolynomialSet<T, Comp> F5Calculation<T, Comp>::CalculateBasis() {
    if (given_set_.empty()) {
        return {};
    }

    const Monomial<T> value_type_one(1);
    result_indexes_.back() = {given_set_.size() - 1};
    labeled_polynomials_.back() = {given_set_.size() - 1, given_set_.back().Normalized()};

    for (size_t i = given_set_.size() - 1; i != 0; --i) {
        algorithm_f5_(i - 1);
        for (const auto& index : result_indexes_[i - 1]) {
            // std::cout << index << std::endl;
            if (labeled_polynomials_[index].GetEvaluation() == value_type_one) {
                return {value_type_one};
            }
        }
    }

    PolynomialSet<T, Comp> result;
    for (const auto& index : result_indexes_.front()) {
        result.AddPolynomial(labeled_polynomials_[index].GetEvaluation());
    }
    return result;
}

template <typename T, typename Comp>
void F5Calculation<T, Comp>::algorithm_f5_(const size_t& current_index) {  // G' == G[current_index], G_i == G[current_index + 1];
    labeled_polynomials_[current_index] = {current_index, given_set_[current_index].Normalized()};

    result_indexes_[current_index] = result_indexes_[current_index + 1];
    result_indexes_[current_index].insert(current_index);

    std::set<IndexCriticalPair> critical_pairs;
    for (const auto& j : result_indexes_[current_index + 1]) {
        const auto critical_pair = get_critical_pair_(current_index, j);
        if (critical_pair.has_value()) {
            critical_pairs.insert(critical_pair.value());
        }
    }

    while (!critical_pairs.empty()) {
        std::set<IndexCriticalPair> selected;
        const auto min_degree = critical_pairs.begin()->degree;
        for (auto it = critical_pairs.begin(); it != critical_pairs.end(); ) {
            if (it->degree != min_degree) {
                break;
            }
            selected.insert(*it);
            it = critical_pairs.erase(it);
        }

        for (const auto& reduced_index : reduction_(get_s_polynomials_(selected), current_index)) {
            for (const auto& j : result_indexes_[current_index]) {
                const auto critical_pair = get_critical_pair_(reduced_index, j);
                if (critical_pair.has_value()) {
                    critical_pairs.insert(critical_pair.value());
                }
            }
            result_indexes_[current_index].insert(reduced_index);
        }
    }
}

template <typename T, typename Comp>
std::optional<typename F5Calculation<T, Comp>::IndexCriticalPair> F5Calculation<T, Comp>::get_critical_pair_(size_t lht_index, size_t rht_index) {
    const Term current_lcm = lcm(labeled_polynomials_[lht_index].LeadTerm(), labeled_polynomials_[rht_index].LeadTerm());
    auto lht_multiplier = current_lcm / labeled_polynomials_[lht_index].LeadTerm();
    auto rht_multiplier = current_lcm / labeled_polynomials_[rht_index].LeadTerm();

    Comp comparator;  // TODO: sigmoid<
    bool comparition_result = comparator(
        Monomial<T>(lht_multiplier * labeled_polynomials_[lht_index].GetTerm(), static_cast<T>(1)),
        Monomial<T>(rht_multiplier * labeled_polynomials_[rht_index].GetTerm(), static_cast<T>(1))
    );
    if (lht_index > rht_index || (lht_index == rht_index && comparition_result)) {
        std::swap(lht_index, rht_index);
        std::swap(lht_multiplier, rht_multiplier);
    }

    const auto [lht_term, lht_signature_index] = labeled_polynomials_[lht_index].GetSignature();
    for (const auto& r_index : result_indexes_[lht_signature_index + 1]) {
        if ((lht_multiplier * lht_term).IsDivisibleBy(labeled_polynomials_[r_index].LeadTerm())) {
            return std::nullopt;
        }
    }

    const auto [rht_term, rht_signature_index] = labeled_polynomials_[rht_index].GetSignature();
    for (const auto& r_index : result_indexes_[rht_signature_index + 1]) {
        if ((rht_multiplier * rht_term).IsDivisibleBy(labeled_polynomials_[r_index].LeadTerm())) {
            return std::nullopt;
        }
    }
    return {{deg(current_lcm), current_lcm, lht_multiplier, lht_index, rht_multiplier, rht_index}};
}

template <typename T, typename Comp>
std::vector<size_t> F5Calculation<T, Comp>::get_s_polynomials_(const std::set<typename F5Calculation<T, Comp>::IndexCriticalPair>& selected) {
    std::vector<size_t> result;
    for (const auto& critical_pair : selected) {
        const auto lht_coefficient = labeled_polynomials_[critical_pair.left_polynomial_index].GetEvaluation().LeadCoefficient();
        const auto rht_coefficient = labeled_polynomials_[critical_pair.right_polynomial_index].GetEvaluation().LeadCoefficient();

        const auto s_polynomial = \
            Monomial<T>(critical_pair.left_term, static_cast<T>(1)) * labeled_polynomials_[critical_pair.left_polynomial_index].GetEvaluation() \
            - Monomial<T>(critical_pair.right_term, lht_coefficient / rht_coefficient) * labeled_polynomials_[critical_pair.right_polynomial_index].GetEvaluation();

        if (
            s_polynomial.IsZero() ||
            is_rewritable_(critical_pair.left_term, critical_pair.left_polynomial_index) ||
            is_rewritable_(critical_pair.right_term, critical_pair.right_polynomial_index)
        ) {
            continue;
        }

        labeled_polynomials_.emplace_back(
            critical_pair.left_term * labeled_polynomials_[critical_pair.right_polynomial_index].GetTerm(),
            critical_pair.right_polynomial_index,
            s_polynomial
        );

        add_rule_(labeled_polynomials_.size() - 1);
        result.push_back(labeled_polynomials_.size() - 1);
    }
    // TODO: sort F s.t. i < j => S(rFi) ≺ S(rFj)
    return result;
}

template <typename T, typename Comp>  // G' == G[current_index], G_i == G[current_index + 1];
std::set<size_t> F5Calculation<T, Comp>::reduction_(const std::vector<size_t>& s_polynomials, const size_t& current_index) {
    std::set<size_t> result;
    // TODO

    return result;
}

template <typename T, typename Comp>
void F5Calculation<T, Comp>::add_rule_(const size_t& rule_index) {
    const auto& [term, i] = labeled_polynomials_[rule_index].GetSignature();
    rules_[i].emplace_back(term, rule_index);
}

template <typename T, typename Comp>
bool F5Calculation<T, Comp>::is_rewritable_(const Term& to_rewrite, const size_t& r_index) {
    return r_index != rewrite_(to_rewrite, r_index);
}

template <typename T, typename Comp>
size_t F5Calculation<T, Comp>::rewrite_(const Term& to_rewrite, const size_t& r_index) {
    const auto& [multiplier, i] = labeled_polynomials_[r_index].GetSignature();
    for (auto j = rules_[i].size(); j != 0; --j) {
        const auto& [divisible, candidate] = rules_[i][j - 1];
        if ((multiplier * to_rewrite).IsDivisibleBy(divisible)) {
            return candidate;
        }
    }
    return r_index;
}

}  // namespace gb
