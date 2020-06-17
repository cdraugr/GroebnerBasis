#pragma once

#include "PolynomialSet.h"

namespace gb {

template <typename T, typename Comp = LexCoefComp>
class CriticalPair {
public:
    using side_pair = std::pair<Monomial, Polynomial<T, Comp>>;

    explicit CriticalPair();
    explicit CriticalPair(const Polynomial<T, Comp>&, const Polynomial<T, Comp>&);

    i64 GetDegree() const noexcept;
    const Monomial& Getlcm() const noexcept;

    const side_pair& Left() const noexcept;
    const side_pair& Right() const noexcept;

    const Polynomial<T, Comp>& leftPolynomial() const noexcept;
    const Polynomial<T, Comp>& rightPolynomial() const noexcept;

    const Monomial& leftMonomial() const noexcept;
    const Monomial& rightMonomial() const noexcept;

    friend bool operator<(const CriticalPair& left, const CriticalPair& right) noexcept {
        PolynomialOrder<LexCoefComp> poly_comparator;
        return left.GetDegree() != right.GetDegree() ? left.GetDegree() < right.GetDegree() :
                poly_comparator(left.leftPolynomial(), right.leftPolynomial()) ||
                poly_comparator(left.rightPolynomial(), right.rightPolynomial());
    }

private:
    i64 degree_{};
    Monomial lcm_{};
    side_pair left_{};
    side_pair right_{};
};

template <typename T, typename Comp>
CriticalPair<T, Comp>::CriticalPair() = default;

template <typename T, typename Comp>
CriticalPair<T, Comp>::CriticalPair(
        const Polynomial<T, Comp>& left_polynomial,
        const Polynomial<T, Comp>& right_polynomial) {
    lcm_ = lcm(left_polynomial.LeadMonomial(), right_polynomial.LeadMonomial());
    degree_ = deg(lcm_);

    left_.first = lcm_ / left_polynomial.LeadMonomial();
    left_.second = left_polynomial;

    right_.first = lcm_ / right_polynomial.LeadMonomial();
    right_.second = right_polynomial;
}

template <typename T, typename Comp>
i64 CriticalPair<T, Comp>::GetDegree() const noexcept {
    return degree_;
}

template <typename T, typename Comp>
const Monomial& CriticalPair<T, Comp>::Getlcm() const noexcept {
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
const Polynomial<T, Comp>& CriticalPair<T, Comp>::leftPolynomial() const noexcept {
    return Left().second;
}

template <typename T, typename Comp>
const Polynomial<T, Comp>& CriticalPair<T, Comp>::rightPolynomial() const noexcept {
    return Right().second;
}

template <typename T, typename Comp>
const Monomial& CriticalPair<T, Comp>::leftMonomial() const noexcept {
    return Left().first;
}

template <typename T, typename Comp>
const Monomial& CriticalPair<T, Comp>::rightMonomial() const noexcept {
    return Right().first;
}

template <typename T, typename Comp>
std::ostream& operator<<(std::ostream& out, const CriticalPair<T, Comp>& critical_pair) {
    out << "(" << critical_pair.Getlcm();
    out << ", " << critical_pair.leftMonomial() << ", " << critical_pair.leftPolynomial();
    out << ", " << critical_pair.rightMonomial() << ", " << critical_pair.rightPolynomial();
    return out << ')';
}

}  // namespace gb
