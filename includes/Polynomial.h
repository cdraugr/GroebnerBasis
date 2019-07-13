#include <algorithm>
#include <cassert>
#include <iterator>
#include <set>
#include <utility>
#include "MonomialOrder.h"

template <typename Comp>
class Polynomial {
public:
    using container = std::set<Monomial, Comp>;

    Polynomial();
    Polynomial(const Monomial&);
    Polynomial(const container&);

    const container& MonomialSet() const noexcept;
    const Monomial& LeadMonom(i32 index = 1) const;  // numeration starts from 1

    bool ReductionBy(const Polynomial&) noexcept;  // True if reduction was, else false 

    Polynomial operator-() const noexcept;
    Polynomial operator+() const noexcept;

    Polynomial& operator+=(const Polynomial&) noexcept;
    Polynomial& operator-=(const Polynomial&) noexcept;
    Polynomial& operator*=(const Polynomial&) noexcept;

    Polynomial& operator+=(const Monomial&) noexcept;
    Polynomial& operator-=(const Monomial&) noexcept;
    Polynomial& operator*=(const Monomial&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator+(Polynomial<OtherComp>, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator-(Polynomial<OtherComp>, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator*(Polynomial<OtherComp>, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator+(const Monomial&, Polynomial<OtherComp>) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator-(const Monomial&, Polynomial<OtherComp>) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator*(const Monomial&, Polynomial<OtherComp>) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator+(Polynomial<OtherComp>, const Monomial&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator-(Polynomial<OtherComp>, const Monomial&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator*(Polynomial<OtherComp>, const Monomial&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> SPolynomial(const Polynomial<OtherComp>&, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend bool operator==(const Polynomial<OtherComp>&, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend bool operator!=(const Polynomial<OtherComp>&, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend bool operator==(const Polynomial<OtherComp>&, const Monomial&) noexcept;

    template<typename OtherComp>
    friend bool operator!=(const Polynomial<OtherComp>&, const Monomial&) noexcept;

    template<typename OtherComp>
    friend bool operator==(const Monomial&, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend bool operator!=(const Monomial&, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend std::ostream& operator<<(std::ostream&, const Polynomial<OtherComp>&) noexcept;

private:
    container monoms_{};
};

template <typename Comp>
Polynomial<Comp>::Polynomial() = default;

template <typename Comp>
Polynomial<Comp>::Polynomial(const Monomial& monom) {
    if (monom != 0) {
        monoms_ = {monom};
    }
}

template <typename Comp>
Polynomial<Comp>::Polynomial(const typename Polynomial<Comp>::container& polynom) {
    for (const auto& monom : polynom) {
        if (monom != 0) {
            monoms_.insert(monom);
        }
    }
}

template <typename Comp>
const typename Polynomial<Comp>::container& Polynomial<Comp>::MonomialSet() const noexcept {
    return monoms_;
}

template <typename Comp>
const Monomial& Polynomial<Comp>::LeadMonom(i32 index) const {
    assert(static_cast<size_t>(index) <= MonomialSet().size());
    assert(1 <= index);

    auto it = MonomialSet().begin();
    std::advance(it, index - 1);
    return *it;
}

template <typename Comp>
Polynomial<Comp> Polynomial<Comp>::operator-() const noexcept {
    Polynomial<Comp>::container monoms;
    for (auto& monom : MonomialSet()) {
        monoms.insert(-monom);
    }
    return Polynomial(monoms);
}

template <typename Comp>
Polynomial<Comp> Polynomial<Comp>::operator+() const noexcept {
    return Polynomial<Comp>(*this);;
}

template <typename Comp>
bool Polynomial<Comp>::ReductionBy(const Polynomial<Comp>& other) noexcept {
    if (MonomialSet().empty() || other.MonomialSet().empty()) {
        return false;
    }

    for (const auto& monom : monoms_) {
        if (monom.IsDividedBy(other.LeadMonom())) {
            *this -= Polynomial<Comp>(monom / other.LeadMonom()) * other;
            return true;
        }
    }
    return false;
}

template <typename Comp>
Polynomial<Comp>& Polynomial<Comp>::operator+=(const Polynomial<Comp>& polynom) noexcept {
    for (const auto& monom : polynom.MonomialSet()) {
        *this += monom;
    }

    return *this;
}

template <typename Comp>
Polynomial<Comp>& Polynomial<Comp>::operator-=(const Polynomial<Comp>& polynom) noexcept {
    *this += -polynom;
    return *this;
}

template <typename Comp>
Polynomial<Comp>& Polynomial<Comp>::operator*=(const Polynomial<Comp>& polynom) noexcept {
    Polynomial<Comp> answer;
    for (const auto& monom : MonomialSet()) {
        answer += polynom * monom;
    }

    std::swap(*this, answer);
    return *this;
}

template <typename Comp>
Polynomial<Comp>& Polynomial<Comp>::operator+=(const Monomial& monom) noexcept {
    bool was_changed = false;
    for (const auto& this_monom : MonomialSet()) {
        if (this_monom.degrees() == monom.degrees()) {
            auto count = this_monom.coefficient() + monom.coefficient();
            monoms_.erase(this_monom);
            if (count != 0) {
                monoms_.insert(Monomial(monom.degrees(), count));
            }
            was_changed = true;
            break;
        }
    }
    if (was_changed == false) {
        monoms_.insert(monom);
    }
    return *this;
}

template <typename Comp>
Polynomial<Comp>& Polynomial<Comp>::operator-=(const Monomial& monom) noexcept {
    *this += -monom;
    return *this;
}

template <typename Comp>
Polynomial<Comp>& Polynomial<Comp>::operator*=(const Monomial& monom) noexcept {
    Polynomial<Comp> answer;

    for (const auto& other_monom : MonomialSet()) {
        answer += Polynomial<Comp>(monom * other_monom);
    }

    std::swap(*this, answer);
    return *this;
}

template <typename Comp>
Polynomial<Comp> operator+(const Monomial& monom, Polynomial<Comp> polynom) noexcept {
    polynom += monom;
    return polynom;
}

template <typename Comp>
Polynomial<Comp> operator-(const Monomial& monom, Polynomial<Comp> polynom) noexcept {
    polynom -= monom;
    return polynom;
}

template <typename Comp>
Polynomial<Comp> operator*(const Monomial& monom, Polynomial<Comp> polynom) noexcept {
    polynom *= monom;
    return polynom;
}

template <typename Comp>
Polynomial<Comp> operator+(Polynomial<Comp> polynom, const Monomial& monom) noexcept {
    polynom += monom;
    return polynom;
}

template <typename Comp>
Polynomial<Comp> operator-(Polynomial<Comp> polynom, const Monomial& monom) noexcept {
    polynom -= monom;
    return polynom;
}

template <typename Comp>
Polynomial<Comp> operator*(Polynomial<Comp> polynom, const Monomial& monom) noexcept {
    polynom *= monom;
    return polynom;
}

template <typename Comp>
Polynomial<Comp> operator+(Polynomial<Comp> left, const Polynomial<Comp>& right) noexcept {
    left += right;
    return left;
}

template <typename Comp>
Polynomial<Comp> operator-(Polynomial<Comp> left, const Polynomial<Comp>& right) noexcept {
    left -= right;
    return left;
}

template <typename Comp>
Polynomial<Comp> operator*(Polynomial<Comp> left, const Polynomial<Comp>& right) noexcept {
    left *= right;
    return left;
}

template<typename Comp>
Polynomial<Comp> SPolynomial(const Polynomial<Comp>& left, const Polynomial<Comp>& right) noexcept {
    if (left.MonomialSet().empty() && right.MonomialSet().empty()) {
        return {};  // assert
    } else if (left.MonomialSet().empty()) {
        return -right;
    } else if (right.MonomialSet().empty()) {
        return left;
    }

    auto lead_lcm = lcm(left.LeadMonom(), right.LeadMonom());
    auto m1 = lead_lcm / left.LeadMonom();
    auto m2 = lead_lcm / right.LeadMonom();
    return left * Polynomial<Comp>(m1) - right * Polynomial<Comp>(m2);
}

template <typename Comp>
bool operator==(const Polynomial<Comp>& left, const Polynomial<Comp>& right) noexcept {
    return left.MonomialSet() == right.MonomialSet();
}

template <typename Comp>
bool operator!=(const Polynomial<Comp>& left, const Polynomial<Comp>& right) noexcept {
    return !(left == right);
}

template <typename Comp>
bool operator==(const Polynomial<Comp>& polynom, const Monomial& monom) noexcept {
    return polynom == Polynomial<Comp>(monom);
}

template <typename Comp>
bool operator!=(const Polynomial<Comp>& polynom, const Monomial& monom) noexcept {
    return !(polynom == monom);
}

template <typename Comp>
bool operator==(const Monomial& monom, const Polynomial<Comp>& polynom) noexcept {
    return polynom == monom;
}

template <typename Comp>
bool operator!=(const Monomial& monom, const Polynomial<Comp>& polynom) noexcept {
    return !(polynom == monom);
}

template <typename Comp>
std::ostream& operator<<(std::ostream& out, const Polynomial<Comp>& polynom) noexcept {
    if (polynom.MonomialSet().empty()) {
        return out << 0;
    }

    for (const auto& monom : polynom.MonomialSet()) {
        if (monom != polynom.LeadMonom() && monom.coefficient() > 0) {
            out << '+';
        }
        out << monom;
    }
    return out;
}
