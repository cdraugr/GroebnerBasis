#pragma once

#include "PolynomialSet.hpp"

namespace gb {
namespace matrix_reduction {

template <typename T>
using Row = std::vector<T>;

template <typename T>
using Matrix = std::vector<Row<T>>;

/* Declaration */

template <typename T, typename Comp>
Polynomial<T, Comp> row_to_polynomial_(const Row<T>&, const typename Polynomial<T, Comp>::container&);

template <typename T>
size_t column_unzero_(const Matrix<T>&, size_t, size_t);

template <typename T>
void triangulation_(Matrix<T>&);

template <typename T, typename Comp>
std::pair<PolynomialSet<T, Comp>, PolynomialSet<T, Comp>>
matrix_reduction(
    const PolynomialSet<T, Comp>& to_reduce,
    const typename Polynomial<T, Comp>::container& all_monomials,
    const typename Polynomial<T, Comp>::container& lead_monomials
);

/* Implementation */

template <typename T, typename Comp>
Polynomial<T, Comp> row_to_polynomial_(const Row<T>& row, const typename Polynomial<T, Comp>::container& all_monomials) {
    const T value_type_zero(0);
    typename Polynomial<T, Comp>::container polynomial;
    auto it = all_monomials.begin();
    for (size_t i = 0; i != row.size(); ++i, ++it) {
        if (row[i] != value_type_zero) {
            polynomial.insert(Monomial<T>(it->GetTerm(), row[i]));
        }
    }
    return polynomial;
}

template <typename T>
size_t column_unzero_(const Matrix<T>& matrix, size_t curren_line, size_t current_column) {
    const T value_type_zero(0);
    for (size_t i = curren_line; i != matrix.size(); ++i) {
        if (matrix[i][current_column] != value_type_zero) {
           return i;
        }
    }
    return matrix.size();
}

template <typename T>
void triangulation_(Matrix<T>& matrix) {
    const T value_type_zero(0), value_type_one(1);
    size_t current_column = 0, i = 0;
    while (i != matrix.size() && current_column != matrix.front().size()) {
        size_t current_index = column_unzero_(matrix, i, current_column);
        if (current_index == matrix.size()) {
            ++current_column;
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
        ++current_column;
        ++i;
    }
}

template <typename T, typename Comp>
std::pair<PolynomialSet<T, Comp>, PolynomialSet<T, Comp>> matrix_reduction(
        const PolynomialSet<T, Comp>& to_reduce,
        const typename Polynomial<T, Comp>::container& all_monomials,
        const typename Polynomial<T, Comp>::container& lead_monomials) {
    Matrix<T> matrix(to_reduce.GetPolynomials().size(), Row<T>(all_monomials.size()));
    size_t index = matrix.size() - 1;
    for (auto it = to_reduce.GetPolynomials().begin(); it != to_reduce.GetPolynomials().end(); ++it, --index) {
        size_t jndex = 0;
        auto monomial_it = it->GetMonomials().begin();
        for (auto jt = all_monomials.begin(); monomial_it != it->GetMonomials().end(); ++jt, ++jndex) {
            if (monomial_it->GetTerm() == jt->GetTerm()) {
                matrix[index][jndex] = monomial_it->GetCoefficient();
                ++monomial_it;
            }
        }
    }

    triangulation_(matrix);

    const T value_type_zero(0);
    PolynomialSet<T, Comp> reduced_results, triang;
    for (const auto& row : matrix) {
        const auto polynomial = row_to_polynomial_<T, Comp>(row, all_monomials);
        if (polynomial == Monomial<T>(0)) {
            break;
        }
        triang.AddPolynomial(polynomial);
        if (lead_monomials.find(polynomial.LeadMonomial()) == lead_monomials.end()) {
            reduced_results.AddPolynomial(polynomial);
        }
    }

    return {triang, reduced_results};
}

}  // namespace matrix_reduction
}  // namespace gb
