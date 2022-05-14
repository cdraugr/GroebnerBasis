#pragma once

#include "F5Calculation.hpp"

namespace gb {

/* Declaration */

template <typename T, typename Comp>
PolynomialSet<T, Comp>& inplace_calculate_f5_gb(PolynomialSet<T, Comp>&);

template <typename T, typename Comp>
PolynomialSet<T, Comp> calculate_f5_gb(const PolynomialSet<T, Comp>&);

/* Implementation */

template <typename T, typename Comp>
PolynomialSet<T, Comp>& inplace_calculate_f5_gb(PolynomialSet<T, Comp>& given_set) {
    given_set = calculate_f5_gb(given_set);
    return given_set;
}

template <typename T, typename Comp>
PolynomialSet<T, Comp> calculate_f5_gb(const PolynomialSet<T, Comp>& given_set) {
    F5Calculation f5_evaluator(given_set);
    return f5_evaluator.CalculateBasis();
}

}  // namespace gb
