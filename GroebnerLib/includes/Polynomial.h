#pragma once

#include "TermOrder.h"

namespace gb {

template <typename T, typename Comp = LexCoefComp>
class Polynomial {
public:
    using container = std::set<Term<T>, ReComp<Comp>>;

    Polynomial();
    Polynomial(Term<T>);
    Polynomial(const container&);

    template <typename OtherComp>
    Polynomial(const Polynomial<T, OtherComp>&);

    const container& TermSet() const noexcept;
    const Term<T>& LeadTerm(const i64& = 0) const;

    template <typename OtherT, typename OtherComp>
    friend i64 deg(const Polynomial<OtherT, OtherComp>&) noexcept;

    bool TryReduceOnceBy(const Polynomial&) noexcept;  // Returns true if there was a reduction otherwise returns false.

    Polynomial operator-() const noexcept;
    Polynomial operator+() const noexcept;

    Polynomial& operator+=(const Polynomial&) noexcept;
    Polynomial& operator-=(const Polynomial&) noexcept;
    Polynomial& operator*=(const Polynomial&) noexcept;

    Polynomial& operator+=(const Term<T>&) noexcept;
    Polynomial& operator-=(const Term<T>&) noexcept;
    Polynomial& operator*=(const Term<T>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator+(Polynomial<OtherT, OtherComp>, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator-(Polynomial<OtherT, OtherComp>, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator*(Polynomial<OtherT, OtherComp>, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator+(const Term<OtherT>&, Polynomial<OtherT, OtherComp>) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator-(const Term<OtherT>&, Polynomial<OtherT, OtherComp>) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator*(const Term<OtherT>&, Polynomial<OtherT, OtherComp>) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator+(Polynomial<OtherT, OtherComp>, const Term<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator-(Polynomial<OtherT, OtherComp>, const Term<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator*(Polynomial<OtherT, OtherComp>, const Term<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> SPolynomial(const Polynomial<OtherT, OtherComp>&, const Polynomial<OtherT, OtherComp>&);

    template <typename OtherT, typename OtherComp>
    friend bool operator==(const Polynomial<OtherT, OtherComp>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator!=(const Polynomial<OtherT, OtherComp>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator==(const Polynomial<OtherT, OtherComp>&, const Term<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator!=(const Polynomial<OtherT, OtherComp>&, const Term<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator==(const Term<OtherT>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator!=(const Term<OtherT>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> GiveSigma(const i64&, const i64&);

    template <typename OtherT, typename OtherComp>
    friend std::ostream& operator<<(std::ostream&, const Polynomial<OtherT, OtherComp>&) noexcept;

private:
    container terms_{};
};

template <typename T, typename Comp>
Polynomial<T, Comp>::Polynomial() = default;

template <typename T, typename Comp>
Polynomial<T, Comp>::Polynomial(Term<T> term) {
    if (term != static_cast<T>(0)) {
        terms_.insert(std::move(term));
    }
}

template <typename T, typename Comp>
Polynomial<T, Comp>::Polynomial(const typename Polynomial<T, Comp>::container& polynom) {
    for (const auto& term : polynom) {
        if (term != static_cast<T>(0)) {
            terms_.insert(term);
        }
    }
}

template <typename T, typename Comp>
template <typename OtherComp>
Polynomial<T, Comp>::Polynomial(const Polynomial<T, OtherComp>& polynom) {
    for (const auto& term : polynom.TermSet()) {
        terms_.insert(term);
    }
}

template <typename T, typename Comp>
const typename Polynomial<T, Comp>::container& Polynomial<T, Comp>::TermSet() const noexcept {
    return terms_;
}

template <typename T, typename Comp>
const Term<T>& Polynomial<T, Comp>::LeadTerm(const i64& index) const {
    assert(0 <= index);  // Firstly check negative.
    assert(static_cast<size_t>(index) < TermSet().size());

    auto it = TermSet().begin();
    std::advance(it, index);
    return *it;
}

template <typename T, typename Comp>
i64 deg(const Polynomial<T, Comp>& polynom) noexcept {
    i64 max_degree = -1;
    for (const auto& term : polynom.TermSet()) {
        const auto current_degree = deg(term);
        if (current_degree > max_degree) {
            max_degree = current_degree;
        }
    }
    return max_degree;
}

template <typename T, typename Comp>
Polynomial<T, Comp> Polynomial<T, Comp>::operator-() const noexcept {
    Polynomial<T, Comp>::container terms;
    for (auto& term : TermSet()) {
        terms.insert(-term);
    }
    return Polynomial(terms);
}

template <typename T, typename Comp>
Polynomial<T, Comp> Polynomial<T, Comp>::operator+() const noexcept {
    return *this;
}

template <typename T, typename Comp>
bool Polynomial<T, Comp>::TryReduceOnceBy(const Polynomial<T, Comp>& other) noexcept {
    if (*this == Term<T>(0) || other == Term<T>(0)) {
        return false;
    }

    for (const auto& term : TermSet()) {
        if (term.IsDivisibleBy(other.LeadTerm())) {
            *this -= Polynomial<T, Comp>(term / other.LeadTerm()) * other;
            return true;
        }
    }
    return false;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator+=(const Polynomial<T, Comp>& polynom) noexcept {
    for (const auto& term : polynom.TermSet()) {
        *this += term;
    }

    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator-=(const Polynomial<T, Comp>& polynom) noexcept {
    *this += -polynom;
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator*=(const Polynomial<T, Comp>& polynom) noexcept {
    Polynomial<T, Comp> answer;
    for (const auto& term : TermSet()) {
        answer += polynom * term;
    }

    *this = std::move(answer);
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator+=(const Term<T>& term) noexcept {
    if (term == static_cast<T>(0)) {
        return *this;
    }
    for (const auto& this_term : TermSet()) {
        if (this_term.monom() == term.monom()) {
            auto count = this_term.coefficient() + term.coefficient();
            terms_.erase(this_term);
            if (count != static_cast<T>(0)) {
                terms_.insert(Term<T>(term.monom(), count));
            }
            return *this;
        }
    }
    terms_.insert(term);
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator-=(const Term<T>& term) noexcept {
    *this += -term;
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator*=(const Term<T>& term) noexcept {
    Polynomial<T, Comp> answer;

    for (const auto& other_term : TermSet()) {
        answer += Polynomial<T, Comp>(term * other_term);
    }

    *this = std::move(answer);
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator+(const Term<T>& term, Polynomial<T, Comp> polynom) noexcept {
    polynom += term;
    return polynom;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator-(const Term<T>& term, Polynomial<T, Comp> polynom) noexcept {
    polynom -= term;
    return polynom;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator*(const Term<T>& term, Polynomial<T, Comp> polynom) noexcept {
    polynom *= term;
    return polynom;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator+(Polynomial<T, Comp> polynom, const Term<T>& term) noexcept {
    polynom += term;
    return polynom;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator-(Polynomial<T, Comp> polynom, const Term<T>& term) noexcept {
    polynom -= term;
    return polynom;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator*(Polynomial<T, Comp> polynom, const Term<T>& term) noexcept {
    polynom *= term;
    return polynom;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator+(Polynomial<T, Comp> left, const Polynomial<T, Comp>& right) noexcept {
    left += right;
    return left;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator-(Polynomial<T, Comp> left, const Polynomial<T, Comp>& right) noexcept {
    left -= right;
    return left;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator*(Polynomial<T, Comp> left, const Polynomial<T, Comp>& right) noexcept {
    left *= right;
    return left;
}

template <typename T, typename Comp>
Polynomial<T, Comp> SPolynomial(const Polynomial<T, Comp>& left, const Polynomial<T, Comp>& right) {
    if (left == Term<T>(0) || right == Term<T>(0)) {
        throw std::runtime_error("No S-Polynomial from 0.");
    }

    auto lead_lcm = lcm(left.LeadTerm(), right.LeadTerm());
    auto m1 = lead_lcm / left.LeadTerm();
    auto m2 = lead_lcm / right.LeadTerm();
    return left * m1 - right * m2;
}

template <typename T, typename Comp>
bool operator==(const Polynomial<T, Comp>& left, const Polynomial<T, Comp>& right) noexcept {
    return left.TermSet() == right.TermSet();
}

template <typename T, typename Comp>
bool operator!=(const Polynomial<T, Comp>& left, const Polynomial<T, Comp>& right) noexcept {
    return !(left == right);
}

template <typename T, typename Comp>
bool operator==(const Polynomial<T, Comp>& polynom, const Term<T>& term) noexcept {
    return term == static_cast<T>(0) ?
        polynom.TermSet().size() == static_cast<size_t>(0) :
        polynom.TermSet().size() == static_cast<size_t>(1) && polynom.LeadTerm() == term;
}

template <typename T, typename Comp>
bool operator!=(const Polynomial<T, Comp>& polynom, const Term<T>& term) noexcept {
    return !(polynom == term);
}

template <typename T, typename Comp>
bool operator==(const Term<T>& term, const Polynomial<T, Comp>& polynom) noexcept {
    return polynom == term;
}

template <typename T, typename Comp>
bool operator!=(const Term<T>& term, const Polynomial<T, Comp>& polynom) noexcept {
    return !(polynom == term);
}

template <typename T, typename Comp>
Polynomial<T, Comp> GiveSigma(const i64& degree_max, const i64& variable_count) {
    assert(degree_max >= 0);

    Polynomial<T, Comp> answer;
    auto all_combinations = make_combinations(degree_max, variable_count);
    for (const auto& one_combination : all_combinations) {
        std::map<i64, i64> buffer_map;
        for (const auto& degree : one_combination) {
            buffer_map[degree] = 1;
        }
        answer += Term<T>(Monomial(buffer_map), 1);
    }
    return answer;
}

template <typename T, typename Comp>
std::ostream& operator<<(std::ostream& out, const Polynomial<T, Comp>& polynom) noexcept {
    if (polynom == Term<T>(0)) {
        return out << static_cast<T>(0);
    }

    for (const auto& term : polynom.TermSet()) {
        if (term != polynom.LeadTerm() && term.coefficient() > 0) {
            out << '+';
        }
        out << term;
    }
    return out;
}

}  // namespace gb
