#pragma once

#include "Modular.h"
#include "Monomial.h"
#include "Rational.h"

namespace gb {
    template <typename T>
    class Term {
    public:
        using type_name = T;

        Term();
        Term(const type_name&);
        Term(const Monomial&, const type_name&);

        const type_name& coefficient() const noexcept;
        const Monomial& monom() const noexcept;

        i64 GetDegree(const i64&) const noexcept;
        bool IsInteger() const noexcept;
        bool IsDivisibleBy(const Term&) const noexcept;
        i64 GetLastVariableIndex() const noexcept;

        Term<T> operator+() const noexcept;
        Term<T> operator-() const noexcept;

        Term<T>& operator*=(const Term<T>&) noexcept;
        Term<T>& operator/=(const Term<T>&);

        Term<T>& operator*=(const type_name&) noexcept;
        Term<T>& operator/=(const type_name&);

        template <typename OtherT>
        friend Term<OtherT> operator*(Term<OtherT>, const typename Term<OtherT>::type_name&) noexcept;

        template <typename OtherT>
        friend Term<OtherT> operator/(Term<OtherT>, const typename Term<OtherT>::type_name&);

        template <typename OtherT>
        friend Term<OtherT> operator*(const typename Term<OtherT>::type_name&, Term<OtherT>) noexcept;

        template <typename OtherT>
        friend Term<OtherT> operator/(const typename Term<OtherT>::type_name&, Term<OtherT>);

        template <typename OtherT>
        friend Term<OtherT> operator*(Term<OtherT>, const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend Term<OtherT> operator/(Term<OtherT>, const Term<OtherT>&);

        template <typename OtherT>
        friend i64 deg(const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend bool operator==(const Term<OtherT>&, const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend bool operator!=(const Term<OtherT>&, const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend bool operator==(const Term<OtherT>&, const typename Term<OtherT>::type_name&) noexcept;

        template <typename OtherT>
        friend bool operator!=(const Term<OtherT>&, const typename Term<OtherT>::type_name&) noexcept;

        template <typename OtherT>
        friend bool operator==(const typename Term<OtherT>::type_name&, const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend bool operator!=(const typename Term<OtherT>::type_name&, const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend Term<OtherT> gcd(const Term<OtherT>&, const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend Term<OtherT> lcm(const Term<OtherT>&, const Term<OtherT>&) noexcept;

        template <typename OtherT>
        friend std::ostream& operator<<(std::ostream&, const Term<OtherT>&) noexcept;

    private:
        void Reduce() noexcept;

        type_name coefficient_{};
        Monomial monom_{};
    };

    template <typename T>
    Term<T>::Term() = default;

    template <typename T>
    Term<T>::Term(const Term<T>::type_name& coefficient)
        : coefficient_{coefficient} {}

    template <typename T>
    Term<T>::Term(const Monomial& monom, const Term<T>::type_name& coefficient)
        : coefficient_{coefficient}, monom_{monom} {
            Reduce();
        }

    template <typename T>
    const typename Term<T>::type_name& Term<T>::coefficient() const noexcept {
        return coefficient_;
    }

    template <typename T>
    const Monomial& Term<T>::monom() const noexcept {
        return monom_;
    }

    template <typename T>
    i64 Term<T>::GetDegree(const i64& index) const noexcept {
        return monom().GetDegree(index);
    }

    template <typename T>
    bool Term<T>::IsInteger() const noexcept {
        return monom().IsOne();
    }

    template <typename T>
    bool Term<T>::IsDivisibleBy(const Term<T>& other) const noexcept {
        return other.coefficient() != static_cast<T>(0) && monom().IsDivisibleBy(other.monom());
    }

    template <typename T>
    i64 Term<T>::GetLastVariableIndex() const noexcept {
        return monom().GetLastVariableIndex();
    }

    template <typename T>
    Term<T> Term<T>::operator+() const noexcept {
        return Term<T>(monom(), coefficient());
    }

    template <typename T>
    Term<T> Term<T>::operator-() const noexcept {
        return Term<T>(monom(), -coefficient());
    }

    template <typename T>
    Term<T>& Term<T>::operator*=(const Term<T>& other) noexcept {
        coefficient_ *= other.coefficient();
        monom_ *= other.monom();
        Reduce();
        return *this;
    }

    template <typename T>
    Term<T>& Term<T>::operator/=(const Term<T>& other) {
        coefficient_ /= other.coefficient();
        monom_ /= other.monom();
        return *this;
    }

    template <typename T>
    Term<T>& Term<T>::operator*=(const typename Term<T>::type_name& type_elem) noexcept {
        coefficient_ *= type_elem;
        Reduce();
        return *this;
    }

    template <typename T>
    Term<T>& Term<T>::operator/=(const typename Term<T>::type_name& type_elem) {
        coefficient_ /= type_elem;
        return *this;
    }

    template <typename T>
    Term<T> operator*(Term<T> term, const typename Term<T>::type_name& type_elem) noexcept {
        term *= type_elem;
        return term;
    }

    template <typename T>
    Term<T> operator/(Term<T> term, const typename Term<T>::type_name& type_elem) {
        term /= type_elem;
        return term;
    }

    template <typename T>
    Term<T> operator*(const typename Term<T>::type_name& type_elem, Term<T> term) noexcept {
        term *= type_elem;
        return term;
    }

    template <typename T>
    Term<T> operator/(const typename Term<T>::type_name& type_elem, Term<T> term) {
        term /= type_elem;
        return term;
    }

    template <typename T>
    Term<T> operator*(Term<T> left, const Term<T>& right) noexcept {
        left *= right;
        return left;
    }

    template <typename T>
    Term<T> operator/(Term<T> left, const Term<T>& right) {
        left /= right;
        return left;
    }

    template <typename T>
    i64 deg(const Term<T>& term) noexcept {
        return deg(term.monom());
    }

    template <typename T>
    bool operator==(const Term<T>& left, const Term<T>& right) noexcept {
        return left.coefficient() == right.coefficient() && left.monom() == right.monom();
    }

    template <typename T>
    bool operator!=(const Term<T>& left, const Term<T>& right) noexcept {
        return !(left == right);
    }

    template <typename T>
    bool operator==(const Term<T>& term, const typename Term<T>::type_name& type_elem) noexcept {
        return term.coefficient() == type_elem && term.IsInteger();
    }

    template <typename T>
    bool operator!=(const Term<T>& term, const typename Term<T>::type_name& type_elem) noexcept {
        return !(term == type_elem);
    }

    template <typename T>
    bool operator==(const typename Term<T>::type_name& type_elem, const Term<T>& term) noexcept {
        return term == type_elem;
    }

    template <typename T>
    bool operator!=(const typename Term<T>::type_name& type_elem, const Term<T>& term) noexcept {
        return !(term == type_elem);
    }

    template <typename T>
    Term<T> gcd(const Term<T>& left, const Term<T>& right) noexcept {
        return Term<T>(gcd(left.monom(), right.monom()), 1);
    }

    template <typename T>
    Term<T> lcm(const Term<T>& left, const Term<T>& right) noexcept {
        return Term<T>(lcm(left.monom(), right.monom()), left.coefficient() * right.coefficient());
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& out, const Term<T>& term) noexcept {
        if (term.IsInteger()) {
            return out << term.coefficient();
        }

        if (term.coefficient() == static_cast<T>(-1) && term.coefficient() < static_cast<T>(0)) {
            out << '-';
        } else if (term.coefficient() != static_cast<T>(1)) {
            out << term.coefficient() << '*';
        }

        return out << term.monom();
    }

    template <typename T>
    void Term<T>::Reduce() noexcept {  // private
        if (coefficient() == static_cast<T>(0)) {
            monom_ = Monomial();
        }
    }
}
