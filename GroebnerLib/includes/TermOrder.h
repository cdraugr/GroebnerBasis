#include "Term.h"

namespace gb {
    class DegComp {
    public:
        template <typename T>
        bool operator()(const Term<T>&, const Term<T>&) const noexcept;
    };

    class LexComp {
    public:
        template <typename T>
        bool operator()(const Term<T>&, const Term<T>&) const noexcept;
    };

    class CoefComp {
    public:
        template <typename T>
        bool operator()(const Term<T>&, const Term<T>&) const noexcept;
    };

    template <typename Comp>
    class ReComp {
    public:
        template <typename T>
        bool operator()(const Term<T>&, const Term<T>&) const noexcept;
    };

    template <typename FComp, typename SComp>
    class CombineComp {
    public:
        template <typename T>
        bool operator()(const Term<T>&, const Term<T>&) const noexcept;
    };

    template <typename T>
    bool DegComp::operator()(const Term<T>& left, const Term<T>& right) const noexcept {
        return deg(left) < deg(right);
    }

    template <typename T>
    bool LexComp::operator()(const Term<T>& left, const Term<T>& right) const noexcept {
        i64 maximum = std::max(left.GetLastVariableIndex(), right.GetLastVariableIndex());
        for (i64 i = 0; i <= maximum; ++i) {
            if (left.GetDegree(i) != right.GetDegree(i)) {
                return left.GetDegree(i) < right.GetDegree(i);
            }
        }
        return false;
    }

    template <typename Comp>
    template <typename T>
    bool ReComp<Comp>::operator()(const Term<T>& left, const Term<T>& right) const noexcept {
        Comp comparator;
        return left == right ? false : !comparator(left, right);
    }

    template <typename T>
    bool CoefComp::operator()(const Term<T>& left, const Term<T>& right) const noexcept {
        return left.coefficient() < right.coefficient();
    }

    template <typename FComp, typename SComp>
    template <typename T>
    bool CombineComp<FComp, SComp>::operator()(
        const Term<T>& left,
        const Term<T>& right
    ) const noexcept {
        FComp first_comp;
        SComp second_comp;
        return !first_comp(left, right) && !first_comp(right, left) ?
            second_comp(left, right) :
            first_comp(left, right);
    }

    using ReLexComp = ReComp<LexComp>;
    using DegLexComp = CombineComp<DegComp, LexComp>;
    using DegReLexComp = CombineComp<DegComp, ReLexComp>;
    using LexCoefComp = CombineComp<LexComp, CoefComp>;
    using ReLexCoefComp = CombineComp<ReLexComp, CoefComp>;
}
