#include <algorithm>
#include <cassert>
#include <iterator>
#include <set>
#include "MonomialOrder.h"

template <typename Comp>
class Polynomial {
public:
    using container = std::set<Monomial, Comp>;

    Polynomial();
    Polynomial(const Monomial&);
    Polynomial(const container&);

    const container& MonomialSet() const noexcept;

    const Monomial& LeadMonom(i32 index = 1) const;

    Polynomial operator-() const noexcept;
    Polynomial operator+() const noexcept;

    Polynomial& operator+=(const Polynomial&) noexcept;
    Polynomial& operator-=(const Polynomial&) noexcept;
    Polynomial& operator*=(const Polynomial&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator+(Polynomial<OtherComp>, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator-(Polynomial<OtherComp>, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> operator*(Polynomial<OtherComp>, const Polynomial<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend Polynomial<OtherComp> SPolynomial(const Polynomial<OtherComp>&, const Polynomial<OtherComp>&) noexcept;

    Polynomial& ReductionBy(const Polynomial&) noexcept;

    template<typename OtherComp>
    friend std::ostream& operator<<(std::ostream& out, const Polynomial<OtherComp>& polynom) noexcept;

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
Polynomial<Comp>::Polynomial(const typename Polynomial<Comp>::container& polynom)
    : monoms_{polynom} {}

template <typename Comp>
const typename Polynomial<Comp>::container& Polynomial<Comp>::MonomialSet() const noexcept {
    return monoms_;
}

template <typename Comp>
const Monomial& Polynomial<Comp>::LeadMonom(i32 index) const {
    assert(1 <= index && static_cast<size_t>(index) <= MonomialSet().size());
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
Polynomial<Comp>& Polynomial<Comp>::operator+=(const Polynomial<Comp>& polynom) noexcept {
    Polynomial<Comp>::container monoms(monoms_);
    for (const auto& monom : polynom.MonomialSet()) {
        bool was_changed = false;

        for (const auto& this_monom : monoms_) {
            if (this_monom.degrees() == monom.degrees()) {
                monoms.erase(this_monom);
                if (this_monom.coefficient() + monom.coefficient() != 0) {
                    if (monom.degrees().empty()) {
                        monoms.insert(this_monom.coefficient() + monom.coefficient());
                    } else {
                        monoms.insert({monom.degrees(), this_monom.coefficient() + monom.coefficient()});
                    }
                }
                was_changed = true;
                break;
            }
        }
        if (was_changed == false) {
            monoms.insert(monom);
        }
    }
    Polynomial<Comp> extra_polynom(monoms);
    std::swap(*this, extra_polynom);
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
    for (const auto& monom_i : MonomialSet()) {
        for (const auto& monom_j : polynom.MonomialSet()) {
            answer += Polynomial<ReLexComp>(monom_i * monom_j);
        }
    }

    std::swap(*this, answer);
    return *this;
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
        return {};
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
Polynomial<Comp>& Polynomial<Comp>::ReductionBy(const Polynomial<Comp>& polynom) noexcept {
    if (polynom.MonomialSet().empty()) {
        return *this;
    }

    for (const auto& monom : monoms_) {
        if (monom / polynom.LeadMonom() != 0) {
            *this -= Polynomial<Comp>(monom / polynom.LeadMonom()) * polynom;
            break;
        }
    }
    return *this;
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
