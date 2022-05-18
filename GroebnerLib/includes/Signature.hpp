#pragma once

#include "Term.hpp"

namespace gb {

template <typename T, typename Comp>
class Signature {
public:
    Signature();
    Signature(const Term&, const size_t&);
    Signature(const size_t&);

    const Term& GetTerm() const noexcept;
    const size_t& GetBasisIndex() const noexcept;
    std::pair<Term, size_t> GetPairSignature() const noexcept;

    template <typename OtherT, typename OtherComp>
    friend Signature<OtherT, OtherComp> operator*(const Term&, const Signature<OtherT, OtherComp>&);

    friend bool operator<(const Signature& left, const Signature& right) noexcept {
        Comp comparator;
        return left.GetBasisIndex() > right.GetBasisIndex() ||
            (
                left.GetBasisIndex() == right.GetBasisIndex() &&
                comparator(Monomial<T>(left.GetTerm(), static_cast<T>(1)), Monomial<T>(right.GetTerm(), static_cast<T>(1)))
            );
    }

    friend bool operator==(const Signature& left, const Signature& right) noexcept {
        return left.GetTerm() == right.GetTerm() && left.GetBasisIndex() == right.GetBasisIndex();
    }

    friend bool operator!=(const Signature& left, const Signature& right) noexcept {
        return !(left == right);
    }

private:
    Term term_;
    size_t index_{};
};

template <typename T, typename Comp>
Signature<T, Comp>::Signature() = default;

template <typename T, typename Comp>
Signature<T, Comp>::Signature(const Term& term, const size_t& index) {
    term_ = term;
    index_ = index;
}

template <typename T, typename Comp>
Signature<T, Comp>::Signature(const size_t& index) {
    index_ = index;
}

template <typename T, typename Comp>
const Term& Signature<T, Comp>::GetTerm() const noexcept {
    return term_;
}

template <typename T, typename Comp>
const size_t& Signature<T, Comp>::GetBasisIndex() const noexcept {
    return index_;
}

template <typename T, typename Comp>
std::pair<Term, size_t> Signature<T, Comp>::GetPairSignature() const noexcept {
    return {GetTerm(), GetBasisIndex()};
}

template <typename T, typename Comp>
Signature<T, Comp> operator*(const Term& term, const Signature<T, Comp>& signature) {
    return Signature<T, Comp>(term * signature.GetTerm(), signature.GetBasisIndex());
}

} // namespace gb
