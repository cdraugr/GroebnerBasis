#pragma once

#include "MatrixReduction.hpp"
#include "CriticalPairSet.hpp"

namespace gb {

template <typename T, typename Comp>  // vector<pair<set to reduce, result of reductions>>
using ResultsTriangPairs = std::vector<std::pair<PolynomialSet<T, Comp>, PolynomialSet<T, Comp>>>;

/* Declaration */

template <typename T, typename Comp>
CriticalPairSet<T, Comp> normal_select(CriticalPairSet<T, Comp>&);

template <typename T, typename Comp>
void erase_crit_by_lcm_(const Polynomial<T, Comp>&, CriticalPairSet<T, Comp>&);

template <typename T, typename Comp>
void insert_crit_by_gcd_(const CriticalPairSet<T, Comp>&, const Polynomial<T, Comp>&, CriticalPairSet<T, Comp>&);

template <typename T, typename Comp>
void insert_crit_by_lcm_(const CriticalPairSet<T, Comp>&, const Polynomial<T, Comp>&, CriticalPairSet<T, Comp>&);

template <typename T, typename Comp>
void erase_polynomial_by_lead_(const Polynomial<T, Comp>&, PolynomialSet<T, Comp>&);

template <typename T, typename Comp>
void update_(PolynomialSet<T, Comp>&, CriticalPairSet<T, Comp>&, const Polynomial<T, Comp>&);

template <typename T, typename Comp>
Polynomial<T, Comp> simplify_and_multiplicate_(const Term&, const Polynomial<T, Comp>&, const ResultsTriangPairs<T, Comp>&);

template <typename T, typename Comp>
std::pair<typename Polynomial<T, Comp>::container, typename Polynomial<T, Comp>::container>
prepare_monomials_sets_(const PolynomialSet<T, Comp>&, const CriticalPairSet<T, Comp>&);

template <typename T, typename Comp>
void find_and_insert_possible_reducer_(
    const PolynomialSet<T, Comp>&, const Monomial<T>&, const typename Polynomial<T, Comp>::container&,
    const ResultsTriangPairs<T, Comp>&, PolynomialSet<T, Comp>&, typename Polynomial<T, Comp>::container&
);

template <typename T, typename Comp>
std::pair<PolynomialSet<T, Comp>, typename Polynomial<T, Comp>::container>
sym_preproc_(const CriticalPairSet<T, Comp>&, const PolynomialSet<T, Comp>&, const ResultsTriangPairs<T, Comp>&);

template <typename T, typename Comp>
PolynomialSet<T, Comp> reduction_(const CriticalPairSet<T, Comp>&, const PolynomialSet<T, Comp>&, ResultsTriangPairs<T, Comp>&);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
PolynomialSet<T, Comp>& inplace_calculate_f4_gb(PolynomialSet<T, Comp>&, SelFunction = normal_select);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
PolynomialSet<T, Comp> calculate_f4_gb(const PolynomialSet<T, Comp>&, SelFunction = normal_select);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
bool fast_is_gb(const PolynomialSet<T, Comp>&, SelFunction = normal_select);

/* Implementation */

template <typename T, typename Comp>
CriticalPairSet<T, Comp> normal_select(CriticalPairSet<T, Comp>& critical_pairs) {
    CriticalPairSet<T, Comp> selected;
    const auto min_degree = critical_pairs.GetCriticalPairs().begin()->GetDegree();

    for (auto it = critical_pairs.GetCriticalPairs().begin(); it != critical_pairs.GetCriticalPairs().end(); ) {
        if (it->GetDegree() != min_degree) {
            break;
        }
        selected.AddCriticalPair(*it);
        it = critical_pairs.RemoveCriticalPair(it);
    }
    return selected;
}

template <typename T, typename Comp>
void erase_crit_by_lcm_(const Polynomial<T, Comp>& polynomial_to_insert, CriticalPairSet<T, Comp>& all_crit) {
    for (auto it = all_crit.GetCriticalPairs().begin(); it != all_crit.GetCriticalPairs().end(); ) {
        if (gcd(polynomial_to_insert.LeadTerm(), it->GetRightPolynomial().LeadTerm()).IsOne()) {
            ++it;
            continue;
        }

        bool erased = false;
        for (auto jt = all_crit.GetCriticalPairs().begin(); jt != all_crit.GetCriticalPairs().end(); ++jt) {
            if (it == jt) {
                continue;
            }

            if (lcm(
                    polynomial_to_insert.LeadTerm(), it->GetRightPolynomial().LeadTerm()
                ).IsDivisibleBy(lcm(
                    polynomial_to_insert.LeadTerm(), jt->GetRightPolynomial().LeadTerm()
                ))
            ) {
                it = all_crit.RemoveCriticalPair(it);
                erased = true;
                break;
            }
        }
        if (!erased) {
            ++it;
        }
    }
}

template <typename T, typename Comp>
void insert_crit_by_gcd_(
        const CriticalPairSet<T, Comp>& all_crit,
        const Polynomial<T, Comp>& polynomial_to_insert,
        CriticalPairSet<T, Comp>& new_crit_pairs) {
    for (auto it = all_crit.GetCriticalPairs().begin(); it != all_crit.GetCriticalPairs().end(); ++it) {
        if (!gcd(polynomial_to_insert.LeadTerm(), it->GetRightPolynomial().LeadTerm()).IsOne()) {
            new_crit_pairs.AddCriticalPair(*it);
        }
    }
}

template <typename T, typename Comp>
void insert_crit_by_lcm_(
        const CriticalPairSet<T, Comp>& old_crit_pairs,
        const Polynomial<T, Comp>& polynomial_to_insert,
        CriticalPairSet<T, Comp>& new_crit_pairs) {
    for (const auto& old_pair : old_crit_pairs.GetCriticalPairs()) {
        if (!old_pair.GetLcm().IsDivisibleBy(polynomial_to_insert.LeadTerm()) ||
            (old_pair.GetLcm() == lcm(old_pair.GetLeftPolynomial().LeadTerm(), polynomial_to_insert.LeadTerm())) ||
            (old_pair.GetLcm() == lcm(old_pair.GetRightPolynomial().LeadTerm(), polynomial_to_insert.LeadTerm()))
        ) {
            new_crit_pairs.AddCriticalPair(old_pair);
        }
    }
}

template <typename T, typename Comp>
void erase_polynomial_by_lead_(const Polynomial<T, Comp>& polynomial_to_insert, PolynomialSet<T, Comp>& old_polynomial_set) {
    for (auto it = old_polynomial_set.GetPolynomials().begin(); it != old_polynomial_set.GetPolynomials().end(); ) {
        if (it->LeadTerm().IsDivisibleBy(polynomial_to_insert.LeadTerm())) {
            it = old_polynomial_set.RemovePolynomial(it);
        } else {
            ++it;
        }
    }
}

template <typename T, typename Comp>
void update_(
        PolynomialSet<T, Comp>& old_polynomial_set,
        CriticalPairSet<T, Comp>& old_crit_pairs,
        const Polynomial<T, Comp>& polynomial_to_insert) {
    CriticalPairSet<T, Comp> all_crit, new_crit_pairs;
    for (const auto& polynomial : old_polynomial_set.GetPolynomials()) {
        all_crit.AddCriticalPair(CriticalPair(polynomial_to_insert, polynomial));
    }

    erase_crit_by_lcm_(polynomial_to_insert, all_crit);
    insert_crit_by_gcd_(all_crit, polynomial_to_insert, new_crit_pairs);
    insert_crit_by_lcm_(old_crit_pairs, polynomial_to_insert, new_crit_pairs);
    old_crit_pairs = std::move(new_crit_pairs);

    erase_polynomial_by_lead_(polynomial_to_insert, old_polynomial_set);
    old_polynomial_set.AddPolynomial(polynomial_to_insert);
}

template <typename T, typename Comp>
Polynomial<T, Comp> simplify_and_multiplicate_(
        const Term& term, const Polynomial<T, Comp>& polynomial,
        const ResultsTriangPairs<T, Comp>& results_triang_pairs) {
    const T value_type_one(1);
    const auto divisors = GetAllDivisors(term);

    for (const auto& divisor : divisors) {
        for (const auto& [result, triang] : results_triang_pairs) {
            const auto multiplicated = Monomial<T>(divisor, value_type_one) * polynomial;
            if (!result.IsPolynomialInMe(multiplicated)) {
                continue;
            }

            for (const auto& triang_polynomial : triang.GetPolynomials()) {
                if (triang_polynomial.LeadTerm() == multiplicated.LeadTerm()) {
                    if (divisor.IsOne()) {
                        return Monomial<T>(term, value_type_one) * triang_polynomial;
                    } else if (divisor != term) {
                        return simplify_and_multiplicate_(term / divisor, triang_polynomial, results_triang_pairs);
                    }
                    return triang_polynomial;
                }
            }
        }
    }
    return Monomial<T>(term, value_type_one) * polynomial;
}

template <typename T, typename Comp>
std::pair<typename Polynomial<T, Comp>::container, typename Polynomial<T, Comp>::container>
prepare_monomials_sets_(const PolynomialSet<T, Comp>& to_reduce, const CriticalPairSet<T, Comp>& critical_pairs) {
    const T value_type_one(1);
    typename Polynomial<T, Comp>::container relative_complement;
    for (const auto& polynomial : to_reduce.GetPolynomials()) {
        for (const auto& monomial : polynomial.GetMonomials()) {
            relative_complement.insert(Monomial<T>(monomial.GetTerm(), value_type_one));
        }
    }

    typename Polynomial<T, Comp>::container done_monomials;
    for (const auto& critical_pair : critical_pairs.GetCriticalPairs()) {
        Monomial<T> done_monomial(critical_pair.GetLcm(), value_type_one);
        done_monomials.insert(done_monomial);
        relative_complement.erase(done_monomial);
    }
    return {relative_complement, done_monomials};
}

template <typename T, typename Comp>
void find_and_insert_possible_reducer_(
        const PolynomialSet<T, Comp>& polynomial_set,
        const Monomial<T>& current_monomial,
        const typename Polynomial<T, Comp>::container& done_monomials,
        const ResultsTriangPairs<T, Comp>& results_triang_pairs,
        PolynomialSet<T, Comp>& to_reduce,
        typename Polynomial<T, Comp>::container& relative_complement) {
    for (const auto& polynomial : polynomial_set.GetPolynomials()) {
        if (!current_monomial.IsDivisibleBy(polynomial.LeadMonomial())) {
            continue;
        }

        const auto polynomial_to_add =
            simplify_and_multiplicate_((current_monomial / polynomial.LeadMonomial()).GetTerm(), polynomial, results_triang_pairs);
        to_reduce.AddPolynomial(polynomial_to_add);

        const T value_type_one(1);
        for (const auto& monomial : polynomial_to_add.GetMonomials()) {
            Monomial<T> monomial_to_add(monomial.GetTerm(), value_type_one);
            if (done_monomials.find(monomial_to_add) == done_monomials.end()) {
                relative_complement.insert(monomial_to_add);
            }
        }
        return;
    }
}

template <typename T, typename Comp>
std::pair<PolynomialSet<T, Comp>, typename Polynomial<T, Comp>::container>
sym_preproc_(
        const CriticalPairSet<T, Comp>& critical_pairs,
        const PolynomialSet<T, Comp>& polynomial_set,
        const ResultsTriangPairs<T, Comp>& results_triang_pairs) {
    PolynomialSet<T, Comp> to_reduce;
    for (const auto& critical_pair : critical_pairs.GetCriticalPairs()) {
        to_reduce.AddPolynomial(simplify_and_multiplicate_(critical_pair.GetLeftTerm(), critical_pair.GetLeftPolynomial(), results_triang_pairs));
        to_reduce.AddPolynomial(simplify_and_multiplicate_(critical_pair.GetRightTerm(), critical_pair.GetRightPolynomial(), results_triang_pairs));
    }

    auto [relative_complement, done_monomials] = prepare_monomials_sets_(to_reduce, critical_pairs);

    while (!relative_complement.empty()) {
        const Monomial<T> current_monomial = *relative_complement.begin();
        done_monomials.insert(current_monomial);
        relative_complement.erase(relative_complement.begin());
        find_and_insert_possible_reducer_(polynomial_set, current_monomial, done_monomials, results_triang_pairs, to_reduce, relative_complement);
    }

    return {to_reduce, done_monomials};
}

template <typename T, typename Comp>
PolynomialSet<T, Comp> reduction_(
        const CriticalPairSet<T, Comp>& critical_pairs,
        const PolynomialSet<T, Comp>& polynomial_set,
        ResultsTriangPairs<T, Comp>& results_triang_pairs) {
    auto [results, all_monomials] = sym_preproc_(critical_pairs, polynomial_set, results_triang_pairs);

    const T value_type_one(1);
    typename Polynomial<T, Comp>::container lead_monomials;
    for (const auto& polynomial : results.GetPolynomials()) {
        lead_monomials.insert(Monomial<T>(polynomial.LeadTerm(), value_type_one));
    }

    const auto [triang, reduced_results] = matrix_reduction::matrix_reduction(results, all_monomials, lead_monomials);
    results_triang_pairs.push_back({results, triang});
    return reduced_results;
}

template <typename T, typename Comp, typename SelFunction>
PolynomialSet<T, Comp>& inplace_calculate_f4_gb(PolynomialSet<T, Comp>& given_set, SelFunction select_function) {
    given_set = calculate_f4_gb(given_set, select_function);
    return given_set;
}

template <typename T, typename Comp, typename SelFunction>
PolynomialSet<T, Comp> calculate_f4_gb(const PolynomialSet<T, Comp>& given_set, SelFunction select_function) {
    PolynomialSet<T, Comp> groebner_basis;
    CriticalPairSet<T, Comp> critical_pairs;
    for (auto it = given_set.GetPolynomials().rbegin(); it != given_set.GetPolynomials().rend(); ++it) {
        update_(groebner_basis, critical_pairs, *it);
    }

    ResultsTriangPairs<T, Comp> results_triang_pairs;
    results_triang_pairs.reserve(given_set.size() * 2);
    while (!critical_pairs.empty()) {
        const auto selected_set = select_function(critical_pairs);
        const auto reduced_set = reduction_(selected_set, groebner_basis, results_triang_pairs);
        for (auto it = reduced_set.GetPolynomials().rbegin(); it != reduced_set.GetPolynomials().rend(); ++it) {
            update_(groebner_basis, critical_pairs, *it);
        }
    }
    return groebner_basis;
}

template <typename T, typename Comp, typename SelFunction>
bool fast_is_gb(const PolynomialSet<T, Comp>& given_set, SelFunction select_function) {
    PolynomialSet<T, Comp> groebner_basis;
    CriticalPairSet<T, Comp> critical_pairs;
    for (const auto& polynomial : given_set.GetPolynomials()) {
        update_(groebner_basis, critical_pairs, polynomial);
    }

    ResultsTriangPairs<T, Comp> results_triang_pairs;
    results_triang_pairs.reserve(given_set.size() * 2);
    while (!critical_pairs.empty()) {
        const auto selected_set = select_function(critical_pairs);
        const auto reduced_set = reduction_(selected_set, groebner_basis, results_triang_pairs);
        if (reduced_set.size()) {
            return false;
        }
    }
    return true;
}

}  // namespace gb
