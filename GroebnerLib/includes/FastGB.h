#pragma once

#include "MatrixReduction.h"
#include "CriticalPairs.h"

namespace gb {

template <typename T, typename Comp>  // vector<pair<set to reduce, result>>
using ResultsTriangPairs =
    std::vector<std::pair<PolynomialSet<T, Comp>, PolynomialSet<T, Comp>>>;

/* Declaration */

template <typename T, typename Comp>
CriticalPairs<T, Comp> normal_select(CriticalPairs<T, Comp>&);

template <typename T, typename Comp>
static void update(PolynomialSet<T, Comp>&, CriticalPairs<T, Comp>&, const Polynomial<T, Comp>&);

template <typename T, typename Comp>
static Polynomial<T, Comp> simplify_and_multiplicate(const Monomial&, const Polynomial<T, Comp>&, const ResultsTriangPairs<T, Comp>&);

template <typename T, typename Comp>
static std::pair<PolynomialSet<T, Comp>, typename Polynomial<T, Comp>::container>
sym_preproc(const CriticalPairs<T, Comp>&, const PolynomialSet<T, Comp>&, const ResultsTriangPairs<T, Comp>&);

template <typename T, typename Comp>
static PolynomialSet<T, Comp>
reduction(const CriticalPairs<T, Comp>&, const PolynomialSet<T, Comp>&, ResultsTriangPairs<T, Comp>&);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
PolynomialSet<T, Comp>& calculated_fast_gb(PolynomialSet<T, Comp>&, SelFunction = normal_select);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
PolynomialSet<T, Comp> calculate_fast_gb(const PolynomialSet<T, Comp>&, SelFunction = normal_select);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
bool fast_is_gb(const PolynomialSet<T, Comp>&, SelFunction = normal_select);

/* Realization */

template <typename T, typename Comp>
CriticalPairs<T, Comp> normal_select(CriticalPairs<T, Comp>& critical_pairs) {
    CriticalPairs<T, Comp> selected;
    const auto min_degree = critical_pairs.GetSet().begin()->GetDegree();

    for (auto it = critical_pairs.GetSet().begin(); it != critical_pairs.GetSet().end(); ) {
        if (it->GetDegree() != min_degree) {
            break;
        }
        selected.insert(*it);
        it = critical_pairs.erase(it);
    }
    return selected;
}

template <typename T, typename Comp>
static void update(
        PolynomialSet<T, Comp>& old_poly_set,
        CriticalPairs<T, Comp>& old_crit_pairs,
        const Polynomial<T, Comp>& poly_to_insert) {
    CriticalPairs<T, Comp> all_crit;
    for (const auto& polynomial : old_poly_set.PolSet()) {
        all_crit.insert(CriticalPair(poly_to_insert, polynomial));
    }

    Monomial monomial_one;
    for (auto it = all_crit.GetSet().begin(); it != all_crit.GetSet().end(); ) {
        bool erased = false;
        if (gcd(poly_to_insert.LeadMonomial(), it->rightPolynomial().LeadMonomial()) != monomial_one) {
            for (auto jt = all_crit.GetSet().begin(); jt != all_crit.GetSet().end(); ++jt) {
                if (it == jt) {
                    continue;
                }

                if (lcm(poly_to_insert.LeadMonomial(), it->rightPolynomial().LeadMonomial()).IsDivisibleBy(lcm(poly_to_insert.LeadMonomial(), jt->rightPolynomial().LeadMonomial()))) {
                    it = all_crit.erase(it);
                    erased = true;
                    break;
                }
            }
        }
        if (!erased) {
            ++it;
        }
    }

    CriticalPairs<T, Comp> new_crit_pairs;
    for (auto it = all_crit.GetSet().begin(); it != all_crit.GetSet().end(); ++it) {
        if (gcd(poly_to_insert.LeadMonomial(), it->rightPolynomial().LeadMonomial()) != monomial_one) {
            new_crit_pairs.insert(*it);
        }
    }

    for (const auto& old_pair : old_crit_pairs.GetSet()) {
        if (!old_pair.Getlcm().IsDivisibleBy(poly_to_insert.LeadMonomial()) ||
            (old_pair.Getlcm() == lcm(old_pair.leftPolynomial().LeadMonomial(), poly_to_insert.LeadMonomial())) ||
            (old_pair.Getlcm() == lcm(old_pair.rightPolynomial().LeadMonomial(), poly_to_insert.LeadMonomial()))
        ) {
            new_crit_pairs.insert(old_pair);
        }
    }

    for (auto it = old_poly_set.PolSet().begin(); it != old_poly_set.PolSet().end(); ) {
        if (it->LeadMonomial().IsDivisibleBy(poly_to_insert.LeadMonomial())) {
            it = old_poly_set.RemovePolynomial(it);
        } else {
            ++it;
        }
    }

    old_poly_set.AddPolynomial(poly_to_insert);
    old_crit_pairs = std::move(new_crit_pairs);
}

template <typename T, typename Comp>
static Polynomial<T, Comp> simplify_and_multiplicate(
        const Monomial& monomial, const Polynomial<T, Comp>& polynomial,
        const ResultsTriangPairs<T, Comp>& results_triang_pairs) {
    const T value_type_one(1);
    const auto divisors = GetAllDivisors(monomial);

    for (const auto& divisor : divisors) {
        for (const auto& [result, triang] : results_triang_pairs) {
            const auto multiplicated = Term<T>(divisor, value_type_one) * polynomial;
            if (!result.IsPolynomialInMe(multiplicated)) {
                continue;
            }

            for (const auto& triang_polynomial : triang.PolSet()) {
                if (triang_polynomial.LeadMonomial() == multiplicated.LeadMonomial()) {
                    if (divisor.IsOne()) {
                        return Term<T>(monomial, value_type_one) * triang_polynomial;
                    } else if (divisor != monomial) {
                        return simplify_and_multiplicate(monomial / divisor, triang_polynomial, results_triang_pairs);
                    }
                    return triang_polynomial;
                }
            }
        }
    }
    return Term<T>(monomial, value_type_one) * polynomial;
}

template <typename T, typename Comp>
static std::pair<PolynomialSet<T, Comp>, typename Polynomial<T, Comp>::container>
sym_preproc(
        const CriticalPairs<T, Comp>& critical_pairs,
        const PolynomialSet<T, Comp>& poly_set,
        const ResultsTriangPairs<T, Comp>& results_triang_pairs) {
    const T value_type_one(1);

    PolynomialSet<T, Comp> to_reduce;
    for (const auto& critical_pair : critical_pairs.GetSet()) {
        to_reduce.AddPolynomial(
            simplify_and_multiplicate(critical_pair.leftMonomial(), critical_pair.leftPolynomial(), results_triang_pairs));
        to_reduce.AddPolynomial(
            simplify_and_multiplicate(critical_pair.rightMonomial(), critical_pair.rightPolynomial(), results_triang_pairs));
    }

    typename Polynomial<T, Comp>::container relative_complement;
    for (const auto& polynomial : to_reduce.PolSet()) {
        for (const auto& term : polynomial.TermSet()) {
            relative_complement.insert(Term<T>(term.monomial(), value_type_one));
        }
    }

    typename Polynomial<T, Comp>::container done_terms;
    for (const auto& critical_pair : critical_pairs.GetSet()) {
        Term<T> done_term(critical_pair.Getlcm(), value_type_one);
        done_terms.insert(done_term);
        relative_complement.erase(done_term);
    }

    while (!relative_complement.empty()) {
        const Term<T> current_term = *relative_complement.begin();
        done_terms.insert(current_term);
        relative_complement.erase(relative_complement.begin());

        for (const auto& polynomial : poly_set.PolSet()) {
            if (!current_term.IsDivisibleBy(polynomial.LeadTerm())) {
                continue;
            }

            const auto polynomial_to_add =
                simplify_and_multiplicate((current_term / polynomial.LeadTerm()).monomial(), polynomial, results_triang_pairs);
            to_reduce.AddPolynomial(polynomial_to_add);

            for (const auto& term : polynomial_to_add.TermSet()) {
                Term<T> term_to_add(term.monomial(), value_type_one);
                if (done_terms.find(term_to_add) == done_terms.end()) {
                    relative_complement.insert(term_to_add);
                }
            }
            break;
        }
    }

    return {to_reduce, done_terms};
}

template <typename T, typename Comp>
static PolynomialSet<T, Comp> reduction(
        const CriticalPairs<T, Comp>& critical_pairs,
        const PolynomialSet<T, Comp>& poly_set,
        ResultsTriangPairs<T, Comp>& results_triang_pairs) {
    auto [results, all_terms] = sym_preproc(critical_pairs, poly_set, results_triang_pairs);

    const T value_type_one(1);
    typename Polynomial<T, Comp>::container lead_terms;
    for (const auto& polynomial : results.PolSet()) {
        lead_terms.insert(Term<T>(polynomial.LeadMonomial(), value_type_one));
    }

    const auto [triang, reduced_results] = matrix_reduction(results, all_terms, lead_terms);
    results_triang_pairs.push_back({results, triang});
    return reduced_results;
}

template <typename T, typename Comp, typename SelFunction>
PolynomialSet<T, Comp>& calculated_fast_gb(PolynomialSet<T, Comp>& given_ideal, SelFunction select_function) {
    given_ideal = std::move(calculate_fast_gb(given_ideal, select_function));
    return given_ideal;
}

template <typename T, typename Comp, typename SelFunction>
PolynomialSet<T, Comp> calculate_fast_gb(const PolynomialSet<T, Comp>& given_ideal, SelFunction select_function) {
    PolynomialSet<T, Comp> groebner_basis;
    CriticalPairs<T, Comp> critical_pairs;
    for (const auto& polynomial : given_ideal.PolSet()) {
        update(groebner_basis, critical_pairs, polynomial);
    }

    ResultsTriangPairs<T, Comp> results_triang_pairs;
    results_triang_pairs.reserve(given_ideal.PolSet().size() * 2);
    while (!critical_pairs.empty()) {
        const auto selected_set = select_function(critical_pairs);
        const auto reduced_set = reduction(selected_set, groebner_basis, results_triang_pairs);
        for (const auto& res : reduced_set.PolSet()) {
            update(groebner_basis, critical_pairs, res);
        }
    }
    return groebner_basis;
}

template <typename T, typename Comp, typename SelFunction>
bool fast_is_gb(const PolynomialSet<T, Comp>& given_ideal, SelFunction select_function) {
    PolynomialSet<T, Comp> groebner_basis;
    CriticalPairs<T, Comp> critical_pairs;
    for (const auto& polynomial : given_ideal.PolSet()) {
        update(groebner_basis, critical_pairs, polynomial);
    }

    ResultsTriangPairs<T, Comp> results_triang_pairs;
    results_triang_pairs.reserve(given_ideal.PolSet().size() * 2);
    while (!critical_pairs.empty()) {
        const auto selected_set = select_function(critical_pairs);
        const auto reduced_set = reduction(selected_set, groebner_basis, results_triang_pairs);
        if (reduced_set.PolSet().size()) {
            return false;
        }
    }
    return true;
}


}  // namespace gb
