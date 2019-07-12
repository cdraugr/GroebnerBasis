#include "Polynomial.h"

template <typename Comp>
class PolynomialOrder {
public:
    template <typename OtherComp>
    bool operator()(const Polynomial<OtherComp>&, const Polynomial<OtherComp>&) const noexcept;
};

template <typename Comp>
template <typename OtherComp>
bool PolynomialOrder<Comp>::operator()(
    const Polynomial<OtherComp>& left,
    const Polynomial<OtherComp>& right
) const noexcept {
    Comp comparator;
    auto maximum = std::min(
        left.MonomialSet().size(),
        right.MonomialSet().size()
    );

    for (size_t i = 1; i <= maximum; ++i) {
        if (comparator(
                left.LeadMonom(static_cast<i32>(i)),
                right.LeadMonom(static_cast<i32>(i))
            ) ||
            comparator(
                right.LeadMonom(static_cast<i32>(i)),
                left.LeadMonom(static_cast<i32>(i)))
        ) {            
            return comparator(
                left.LeadMonom(static_cast<i32>(i)),
                right.LeadMonom(static_cast<i32>(i))
            );
        }
    }

    return left.MonomialSet().size() < right.MonomialSet().size();
}
