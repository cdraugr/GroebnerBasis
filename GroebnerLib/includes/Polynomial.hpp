#pragma once

#include "MonomialOrder.hpp"

namespace gb {

template <typename T, typename Comp = LexCoefComp>
class Polynomial {
public:
    using container = std::set<Monomial<T>, ReComp<Comp>>;

    Polynomial();
    Polynomial(Monomial<T>);
    Polynomial(const container&);

    template <typename OtherComp>
    Polynomial(const Polynomial<T, OtherComp>&);

    const container& GetMonomials() const noexcept;
    const Monomial<T>& LeadMonomial(const gb::i64& = 0) const;
    const Term& LeadTerm(const gb::i64& = 0) const;

    template <typename OtherT, typename OtherComp>
    friend gb::i64 deg(const Polynomial<OtherT, OtherComp>&) noexcept;

    bool TryReduceOnceBy(const Polynomial&) noexcept;  // Returns true if there was a reduction otherwise returns false.

    Polynomial operator-() const noexcept;
    Polynomial operator+() const noexcept;

    Polynomial& operator+=(const Polynomial&) noexcept;
    Polynomial& operator-=(const Polynomial&) noexcept;
    Polynomial& operator*=(const Polynomial&) noexcept;

    Polynomial& operator+=(const Monomial<T>&) noexcept;
    Polynomial& operator-=(const Monomial<T>&) noexcept;
    Polynomial& operator*=(const Monomial<T>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator+(Polynomial<OtherT, OtherComp>, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator-(Polynomial<OtherT, OtherComp>, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator*(Polynomial<OtherT, OtherComp>, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator+(const Monomial<OtherT>&, Polynomial<OtherT, OtherComp>) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator-(const Monomial<OtherT>&, Polynomial<OtherT, OtherComp>) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator*(const Monomial<OtherT>&, Polynomial<OtherT, OtherComp>) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator+(Polynomial<OtherT, OtherComp>, const Monomial<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator-(Polynomial<OtherT, OtherComp>, const Monomial<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> operator*(Polynomial<OtherT, OtherComp>, const Monomial<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> SPolynomial(const Polynomial<OtherT, OtherComp>&, const Polynomial<OtherT, OtherComp>&);

    template <typename OtherT, typename OtherComp>
    friend bool operator==(const Polynomial<OtherT, OtherComp>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator!=(const Polynomial<OtherT, OtherComp>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator==(const Polynomial<OtherT, OtherComp>&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator!=(const Polynomial<OtherT, OtherComp>&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator==(const Monomial<OtherT>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend bool operator!=(const Monomial<OtherT>&, const Polynomial<OtherT, OtherComp>&) noexcept;

    template <typename OtherT, typename OtherComp>
    friend Polynomial<OtherT, OtherComp> GiveRoot(const gb::i64&, const gb::i64&);

    template <typename OtherT, typename OtherComp>
    friend std::ostream& operator<<(std::ostream&, const Polynomial<OtherT, OtherComp>&) noexcept;

private:
    container monomials_{};
};

template <typename T, typename Comp>
Polynomial<T, Comp>::Polynomial() = default;

template <typename T, typename Comp>
Polynomial<T, Comp>::Polynomial(Monomial<T> monomial) {
    if (monomial != static_cast<T>(0)) {
        monomials_.insert(std::move(monomial));
    }
}

template <typename T, typename Comp>
Polynomial<T, Comp>::Polynomial(const typename Polynomial<T, Comp>::container& polynomial) {
    for (const auto& monomial : polynomial) {
        if (monomial != static_cast<T>(0)) {
            monomials_.insert(monomial);
        }
    }
}

template <typename T, typename Comp>
template <typename OtherComp>
Polynomial<T, Comp>::Polynomial(const Polynomial<T, OtherComp>& polynomial) {
    for (const auto& monomial : polynomial.GetMonomials()) {
        monomials_.insert(monomial);
    }
}

template <typename T, typename Comp>
const typename Polynomial<T, Comp>::container& Polynomial<T, Comp>::GetMonomials() const noexcept {
    return monomials_;
}

template <typename T, typename Comp>
const Monomial<T>& Polynomial<T, Comp>::LeadMonomial(const gb::i64& index) const {
    assert(0 <= index);  // Firstly check negative.
    assert(static_cast<size_t>(index) < GetMonomials().size());

    auto it = GetMonomials().begin();
    std::advance(it, index);
    return *it;
}

template <typename T, typename Comp>
const Term& Polynomial<T, Comp>::LeadTerm(const gb::i64& index) const {
    return LeadMonomial(index).GetTerm();
}

template <typename T, typename Comp>
gb::i64 deg(const Polynomial<T, Comp>& polynomial) noexcept {
    gb::i64 max_degree = -1;
    for (const auto& monomial : polynomial.GetMonomials()) {
        const auto current_degree = deg(monomial);
        if (current_degree > max_degree) {
            max_degree = current_degree;
        }
    }
    return max_degree;
}

template <typename T, typename Comp>
Polynomial<T, Comp> Polynomial<T, Comp>::operator-() const noexcept {
    Polynomial<T, Comp>::container monomials;
    for (const auto& monomial : GetMonomials()) {
        monomials.insert(-monomial);
    }
    return Polynomial(monomials);
}

template <typename T, typename Comp>
Polynomial<T, Comp> Polynomial<T, Comp>::operator+() const noexcept {
    return *this;
}

template <typename T, typename Comp>
bool Polynomial<T, Comp>::TryReduceOnceBy(const Polynomial<T, Comp>& other) noexcept {
    if (*this == Monomial<T>(0) || other == Monomial<T>(0)) {
        return false;
    }

    for (const auto& monomial : GetMonomials()) {
        if (monomial.IsDivisibleBy(other.LeadMonomial())) {
            *this -= Polynomial<T, Comp>(monomial / other.LeadMonomial()) * other;
            return true;
        }
    }
    return false;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator+=(const Polynomial<T, Comp>& polynomial) noexcept {
    for (const auto& monomial : polynomial.GetMonomials()) {
        *this += monomial;
    }

    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator-=(const Polynomial<T, Comp>& polynomial) noexcept {
    *this += -polynomial;
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator*=(const Polynomial<T, Comp>& polynomial) noexcept {
    Polynomial<T, Comp> answer;
    for (const auto& monomial : GetMonomials()) {
        answer += polynomial * monomial;
    }

    *this = std::move(answer);
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator+=(const Monomial<T>& monomial) noexcept {
    if (monomial == static_cast<T>(0)) {
        return *this;
    }
    for (const auto& current_monomial : GetMonomials()) {
        if (current_monomial.GetTerm() == monomial.GetTerm()) {
            auto count = current_monomial.GetCoefficient() + monomial.GetCoefficient();
            monomials_.erase(current_monomial);
            if (count != static_cast<T>(0)) {
                monomials_.insert(Monomial<T>(monomial.GetTerm(), count));
            }
            return *this;
        }
    }
    monomials_.insert(monomial);
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator-=(const Monomial<T>& monomial) noexcept {
    *this += -monomial;
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp>& Polynomial<T, Comp>::operator*=(const Monomial<T>& monomial) noexcept {
    Polynomial<T, Comp> answer;

    for (const auto& current_monomial : GetMonomials()) {
        answer += Polynomial<T, Comp>(monomial * current_monomial);
    }

    *this = std::move(answer);
    return *this;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator+(const Monomial<T>& monomial, Polynomial<T, Comp> polynomial) noexcept {
    polynomial += monomial;
    return polynomial;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator-(const Monomial<T>& monomial, Polynomial<T, Comp> polynomial) noexcept {
    polynomial -= monomial;
    return polynomial;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator*(const Monomial<T>& monomial, Polynomial<T, Comp> polynomial) noexcept {
    polynomial *= monomial;
    return polynomial;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator+(Polynomial<T, Comp> polynomial, const Monomial<T>& monomial) noexcept {
    polynomial += monomial;
    return polynomial;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator-(Polynomial<T, Comp> polynomial, const Monomial<T>& monomial) noexcept {
    polynomial -= monomial;
    return polynomial;
}

template <typename T, typename Comp>
Polynomial<T, Comp> operator*(Polynomial<T, Comp> polynomial, const Monomial<T>& monomial) noexcept {
    polynomial *= monomial;
    return polynomial;
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
    if (left == Monomial<T>(0) || right == Monomial<T>(0)) {
        throw std::runtime_error("No S-Polynomial from 0.");
    }

    auto lead_lcm = lcm(left.LeadMonomial(), right.LeadMonomial());
    auto m1 = lead_lcm / left.LeadMonomial();
    auto m2 = lead_lcm / right.LeadMonomial();
    return left * m1 - right * m2;
}

template <typename T, typename Comp>
bool operator==(const Polynomial<T, Comp>& left, const Polynomial<T, Comp>& right) noexcept {
    return left.GetMonomials() == right.GetMonomials();
}

template <typename T, typename Comp>
bool operator!=(const Polynomial<T, Comp>& left, const Polynomial<T, Comp>& right) noexcept {
    return !(left == right);
}

template <typename T, typename Comp>
bool operator==(const Polynomial<T, Comp>& polynomial, const Monomial<T>& monomial) noexcept {
    return monomial == static_cast<T>(0) ?
        polynomial.GetMonomials().size() == static_cast<size_t>(0) :
        polynomial.GetMonomials().size() == static_cast<size_t>(1) && polynomial.LeadMonomial() == monomial;
}

template <typename T, typename Comp>
bool operator!=(const Polynomial<T, Comp>& polynomial, const Monomial<T>& monomial) noexcept {
    return !(polynomial == monomial);
}

template <typename T, typename Comp>
bool operator==(const Monomial<T>& monomial, const Polynomial<T, Comp>& polynomial) noexcept {
    return polynomial == monomial;
}

template <typename T, typename Comp>
bool operator!=(const Monomial<T>& monomial, const Polynomial<T, Comp>& polynomial) noexcept {
    return !(polynomial == monomial);
}

template <typename T, typename Comp>
Polynomial<T, Comp> GiveRoot(const gb::i64& degree_max, const gb::i64& variable_count) {
    assert(degree_max >= 0);

    Polynomial<T, Comp> answer;
    auto all_combinations = utils::make_combinations(degree_max, variable_count);
    for (const auto& one_combination : all_combinations) {
        std::map<gb::i64, gb::i64> buffer_map;
        for (const auto& degree : one_combination) {
            buffer_map[degree] = 1;
        }
        answer += Monomial<T>(Term::term_from_map(buffer_map), 1);
    }
    return answer;
}

template <typename T, typename Comp>
std::ostream& operator<<(std::ostream& out, const Polynomial<T, Comp>& polynomial) noexcept {
    if (polynomial == Monomial<T>(0)) {
        return out << static_cast<T>(0);
    }

    for (const auto& monomial : polynomial.GetMonomials()) {
        if (monomial != polynomial.LeadMonomial() && monomial.GetCoefficient() > static_cast<T>(0)) {
            out << '+';
        }
        out << monomial;
    }
    return out;
}

}  // namespace gb
