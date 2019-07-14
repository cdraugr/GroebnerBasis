#include "Monomial.h"

namespace bg {
    class DegComp {
    public:
        bool operator()(const Monomial&, const Monomial&) const noexcept;
    };

    class LexComp {
    public:
        bool operator()(const Monomial&, const Monomial&) const noexcept;
    };

    class ReLexComp {
    public:
        bool operator()(const Monomial&, const Monomial&) const noexcept;
    };

    class CoefComp {
    public:
        bool operator()(const Monomial&, const Monomial&) const noexcept;
    };

    template <typename FComp, typename SComp>
    class CombineComp {
    public:
        bool operator()(const Monomial&, const Monomial&) const noexcept;
    };

    template <typename FComp, typename SComp>
    bool CombineComp<FComp, SComp>::operator()(
        const Monomial& left,
        const Monomial& right
    ) const noexcept {
        FComp first_comp;
        SComp second_comp;
        return !first_comp(left, right) && !first_comp(right, left) ?
            second_comp(left, right) :
            first_comp(left, right);
    }

    using DegLexComp = CombineComp<DegComp, LexComp>;
    using DegReLexComp = CombineComp<DegComp, ReLexComp>;
    using LexCoefComp = CombineComp<LexComp, CoefComp>;
}
