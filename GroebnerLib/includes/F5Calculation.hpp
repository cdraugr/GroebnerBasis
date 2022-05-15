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
    std::vector<std::vector<Signature<T, Comp>>> rules_;  // Rules

    void algorithm_f5_(const size_t&);
    std::optional<IndexCriticalPair> get_critical_pair_(size_t, size_t);
    std::set<size_t> reduction_(std::vector<size_t>, const size_t&);
    std::vector<size_t> get_s_polynomials_(const std::set<IndexCriticalPair>&);
    void add_rule_(const size_t&);
    bool is_rewritable_(const Term&, const size_t&);
    size_t rewrite_(const Term&, const size_t&);
    std::pair<std::set<size_t>, std::vector<size_t>> top_reduction_(const size_t&, const std::set<size_t>&);
    std::optional<size_t> find_reductor_(const size_t&, const std::set<size_t>&);

    template <class RandomIt>
    void sort_by_signatures_(RandomIt, RandomIt);

    PolynomialSet<T, Comp> get_polynomial_set_from_result_indexes_(const size_t&);
    bool is_top_reducible_(const Term&, const size_t&);
};

template <typename T, typename Comp>
F5Calculation<T, Comp>::F5Calculation(const PolynomialSet<T, Comp>& given_set) {
    given_set_.resize(given_set.size());
    std::copy(given_set.GetPolynomials().rbegin(), given_set.GetPolynomials().rend(), given_set_.begin());

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
            if (labeled_polynomials_[index].GetEvaluation() == value_type_one) {
                return {value_type_one};
            }
        }
    }

    return get_polynomial_set_from_result_indexes_(0);
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

    if (lht_multiplier * labeled_polynomials_[lht_index].GetSignature() < rht_multiplier * labeled_polynomials_[rht_index].GetSignature()) {
        std::swap(lht_index, rht_index);
        std::swap(lht_multiplier, rht_multiplier);
    }

    const auto [lht_term, lht_signature_index] = labeled_polynomials_[lht_index].GetPairSignature();
    if (is_top_reducible_(lht_multiplier * lht_term, lht_signature_index)) {
        return std::nullopt;
    }

    const auto [rht_term, rht_signature_index] = labeled_polynomials_[rht_index].GetPairSignature();
    if (is_top_reducible_(rht_multiplier * rht_term, rht_signature_index)) {
        return std::nullopt;
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
            labeled_polynomials_[critical_pair.right_polynomial_index].GetBasisIndex(),
            s_polynomial
        );

        add_rule_(labeled_polynomials_.size() - 1);
        result.push_back(labeled_polynomials_.size() - 1);
    }
    sort_by_signatures_(result.begin(), result.end());
    return result;
}

template <typename T, typename Comp>
std::set<size_t> F5Calculation<T, Comp>::reduction_(std::vector<size_t> s_polynomials, const size_t& current_index) {
    std::set<size_t> result;
    while (!s_polynomials.empty()) {
        sort_by_signatures_(s_polynomials.rbegin(), s_polynomials.rend());
        const auto r_index = s_polynomials.back();
        s_polynomials.pop_back();

        auto polynomial_to_reduce = labeled_polynomials_[r_index].GetEvaluation();
        get_polynomial_set_from_result_indexes_(current_index).ReductionToResByMe(&polynomial_to_reduce);
        labeled_polynomials_[r_index].SetEvaluation(polynomial_to_reduce);

        auto set_to_reduce = result_indexes_[current_index];
        set_to_reduce.insert(result.cbegin(), result.cend());
        auto [new_polynomials, to_do] = top_reduction_(r_index, set_to_reduce);
        result.merge(new_polynomials);
        s_polynomials.insert(s_polynomials.end(), to_do.begin(), to_do.end());
    }
    return result;
}

template <typename T, typename Comp>
void F5Calculation<T, Comp>::add_rule_(const size_t& rule_index) {
    const auto& [term, i] = labeled_polynomials_[rule_index].GetPairSignature();
    rules_[i].emplace_back(term, rule_index);
}

template <typename T, typename Comp>
bool F5Calculation<T, Comp>::is_rewritable_(const Term& to_rewrite, const size_t& r_index) {
    return r_index != rewrite_(to_rewrite, r_index);
}

template <typename T, typename Comp>
size_t F5Calculation<T, Comp>::rewrite_(const Term& to_rewrite, const size_t& r_index) {
    const auto& [multiplier, i] = labeled_polynomials_[r_index].GetPairSignature();
    for (auto j = rules_[i].size(); j != 0; --j) {
        const auto& [divisible, candidate] = rules_[i][j - 1].GetPairSignature();
        if ((multiplier * to_rewrite).IsDivisibleBy(divisible)) {
            return candidate;
        }
    }
    return r_index;
}

template <typename T, typename Comp>  // G' = set_to_reduce;
std::pair<std::set<size_t>, std::vector<size_t>> F5Calculation<T, Comp>::top_reduction_(const size_t& r_index, const std::set<size_t>& set_to_reduce) {
    if (labeled_polynomials_[r_index].GetEvaluation().IsZero()) {
        std::cout << "\033[1;33mWarning: reduction to zero!\033[0m\n";
        return {{}, {}};
    }

    auto polynomial = labeled_polynomials_[r_index].GetEvaluation();
    const auto reductor_index = find_reductor_(r_index, set_to_reduce);
    if (!reductor_index.has_value()) {
        labeled_polynomials_[r_index].SetEvaluation(polynomial.Normalized());
        return {{r_index}, {}};
    }

    const auto reductior = labeled_polynomials_[reductor_index.value()].GetEvaluation();
    const auto reductior_term = polynomial.LeadTerm() / reductior.LeadTerm();
    polynomial -= polynomial.LeadMonomial() / reductior.LeadMonomial() * reductior;
    if (reductior_term * labeled_polynomials_[reductor_index.value()].GetSignature() < labeled_polynomials_[r_index].GetSignature()) {
        labeled_polynomials_[r_index].SetEvaluation(polynomial);
        return {{}, {r_index}};
    }

    labeled_polynomials_.emplace_back(
        reductior_term * labeled_polynomials_[reductor_index.value()].GetTerm(),
        labeled_polynomials_[reductor_index.value()].GetBasisIndex(),
        polynomial
    );

    add_rule_(labeled_polynomials_.size() - 1);
    return {{}, {r_index, labeled_polynomials_.size() - 1}};
}

template <typename T, typename Comp>
std::optional<size_t> F5Calculation<T, Comp>::find_reductor_(const size_t& r_index, const std::set<size_t>& set_to_reduce) {
    const auto term = labeled_polynomials_[r_index].LeadTerm();
    for (const auto& i : set_to_reduce) {
        const auto divisible = labeled_polynomials_[i].LeadTerm();
        if (!term.IsDivisibleBy(divisible)) {
            continue;
        }

        const auto [signature_term, result_index] = labeled_polynomials_[i].GetPairSignature();
        const auto quotient = term / divisible;
        if (
            quotient * labeled_polynomials_[i].GetSignature() != labeled_polynomials_[r_index].GetSignature() &&
            !is_rewritable_(quotient, i) &&
            !is_top_reducible_(quotient * signature_term, result_index)
        ) {
            return {i};
        }
    }
    return std::nullopt;
}

template <typename T, typename Comp>
template <typename RandomIt>
void F5Calculation<T, Comp>::sort_by_signatures_(RandomIt first, RandomIt last) {
    std::sort(
        first, last,
        [this](const size_t& lht, const size_t& rht) -> bool {
            return labeled_polynomials_[lht].GetSignature() < labeled_polynomials_[rht].GetSignature();
        }
    );
}

template <typename T, typename Comp>
PolynomialSet<T, Comp> F5Calculation<T, Comp>::get_polynomial_set_from_result_indexes_(const size_t& index) {
    PolynomialSet<T, Comp> result;
    for (const auto& r_index : result_indexes_[index]) {
        result.AddPolynomial(labeled_polynomials_[r_index].GetEvaluation());
    }
    return result;
}

template <typename T, typename Comp>
bool F5Calculation<T, Comp>::is_top_reducible_(const Term& term, const size_t& index) {
    for (const auto& r_index : result_indexes_[index]) {
        if (term.IsDivisibleBy(labeled_polynomials_[r_index].LeadTerm())) {
            return true;
        }
    }
    return false;
}

}  // namespace gb
