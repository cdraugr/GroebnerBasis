#pragma once

#include "PolynomialOrder.hpp"

namespace gb {

template <typename T, typename Comp = LexCoefComp>
class PolynomialSet {
public:
    using container = std::set<Polynomial<T, Comp>, PolynomialOrder<LexCoefComp>>;
    using iterator = typename container::iterator;

    PolynomialSet();
    PolynomialSet(const Polynomial<T, Comp>&);
    PolynomialSet(const container&);

    template <typename OtherComp>
    PolynomialSet(const PolynomialSet<T, OtherComp>&);

    const container& GetPolynomials() const noexcept;
    const Polynomial<T, Comp>& LeadPolynomial(const gb::i64& = 0) const;

    bool OneReductionByMe(Polynomial<T, Comp>*) const noexcept;  // Сhanging given Polynomial.
    bool ReductionToResByMe(Polynomial<T, Comp>*) const noexcept;  // Changing given Polynomial.
    // Returns true if there was a reduction otherwise returns false.

    typename container::iterator AddPolynomial(const Polynomial<T, Comp>&) noexcept;
    void RemovePolynomial(const Polynomial<T, Comp>&);
    iterator RemovePolynomial(iterator);

    PolynomialSet<T, Comp>& MakeGroebnerBasis() noexcept;
    void ReduceCoefficients();
    PolynomialSet<T, Comp>& ReduceBasis();

    bool IsPolynomialInMe(const Polynomial<T, Comp>&) const noexcept;
    bool IsPolynomialInMyIdeal(const Polynomial<T, Comp>&) const noexcept;

    template <typename OtherT, typename OtherComp>
    friend std::list<Polynomial<OtherT, OtherComp>> AllSPolynomials(const PolynomialSet<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool IsGroebnerBasis(const PolynomialSet<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend PolynomialSet<OtherT, OtherComp> GiveRootSet(const gb::i64&);

    template <typename OtherT, typename OtherComp>
    friend PolynomialSet<OtherT, OtherComp> GiveGroebnerRootSet(const gb::i64&);

    template <typename OtherT, typename OtherComp>
    friend std::ostream& operator<<(std::ostream&, const PolynomialSet<OtherT, OtherComp>&) noexcept;

private:
    container polynomials_{};
};

template <typename T, typename Comp>
PolynomialSet<T, Comp>::PolynomialSet() = default;

template <typename T, typename Comp>
PolynomialSet<T, Comp>::PolynomialSet(const Polynomial<T, Comp>& polynomial) {
    AddPolynomial(polynomial);
}

template <typename T, typename Comp>
PolynomialSet<T, Comp>::PolynomialSet(const PolynomialSet<T, Comp>::container& polynomial_set) {
    for (const auto& polynomial : polynomial_set) {
        AddPolynomial(polynomial);
    }
}

template <typename T, typename Comp>
template <typename OtherComp>
PolynomialSet<T, Comp>::PolynomialSet(const PolynomialSet<T, OtherComp>& polynomial_set) {
    for (const auto& polynomial : polynomial_set.GetPolynomials()) {
        AddPolynomial(polynomial);
    }
}


template <typename T, typename Comp>
const typename PolynomialSet<T, Comp>::container& PolynomialSet<T, Comp>::GetPolynomials() const noexcept {
    return polynomials_;
}

template <typename T, typename Comp>
const Polynomial<T, Comp>& PolynomialSet<T, Comp>::LeadPolynomial(const gb::i64& index) const {
    assert(0 <= index);  // Firstly check negative.
    assert(static_cast<size_t>(index) < GetPolynomials().size());

    auto it = GetPolynomials().begin();
    std::advance(it, index);
    return *it;
}

template <typename T, typename Comp>
bool PolynomialSet<T, Comp>::OneReductionByMe(Polynomial<T, Comp> *polynomial) const noexcept {
    bool was_changed = false;
    for (const auto& polynomial_reducer : GetPolynomials()) {
        while (polynomial->TryReduceOnceBy(polynomial_reducer)) {  // 'polynomial' is changing here.
            was_changed = true;
        }
    }
    return was_changed;
}

template <typename T, typename Comp>
bool PolynomialSet<T, Comp>::ReductionToResByMe(Polynomial<T, Comp> *polynomial) const noexcept {
    bool was_changed = false;
    while (OneReductionByMe(polynomial)) {  // 'polynomial' is changing here.
        was_changed = true;
    }
    return was_changed;
}

template <typename T, typename Comp>
typename PolynomialSet<T, Comp>::container::iterator
PolynomialSet<T, Comp>::AddPolynomial(const Polynomial<T, Comp>& polynomial) noexcept {
    if (polynomial != Monomial<T>(0)) {
        return polynomials_.insert(polynomial).first;
    }
    return GetPolynomials().end();
}

template <typename T, typename Comp>
void PolynomialSet<T, Comp>::RemovePolynomial(const Polynomial<T, Comp>& polynomial) {
    polynomials_.erase(polynomial);
}

template <typename T, typename Comp>
typename PolynomialSet<T, Comp>::iterator
PolynomialSet<T, Comp>::RemovePolynomial(
        typename PolynomialSet<T, Comp>::iterator polynomial) {
    return polynomials_.erase(polynomial);
}

template <typename T, typename Comp>
std::list<Polynomial<T, Comp>> AllSPolynomials(const PolynomialSet<T, Comp>& polynomial_set) noexcept {
    PolynomialOrder<LexCoefComp> comparator;
    std::list<Polynomial<T, Comp>> s_polynomials;
    for (const auto& polynomial_f : polynomial_set.GetPolynomials()) {
        for (const auto& polynomial_g : polynomial_set.GetPolynomials()) {
            if (comparator(polynomial_f, polynomial_g) && polynomial_f != polynomial_g) {
                s_polynomials.push_back(SPolynomial(polynomial_f, polynomial_g));
            }
        }
    }
    return s_polynomials;
}

template <typename T, typename Comp>
PolynomialSet<T, Comp>& PolynomialSet<T, Comp>::MakeGroebnerBasis() noexcept {
    auto s_polynomials = AllSPolynomials(*this);
    for (auto& s_polynomial : s_polynomials) {
        ReductionToResByMe(&s_polynomial);
        if (s_polynomial != Monomial<T>(0)) {
            for (const auto& polynomial : GetPolynomials()) {
                s_polynomials.push_back(SPolynomial(polynomial, s_polynomial));
            }
            AddPolynomial(s_polynomial);
        }
    }
    return *this;
}

template <typename T, typename Comp>
void PolynomialSet<T, Comp>::ReduceCoefficients() {
    PolynomialSet<T, Comp>::container tmp;
    for (const auto& polynomial : GetPolynomials()) {
        tmp.insert(polynomial * Monomial<T>(pow(polynomial.LeadMonomial().GetCoefficient(), -1)));
    }
    polynomials_ = std::move(tmp);
}

template <typename T, typename Comp>
PolynomialSet<T, Comp>& PolynomialSet<T, Comp>::ReduceBasis() {
    PolynomialSet<T, Comp> tmp;
    while (!polynomials_.empty()) {
        auto polynomial = *GetPolynomials().begin();
        polynomials_.erase(GetPolynomials().begin());
        while (ReductionToResByMe(&polynomial) || tmp.ReductionToResByMe(&polynomial)) {}
        if (polynomial != Monomial<T>(0)) {
            tmp.polynomials_.insert(polynomial * Monomial<T>(pow(polynomial.LeadMonomial().GetCoefficient(), -1)));
        }  // I don't use AddPolynomial here for small uptimisation.
    }
    *this = std::move(tmp);
    return *this;
}

template <typename T, typename Comp>
bool PolynomialSet<T, Comp>::IsPolynomialInMe(const Polynomial<T, Comp>& polynomial) const noexcept {
    return GetPolynomials().find(polynomial) != GetPolynomials().end();
}


template <typename T, typename Comp>
bool PolynomialSet<T, Comp>::IsPolynomialInMyIdeal(const Polynomial<T, Comp>& polynomial) const noexcept {
    auto ideal = *this;
    auto tmp = polynomial;
    ideal.MakeGroebnerBasis().ReductionToResByMe(&tmp);
    return tmp == Monomial<T>(0);
}

template <typename T, typename Comp>
bool IsGroebnerBasis(const PolynomialSet<T, Comp>& polynomial_set) noexcept {
    PolynomialOrder<LexCoefComp> comparator;
    for (const auto& polynomial_f : polynomial_set.GetPolynomials()) {
        for (const auto& polynomial_g : polynomial_set.GetPolynomials()) {
            if (comparator(polynomial_f, polynomial_g) || polynomial_f == polynomial_g) {
                continue;
            }
            auto s_polynomial = SPolynomial(polynomial_f, polynomial_g);
            polynomial_set.ReductionToResByMe(&s_polynomial);
            if (s_polynomial != Monomial<T>(0)) {
                return false;
            }
        }
    }
    return true;
}

template <typename T, typename Comp>
PolynomialSet<T, Comp> GiveRootSet(const gb::i64& variable_count) {
    PolynomialSet<T, Comp> answer(GiveRoot<T, Comp>(variable_count, variable_count) - Monomial<T>(pow(static_cast<T>(-1), variable_count - 1)));
    for (gb::i64 i = 1; i < variable_count; ++i) {
        answer.AddPolynomial(GiveRoot<T, Comp>(i, variable_count));
    }
    return answer;
}

template <typename T, typename Comp>
PolynomialSet<T, Comp> GiveGroebnerRootSet(const gb::i64& variable_count) {
    return GiveRootSet<T, Comp>(variable_count).MakeGroebnerBasis().ReduceBasis();
}

template <typename T, typename Comp>
std::ostream& operator<<(std::ostream& out, const PolynomialSet<T, Comp>& polynomial_set) noexcept {
    for (auto it = polynomial_set.GetPolynomials().begin(); it != polynomial_set.GetPolynomials().end(); ++it) {
        if (it != polynomial_set.GetPolynomials().begin()) {
            out << "\n";
        }
        out << *it;
    }
    return out;
}

}  // namespace gb
