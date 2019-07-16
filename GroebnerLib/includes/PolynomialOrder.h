#include "Polynomial.h"

namespace gb {
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
        i32 maximum = std::min(left.MonomialSet().size(), right.MonomialSet().size());
        for (i32 i = 1; i <= maximum; ++i) {
            if (comparator(left.LeadMonom(i), right.LeadMonom(i)) ||
                comparator(right.LeadMonom(i), left.LeadMonom(i))) {            
                return comparator(left.LeadMonom(i), right.LeadMonom(i));
            }
        }

        return left.MonomialSet().size() < right.MonomialSet().size();
    }
}
