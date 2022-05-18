#pragma once

#include "Polynomial.hpp"
#include "Signature.hpp"

namespace gb {

template <typename T, typename Comp>
class LabeledPolynomial {
public:
    LabeledPolynomial();
    LabeledPolynomial(const Term&, const size_t&, const Polynomial<T, Comp>&);
    LabeledPolynomial(const size_t&, const Polynomial<T, Comp>&);

    const Term& GetTerm() const noexcept;
    const size_t& GetBasisIndex() const noexcept;
    const Signature<T, Comp>& GetSignature() const noexcept;
    std::pair<Term, size_t> GetPairSignature() const noexcept;
    const Polynomial<T, Comp>& GetEvaluation() const noexcept;

    void SetEvaluation(const Polynomial<T, Comp>&) noexcept;

    const Monomial<T>& LeadMonomial(const gb::i64& = 0) const;
    const Term& LeadTerm(const gb::i64& = 0) const;
    const T& LeadCoefficient(const gb::i64& = 0) const;

    template <typename OtherT, typename OtherComp>
    friend LabeledPolynomial<OtherT, OtherComp> operator*(const Term&, const LabeledPolynomial<OtherT, OtherComp>&);

private:
    Signature<T, Comp> signature_;
    Polynomial<T, Comp> evaluation_;
};

template <typename T, typename Comp>
LabeledPolynomial<T, Comp>::LabeledPolynomial() = default;

template <typename T, typename Comp>
LabeledPolynomial<T, Comp>::LabeledPolynomial(const Term& term, const size_t& index, const Polynomial<T, Comp>& evaluation) {
    signature_ = Signature<T, Comp>(term, index);
    evaluation_ = evaluation;
}

template <typename T, typename Comp>
LabeledPolynomial<T, Comp>::LabeledPolynomial(const size_t& index, const Polynomial<T, Comp>& evaluation) {
    signature_ = Signature<T, Comp>(index);
    evaluation_ = evaluation;
}

template <typename T, typename Comp>
const Term& LabeledPolynomial<T, Comp>::GetTerm() const noexcept {
    return GetSignature().GetTerm();
}

template <typename T, typename Comp>
const size_t& LabeledPolynomial<T, Comp>::GetBasisIndex() const noexcept {
    return GetSignature().GetBasisIndex();
}

template <typename T, typename Comp>
const Signature<T, Comp>& LabeledPolynomial<T, Comp>::GetSignature() const noexcept {
    return signature_;
}

template <typename T, typename Comp>
std::pair<Term, size_t> LabeledPolynomial<T, Comp>::GetPairSignature() const noexcept {
    return GetSignature().GetPairSignature();
}

template <typename T, typename Comp>
const Polynomial<T, Comp>& LabeledPolynomial<T, Comp>::GetEvaluation() const noexcept {
    return evaluation_;
}

template <typename T, typename Comp>
void LabeledPolynomial<T, Comp>::SetEvaluation(const Polynomial<T, Comp>& evaluation) noexcept {
    evaluation_ = evaluation;
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

template <typename T, typename Comp>
LabeledPolynomial<T, Comp> operator*(const Term& term, const LabeledPolynomial<T, Comp>& labeled_polynomial) {
    return LabeledPolynomial<T, Comp>(
        term * labeled_polynomial.GetTerm(),
        labeled_polynomial.GetBasisIndex(),
        Monomial<T>(term, static_cast<T>(1)) * labeled_polynomial.GetEvaluation()
    );
}

}  // namespace gb
