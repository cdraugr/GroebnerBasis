#pragma once

#include "MatrixReduction.h"
#include "CriticalPairs.h"

namespace gb {

/* Declaration */

template <typename T, typename Comp>
CriticalPairs<T, Comp> normal_select(CriticalPairs<T, Comp>&);

template <typename T, typename Comp>
static std::pair<PolynomialSet<T, Comp>, typename Polynomial<T, Comp>::container>
sym_preproc(const CriticalPairs<T, Comp>&, const PolynomialSet<T, Comp>&);

template <typename T, typename Comp>
static PolynomialSet<T, Comp>
reduction(const CriticalPairs<T, Comp>&, const PolynomialSet<T, Comp>&);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
PolynomialSet<T, Comp>& calculated_fast_gb(PolynomialSet<T, Comp>&, SelFunction = normal_select);

template <typename T, typename Comp, typename SelFunction = decltype(normal_select<T, Comp>)>
PolynomialSet<T, Comp>
calculate_fast_gb(const PolynomialSet<T, Comp>&, SelFunction = normal_select);

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
static std::pair<PolynomialSet<T, Comp>, typename Polynomial<T, Comp>::container>
sym_preproc(
        const CriticalPairs<T, Comp>& critical_pairs,
        const PolynomialSet<T, Comp>& poly_set) {
    const T value_type_one(1);

    PolynomialSet<T, Comp> to_reduce;
    for (const auto& critical_pair : critical_pairs.GetSet()) {
        to_reduce.AddPolynomial(critical_pair.leftPolynomial() *
                                Term<T>(critical_pair.leftMonomial(), value_type_one));
        to_reduce.AddPolynomial(critical_pair.rightPolynomial() *
                                Term<T>(critical_pair.rightMonomial(), value_type_one));
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

            const auto polynomial_to_add = polynomial * (current_term / polynomial.LeadTerm());
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
        const PolynomialSet<T, Comp>& poly_set) {
    auto [results, all_terms] = sym_preproc(critical_pairs, poly_set);

    const T value_type_one(1);
    typename Polynomial<T, Comp>::container lead_terms;
    for (const auto& polynomial : results.PolSet()) {
        lead_terms.insert(Term<T>(polynomial.LeadTerm().monomial(), value_type_one));
    }

    return matrix_reduction(results, all_terms, lead_terms);
}

template <typename T, typename Comp, typename SelFunction>
PolynomialSet<T, Comp>& calculated_fast_gb(
        PolynomialSet<T, Comp>& groebner_basis,
        SelFunction select_function) {
    CriticalPairs<T, Comp> critical_pairs(groebner_basis);

    while (!critical_pairs.empty()) {
        const auto selected_set = select_function(critical_pairs);
        const auto reduced_set = reduction(selected_set, groebner_basis);
        for (const auto& res : reduced_set.PolSet()) {
            for (const auto& basis_polynomial : groebner_basis.PolSet()) {
                critical_pairs.insert(CriticalPair(res, basis_polynomial));
            }
            groebner_basis.AddPolynomial(res);
        }
    }
    return groebner_basis;
}

template <typename T, typename Comp, typename SelFunction>
PolynomialSet<T, Comp> calculate_fast_gb(
        const PolynomialSet<T, Comp>& poly_set,
        SelFunction select_function) {
    auto groebner_basis = poly_set;
    return calculated_fast_gb(groebner_basis, select_function);
}

}  // namespace gb
