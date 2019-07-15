#include <algorithm>
#include "../includes/MonomialOrder.h"

namespace gb {
    bool DegComp::operator()(const Monomial& left, const Monomial& right) const noexcept {
        return left == right ? false : deg(left) < deg(right);
    }

    bool LexComp::operator()(const Monomial& left, const Monomial& right) const noexcept {
        if (left == right) {
            return false;
        } else if (left.degrees().empty()) {
                return true;
        } else if (right.degrees().empty()) {
            return false;
        }

        i32 maximum = std::max(
            (left.degrees().crbegin())->first,
            (right.degrees().crbegin())->first
        );
        for (i32 i = 0; i <= maximum; ++i) {
            if (left.GetDegree(i) != right.GetDegree(i)) {
                return left.GetDegree(i) < right.GetDegree(i);
            }
        }
        return false;
    }

    bool ReLexComp::operator()(const Monomial& left, const Monomial& right) const noexcept {
        LexComp lex_comp;
        return left == right ? false : !lex_comp(left, right);
    }

    bool CoefComp::operator()(const Monomial& left, const Monomial& right) const noexcept {
        return left.coefficient() < right.coefficient();
    }
}
