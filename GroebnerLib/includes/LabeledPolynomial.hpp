#pragma once

#include "Polynomial.hpp"

namespace gb {

template <typename T, typename Comp>
class LabeledPolynomial {
public:
    using signature = std::pair<Term, size_t>;

    LabeledPolynomial();
    LabeledPolynomial(const Term&, const size_t&, const Polynomial<T, Comp>&);
    LabeledPolynomial(const size_t&, const Polynomial<T, Comp>&);

    const Term& GetTerm() const noexcept;
    const size_t& GetBasisIndex() const noexcept;
    signature GetSignature() const noexcept;
    const Polynomial<T, Comp>& GetEvaluation() const noexcept;

    const Monomial<T>& LeadMonomial(const gb::i64& = 0) const;
    const Term& LeadTerm(const gb::i64& = 0) const;
    const T& LeadCoefficient(const gb::i64& = 0) const;

private:
    Term term_;
    size_t index_{};
    Polynomial<T, Comp> evaluation_;
};

template <typename T, typename Comp>
LabeledPolynomial<T, Comp>::LabeledPolynomial() = default;

template <typename T, typename Comp>
LabeledPolynomial<T, Comp>::LabeledPolynomial(const Term& term, const size_t& index, const Polynomial<T, Comp>& evaluation) {
    term_ = term;
    index_ = index;
    evaluation_ = evaluation;
}

template <typename T, typename Comp>
LabeledPolynomial<T, Comp>::LabeledPolynomial(const size_t& index, const Polynomial<T, Comp>& evaluation) {
    index_ = index;
    evaluation_ = evaluation;
}

template <typename T, typename Comp>
const Term& LabeledPolynomial<T, Comp>::GetTerm() const noexcept {
    return term_;
}

template <typename T, typename Comp>
const size_t& LabeledPolynomial<T, Comp>::GetBasisIndex() const noexcept {
    return index_;
}

template <typename T, typename Comp>
std::pair<Term, size_t> LabeledPolynomial<T, Comp>::GetSignature() const noexcept {
    return {GetTerm(), GetBasisIndex()};
}

template <typename T, typename Comp>
const Polynomial<T, Comp>& LabeledPolynomial<T, Comp>::GetEvaluation() const noexcept {
    return evaluation_;
}

template <typename T, typename Comp>
const Monomial<T>& LabeledPolynomial<T, Comp>::LeadMonomial(const gb::i64& index) const {
    return GetEvaluation().LeadMonomial(index);
}

template <typename T, typename Comp>
const Term& LabeledPolynomial<T, Comp>::LeadTerm(const gb::i64& index) const {
    return LeadMonomial(index).GetTerm();
}

template <typename T, typename Comp>
const T& LabeledPolynomial<T, Comp>::LeadCoefficient(const gb::i64& index) const {
    return LeadMonomial(index).GetCoefficient();
}

}  // namespace gb
