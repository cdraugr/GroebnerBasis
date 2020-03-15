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
    i64 min_max_index = std::min(left.TermSet().size(), right.TermSet().size());
    for (i64 i = 0; i != min_max_index; ++i) {
        if (comparator(left.LeadTerm(i), right.LeadTerm(i)) ||
            comparator(right.LeadTerm(i), left.LeadTerm(i))) {
            return comparator(left.LeadTerm(i), right.LeadTerm(i));
        }
    }

    return left.TermSet().size() < right.TermSet().size();
}

}  // namespace gb
