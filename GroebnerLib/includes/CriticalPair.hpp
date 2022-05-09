#pragma once

#include "PolynomialSet.hpp"

namespace gb {

template <typename T, typename Comp = LexCoefComp>
class CriticalPair {
public:
    using side_pair = std::pair<Term, Polynomial<T, Comp>>;

    explicit CriticalPair();
    explicit CriticalPair(const Polynomial<T, Comp>&, const Polynomial<T, Comp>&);

    gb::i64 GetDegree() const noexcept;
    const Term& GetLcm() const noexcept;

    const side_pair& Left() const noexcept;
    const side_pair& Right() const noexcept;

    const Polynomial<T, Comp>& GetLeftPolynomial() const noexcept;
    const Polynomial<T, Comp>& GetRightPolynomial() const noexcept;

    const Term& GetLeftTerm() const noexcept;
    const Term& GetRightTerm() const noexcept;

    friend bool operator<(const CriticalPair& left, const CriticalPair& right) noexcept {
        PolynomialOrder<LexCoefComp> polynomial_comparator;
        return left.GetDegree() != right.GetDegree() ? left.GetDegree() < right.GetDegree() :
                polynomial_comparator(left.GetLeftPolynomial(), right.GetLeftPolynomial()) ||
                polynomial_comparator(left.GetRightPolynomial(), right.GetRightPolynomial());
    }

private:
    gb::i64 degree_{};
    Term lcm_{};
    side_pair left_{};
    side_pair right_{};
};

template <typename T, typename Comp>
CriticalPair<T, Comp>::CriticalPair() = default;

template <typename T, typename Comp>
CriticalPair<T, Comp>::CriticalPair(
        const Polynomial<T, Comp>& left_polynomial,
        const Polynomial<T, Comp>& right_polynomial) {
    lcm_ = lcm(left_polynomial.LeadTerm(), right_polynomial.LeadTerm());
    degree_ = deg(lcm_);

    left_.first = lcm_ / left_polynomial.LeadTerm();
    left_.second = left_polynomial;

    right_.first = lcm_ / right_polynomial.LeadTerm();
    right_.second = right_polynomial;
}

template <typename T, typename Comp>
gb::i64 CriticalPair<T, Comp>::GetDegree() const noexcept {
    return degree_;
}

template <typename T, typename Comp>
const Term& CriticalPair<T, Comp>::GetLcm() const noexcept {
    return lcm_;
}

template <typename T, typename Comp>
const typename CriticalPair<T, Comp>::side_pair& CriticalPair<T, Comp>::Left() const noexcept {
    return left_;
}

template <typename T, typename Comp>
const typename CriticalPair<T, Comp>::side_pair& CriticalPair<T, Comp>::Right() const noexcept {
    return right_;
}

template <typename T, typename Comp>
const Polynomial<T, Comp>& CriticalPair<T, Comp>::GetLeftPolynomial() const noexcept {
    return Left().second;
}

template <typename T, typename Comp>
const Polynomial<T, Comp>& CriticalPair<T, Comp>::GetRightPolynomial() const noexcept {
    return Right().second;
}

template <typename T, typename Comp>
const Term& CriticalPair<T, Comp>::GetLeftTerm() const noexcept {
    return Left().first;
}

template <typename T, typename Comp>
const Term& CriticalPair<T, Comp>::GetRightTerm() const noexcept {
    return Right().first;
}

template <typename T, typename Comp>
std::ostream& operator<<(std::ostream& out, const CriticalPair<T, Comp>& critical_pair) {
    out << "(" << critical_pair.GetLcm();
    out << ", " << critical_pair.GetLeftTerm() << ", " << critical_pair.GetLeftPolynomial();
    out << ", " << critical_pair.GetRightTerm() << ", " << critical_pair.GetRightPolynomial();
    return out << ')';
}

}  // namespace gb
