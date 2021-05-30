#pragma once

#include "PolynomialSet.h"

namespace gb {

template <typename T>
using Matrix =  std::vector<std::vector<T>>;

/* Declaration */

template <typename T, typename Comp>
Polynomial<T, Comp> row_to_polynomial(const std::vector<T>&, const typename Polynomial<T, Comp>::container&);

template <typename T, typename Comp>
std::pair<PolynomialSet<T, Comp>, PolynomialSet<T, Comp>>
matrix_reduction(
    const PolynomialSet<T, Comp>&,  // Polynomials to reduce.
    const typename Polynomial<T, Comp>::container&,  // Set of all terms.
    const typename Polynomial<T, Comp>::container&  // Set of all lead terms.
);

template <typename T>
static size_t column_unzero(const Matrix<T>&, size_t, size_t);

template <typename T>
static void triangulation(Matrix<T>&);

/* Realization */

template <typename T, typename Comp>
Polynomial<T, Comp> row_to_polynomial(const std::vector<T>& row, const typename Polynomial<T, Comp>::container& all_terms) {
    const T value_type_zero(0);
    typename Polynomial<T, Comp>::container polynomial;
    auto it = all_terms.begin();
    for (size_t i = 0; i != row.size(); ++i, ++it) {
        if (row[i] != value_type_zero) {
            polynomial.insert(Term<T>(it->monomial(), row[i]));
        }
    }
    return polynomial;
}

template <typename T, typename Comp>
std::pair<PolynomialSet<T, Comp>, PolynomialSet<T, Comp>> matrix_reduction (
        const PolynomialSet<T, Comp>& results,
        const typename Polynomial<T, Comp>::container& all_terms,
        const typename Polynomial<T, Comp>::container& lead_terms) {
    Matrix<T> matrix(results.PolSet().size(), std::vector<T>(all_terms.size()));
    size_t index = matrix.size() - 1;
    for (auto it = results.PolSet().begin(); it != results.PolSet().end(); ++it, --index) {
        size_t jndex = 0;
        auto poly_it = it->TermSet().begin();
        for (auto jt = all_terms.begin(); poly_it != it->TermSet().end(); ++jt, ++jndex) {
            if (poly_it->monomial() == jt->monomial()) {
                matrix[index][jndex] = poly_it->coefficient();
                ++poly_it;
            }
        }
    }

    triangulation(matrix);

    const T value_type_zero(0);
    PolynomialSet<T, Comp> reduced_results, triang;
    for (const auto& row : matrix) {
        const auto polynomial = row_to_polynomial<T, Comp>(row, all_terms);
        if (polynomial == Term<T>(0)) {
            break;
        }
        triang.AddPolynomial(polynomial);
        if (lead_terms.find(polynomial.LeadTerm()) == lead_terms.end()) {
            reduced_results.AddPolynomial(polynomial);
        }
    }

    return {triang, reduced_results};
}

template <typename T>
size_t column_unzero(
        const Matrix<T>& matrix,
        size_t curren_line,
        size_t current_column) {
    const T value_type_zero(0);
    for (size_t i = curren_line; i != matrix.size(); ++i) {
        if (matrix[i][current_column] != value_type_zero) {
           return i;
        }
    }
    return matrix.size();
}

template <typename T>
void triangulation(Matrix<T>& matrix) {
    const T value_type_zero(0), value_type_one(1);
    size_t current_column = 0;
    for (size_t i = 0; i != matrix.size() && current_column != matrix.front().size(); ++current_column) {
        size_t current_index = column_unzero(matrix, i, current_column);
        if (current_index == matrix.size()) {
            continue;
        }

        if (current_index != i) {
            matrix[i].swap(matrix[current_index]);
        }

        if (matrix[i][current_column] != value_type_one) {
            const T factor = matrix[i][current_column];
            for (size_t j = current_column; j != matrix[i].size(); ++j) {
                matrix[i][j] /= factor;
            }
        }

        for (size_t j = 0; j != matrix.size(); ++j) {
            if (j == i) {
                continue;
            }
            if (matrix[j][current_column] != value_type_zero) {
                const T factor = matrix[j][current_column];
                for (size_t k = current_column; k != matrix[j].size(); ++k) {
                    matrix[j][k] -= matrix[i][k] * factor;
                }
            }
        }
        ++i;
    }
}

}  // namespace gb
