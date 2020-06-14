#pragma once

#include "Polynomial.h"

namespace gb {

template <typename Comp>
class PolynomialOrder {
public:
    template <typename T, typename OtherComp>
    bool operator()(const Polynomial<T, OtherComp>&, const Polynomial<T, OtherComp>&) const noexcept;
};

template <typename Comp>
template <typename T, typename OtherComp>
bool PolynomialOrder<Comp>::operator()(
    const Polynomial<T, OtherComp>& left,
    const Polynomial<T, OtherComp>& right
) const noexcept {
    Comp comparator;
    auto left_it = left.TermSet().begin();
    auto right_it = right.TermSet().begin();
    for (; left_it != left.TermSet().end() && right_it != right.TermSet().end(); ++left_it, ++right_it) {
        if (comparator(*left_it, *right_it) || comparator(*right_it, *left_it)) {
            return comparator(*left_it, *right_it);
        }
    }

    return left.TermSet().size() < right.TermSet().size();
}

}  // namespace gb
