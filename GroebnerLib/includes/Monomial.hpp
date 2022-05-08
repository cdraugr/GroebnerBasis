#pragma once

#include "Rational.hpp"
#include "Modular.hpp"
#include "Term.hpp"

namespace gb {

template <typename T>
class Monomial {
public:
    using type_name = T;

    Monomial();
    Monomial(const type_name&);
    Monomial(const Term&, const type_name&);

    const type_name& GetCoefficient() const noexcept;
    const Term& GetTerm() const noexcept;

    gb::i64 GetDegree(const gb::i64&) const noexcept;
    bool IsInteger() const noexcept;
    bool IsDivisibleBy(const Monomial&) const noexcept;
    gb::i64 GetLastVariableIndex() const noexcept;

    Monomial<T> operator+() const noexcept;
    Monomial<T> operator-() const noexcept;

    Monomial<T>& operator*=(const Monomial<T>&) noexcept;
    Monomial<T>& operator/=(const Monomial<T>&);

    Monomial<T>& operator*=(const type_name&) noexcept;
    Monomial<T>& operator/=(const type_name&);

    template <typename OtherT>
    friend Monomial<OtherT> operator*(Monomial<OtherT>, const typename Monomial<OtherT>::type_name&) noexcept;

    template <typename OtherT>
    friend Monomial<OtherT> operator/(Monomial<OtherT>, const typename Monomial<OtherT>::type_name&);

    template <typename OtherT>
    friend Monomial<OtherT> operator*(const typename Monomial<OtherT>::type_name&, Monomial<OtherT>) noexcept;

    template <typename OtherT>
    friend Monomial<OtherT> operator/(const typename Monomial<OtherT>::type_name&, Monomial<OtherT>);

    template <typename OtherT>
    friend Monomial<OtherT> operator*(Monomial<OtherT>, const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend Monomial<OtherT> operator/(Monomial<OtherT>, const Monomial<OtherT>&);

    template <typename OtherT>
    friend gb::i64 deg(const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend bool operator==(const Monomial<OtherT>&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend bool operator!=(const Monomial<OtherT>&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend bool operator==(const Monomial<OtherT>&, const typename Monomial<OtherT>::type_name&) noexcept;

    template <typename OtherT>
    friend bool operator!=(const Monomial<OtherT>&, const typename Monomial<OtherT>::type_name&) noexcept;

    template <typename OtherT>
    friend bool operator==(const typename Monomial<OtherT>::type_name&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend bool operator!=(const typename Monomial<OtherT>::type_name&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend Monomial<OtherT> gcd(const Monomial<OtherT>&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend Monomial<OtherT> lcm(const Monomial<OtherT>&, const Monomial<OtherT>&) noexcept;

    template <typename OtherT>
    friend std::ostream& operator<<(std::ostream&, const Monomial<OtherT>&) noexcept;

private:
    void Reduce_() noexcept;

    type_name coefficient_{};
    Term term_{};
};

template <typename T>
Monomial<T>::Monomial() = default;

template <typename T>
Monomial<T>::Monomial(const Monomial<T>::type_name& coefficient)
    : coefficient_{coefficient} {}

template <typename T>
Monomial<T>::Monomial(const Term& monomial, const Monomial<T>::type_name& coefficient)
    : coefficient_{coefficient}, term_{monomial} {
        Reduce_();
    }

template <typename T>
const typename Monomial<T>::type_name& Monomial<T>::GetCoefficient() const noexcept {
    return coefficient_;
}

template <typename T>
const Term& Monomial<T>::GetTerm() const noexcept {
    return term_;
}

template <typename T>
gb::i64 Monomial<T>::GetDegree(const gb::i64& index) const noexcept {
    return GetTerm().GetDegree(index);
}

template <typename T>
bool Monomial<T>::IsInteger() const noexcept {
    return GetTerm().IsOne();
}

template <typename T>
bool Monomial<T>::IsDivisibleBy(const Monomial<T>& other) const noexcept {
    return other.GetCoefficient() != static_cast<T>(0) && GetTerm().IsDivisibleBy(other.GetTerm());
}

template <typename T>
gb::i64 Monomial<T>::GetLastVariableIndex() const noexcept {
    return GetTerm().GetLastVariableIndex();
}

template <typename T>
Monomial<T> Monomial<T>::operator+() const noexcept {
    return *this;
}

template <typename T>
Monomial<T> Monomial<T>::operator-() const noexcept {
    return Monomial<T>(GetTerm(), -GetCoefficient());
}

template <typename T>
Monomial<T>& Monomial<T>::operator*=(const Monomial<T>& other) noexcept {
    coefficient_ *= other.GetCoefficient();
    term_ *= other.GetTerm();
    Reduce_();
    return *this;
}

template <typename T>
Monomial<T>& Monomial<T>::operator/=(const Monomial<T>& other) {
    coefficient_ /= other.GetCoefficient();
    term_ /= other.GetTerm();
    return *this;
}

template <typename T>
Monomial<T>& Monomial<T>::operator*=(const typename Monomial<T>::type_name& type_elem) noexcept {
    coefficient_ *= type_elem;
    Reduce_();
    return *this;
}

template <typename T>
Monomial<T>& Monomial<T>::operator/=(const typename Monomial<T>::type_name& type_elem) {
    coefficient_ /= type_elem;
    return *this;
}

template <typename T>
Monomial<T> operator*(Monomial<T> monomial, const typename Monomial<T>::type_name& type_elem) noexcept {
    monomial *= type_elem;
    return monomial;
}

template <typename T>
Monomial<T> operator/(Monomial<T> monomial, const typename Monomial<T>::type_name& type_elem) {
    monomial /= type_elem;
    return monomial;
}

template <typename T>
Monomial<T> operator*(const typename Monomial<T>::type_name& type_elem, Monomial<T> monomial) noexcept {
    monomial *= type_elem;
    return monomial;
}

template <typename T>
Monomial<T> operator/(const typename Monomial<T>::type_name& type_elem, Monomial<T> monomial) {
    monomial /= type_elem;
    return monomial;
}

template <typename T>
Monomial<T> operator*(Monomial<T> left, const Monomial<T>& right) noexcept {
    left *= right;
    return left;
}

template <typename T>
Monomial<T> operator/(Monomial<T> left, const Monomial<T>& right) {
    left /= right;
    return left;
}

template <typename T>
gb::i64 deg(const Monomial<T>& monomial) noexcept {
    return deg(monomial.GetTerm());
}

template <typename T>
bool operator==(const Monomial<T>& left, const Monomial<T>& right) noexcept {
    return left.GetCoefficient() == right.GetCoefficient() && left.GetTerm() == right.GetTerm();
}

template <typename T>
bool operator!=(const Monomial<T>& left, const Monomial<T>& right) noexcept {
    return !(left == right);
}

template <typename T>
bool operator==(const Monomial<T>& monomial, const typename Monomial<T>::type_name& type_elem) noexcept {
    return monomial.GetCoefficient() == type_elem && monomial.IsInteger();
}

template <typename T>
bool operator!=(const Monomial<T>& term, const typename Monomial<T>::type_name& type_elem) noexcept {
    return !(term == type_elem);
}

template <typename T>
bool operator==(const typename Monomial<T>::type_name& type_elem, const Monomial<T>& term) noexcept {
    return term == type_elem;
}

template <typename T>
bool operator!=(const typename Monomial<T>::type_name& type_elem, const Monomial<T>& term) noexcept {
    return !(term == type_elem);
}

template <typename T>
Monomial<T> gcd(const Monomial<T>& left, const Monomial<T>& right) noexcept {
    return Monomial<T>(gcd(left.GetTerm(), right.GetTerm()), 1);
}

template <typename T>
Monomial<T> lcm(const Monomial<T>& left, const Monomial<T>& right) noexcept {
    return Monomial<T>(lcm(left.GetTerm(), right.GetTerm()), left.GetCoefficient() * right.GetCoefficient());
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Monomial<T>& monomial) noexcept {
    if (monomial.IsInteger()) {
        return out << monomial.GetCoefficient();
    }

    if (monomial.GetCoefficient() == static_cast<T>(-1) && monomial.GetCoefficient() < static_cast<T>(0)) {
        out << '-';
    } else if (monomial.GetCoefficient() != static_cast<T>(1)) {
        out << monomial.GetCoefficient() << '*';
    }

    return out << monomial.GetTerm();
}

template <typename T>
void Monomial<T>::Reduce_() noexcept {  // private
    if (GetCoefficient() == static_cast<T>(0)) {
        term_ = Term();
    }
}

}  // namespace gb
