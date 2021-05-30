#pragma once

#include "PolynomialSet.h"

namespace gb {

template <typename T, typename Comp>
PolynomialSet<T, Comp>
matrix_reduction(
    const PolynomialSet<T, Comp>&,  // Polynomials to reduce.
    const typename Polynomial<T, Comp>::container&,  // Set of all terms.
    const typename Polynomial<T, Comp>::container&  // Set of all lead terms.
);

// #define VECTOR_MAP

#ifdef VECTOR_MAP

/* Declaration */

template <typename T>
static size_t column_unzero(const std::vector<std::map<size_t, T>>&, size_t, size_t);

template <typename T>
static void triangulation(std::vector<std::map<size_t, T>>& matrix);

/* Realization */

template <typename T, typename Comp>
PolynomialSet<T, Comp> matrix_reduction(
        const PolynomialSet<T, Comp>& results,
        const typename Polynomial<T, Comp>::container& all_terms,
        const typename Polynomial<T, Comp>::container& lead_terms) {
    std::vector<std::map<size_t, T>> matrix(results.PolSet().size());
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

    triangulation(matrix, all_terms.size());

    const T value_type_zero(0), value_type_one(1);
    PolynomialSet<T, Comp> reduced_results;
    for (const auto& row : matrix) {
        if (row.empty()) {
            break;
        }
        typename Polynomial<T, Comp>::container polynomial;
        auto it = all_terms.begin();
        bool is_first = true;
        size_t last_index = 0;
        for (const auto& [index, coefficient] : row) {
            std::advance(it, index - last_index);
            last_index = index;
            if (is_first) {
                if (lead_terms.find(Term<T>(it->monomial(), value_type_one)) != lead_terms.end()) {
                    break;
                }
                is_first = false;
            }
            polynomial.insert(Term<T>(it->monomial(), coefficient));
        }
        reduced_results.AddPolynomial(polynomial);
    }

    return reduced_results;
}

template <typename T>
static size_t column_unzero(
        const std::vector<std::map<size_t, T>>& matrix,
        size_t curren_line,
        size_t current_column) {
    const T value_type_zero(0);
    for (size_t i = curren_line; i != matrix.size(); ++i) {
        if (matrix[i].find(current_column) != matrix[i].end()) {
           return i;
        }
    }
    return matrix.size();
}

template <typename T>
static void triangulation(
        std::vector<std::map<size_t, T>>& matrix,
        size_t column_count) {
    const T value_type_zero(0), value_type_one(1);
    size_t current_column = 0;
    for (size_t i = 0; i != matrix.size() && current_column != column_count; ++current_column) {
        size_t current_index = column_unzero(matrix, i, current_column);
        if (current_index == matrix.size()) {
            continue;
        }

        if (current_index != i) {
            matrix[i].swap(matrix[current_index]);
        }

        if (matrix[i][current_column] != value_type_one) {
            const T divider = matrix[i][current_column];
            for (auto& [index, coefficient] : matrix[i]) {
                coefficient /= divider;
            }
        }

        for (size_t j = 0; j != matrix.size(); ++j) {
            if (j == i) {
                continue;
            }
            const auto it = matrix[j].find(current_column);
            if (it == matrix[j].end()) {
                continue;
            }

            const T factor = it->second;
            for (const auto& [index, coefficient] : matrix[i]) {
                const T res = matrix[j][index] - coefficient * factor;
                if (res == value_type_zero) {
                    matrix[j].erase(index);
                } else {
                    matrix[j][index] = res;
                }
            }
        }
        ++i;
    }
}

#else

/* Declaration */

template <typename T>
static size_t column_unzero(const std::vector<std::vector<size_t>>&, size_t);

template <typename T>
static void triangulation(std::vector<std::vector<T>>& matrix);

/* Realization */

template <typename T, typename Comp>
PolynomialSet<T, Comp> matrix_reduction (
        const PolynomialSet<T, Comp>& results,
        const typename Polynomial<T, Comp>::container& all_terms,
        const typename Polynomial<T, Comp>::container& lead_terms) {
    std::vector<std::vector<T>> matrix(results.PolSet().size(), std::vector<T>(all_terms.size()));
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

    const T value_type_zero(0), value_type_one(1);
    PolynomialSet<T, Comp> reduced_results;
    for (const auto& row : matrix) {
        typename Polynomial<T, Comp>::container polynomial;
        auto it = all_terms.begin();
        bool is_first = true, is_all_zeros = true;
        for (const auto& coefficient : row) {
            if (coefficient == value_type_zero) {
                ++it;
                continue;
            }
            is_all_zeros = false;

            if (is_first) {
                if (lead_terms.find(Term<T>(it->monomial(), value_type_one)) != lead_terms.end()) {
                    break;
                }
                is_first = false;
            }

            polynomial.insert(Term<T>(it->monomial(), coefficient));
            ++it;
        }
        if (is_all_zeros) {
            break;
        }
        reduced_results.AddPolynomial(polynomial);
    }

    return reduced_results;
}

template <typename T>
size_t column_unzero(
        const std::vector<std::vector<T>>& matrix,
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
void triangulation(std::vector<std::vector<T>>& matrix) {
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

#endif

}  // namespace gb
