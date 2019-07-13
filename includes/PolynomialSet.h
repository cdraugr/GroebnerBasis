#include <list>
#include <utility>
#include "PolynomialOrder.h"

template <typename Comp>
class PolynomialSet {
public:
    using container = std::set<Polynomial<Comp>, PolynomialOrder<LexCoefComp>>;

    PolynomialSet();
    PolynomialSet(const Polynomial<Comp>&);
    PolynomialSet(const container&);

    const container& PolSet() const noexcept;

    bool OneReductionByMe(Polynomial<Comp>&) const noexcept;  // changing given Polynomial
    bool ReductionToResByMe(Polynomial<Comp>&) const noexcept;  // changing given Polynomial
    // return values same as Polynomial<Comp>::ReductionBy()

    PolynomialSet<Comp>& MakeGroebnerBasis() noexcept;

    bool IsPolynomialInMe(const Polynomial<Comp>&) const noexcept;

    template <typename OtherComp>
    friend bool IsGroebnerBasis(const PolynomialSet<OtherComp>&) noexcept;

    template<typename OtherComp>
    friend std::ostream& operator<<(std::ostream& out, const PolynomialSet<OtherComp>&) noexcept;

private:
    container polynoms_{};
};

template <typename Comp>
PolynomialSet<Comp>::PolynomialSet() = default;

template <typename Comp>
PolynomialSet<Comp>::PolynomialSet(const Polynomial<Comp>& polynom) {
    if (polynom != 0) {
        polynoms_.insert(polynom);
    }
}

template <typename Comp>
PolynomialSet<Comp>::PolynomialSet(const PolynomialSet<Comp>::container& poly_set) {
    for (const auto& polynom : poly_set) {
        if (polynom != 0) {
            polynoms_.insert(polynom);
        }
    }
}

template <typename Comp>
const typename PolynomialSet<Comp>::container& PolynomialSet<Comp>::PolSet() const noexcept {
    return polynoms_;
}

template <typename Comp>
bool PolynomialSet<Comp>::OneReductionByMe(Polynomial<Comp>& polynom) const noexcept {
    bool was_changed = false;
    for (const auto& redu_poly : PolSet()) {
        while (polynom.ReductionBy(redu_poly)) {  // polynom is changing here
            was_changed = true;
        }
    }
    return was_changed;
}

template <typename Comp>
bool PolynomialSet<Comp>::ReductionToResByMe(Polynomial<Comp>& polynom) const noexcept {
    bool was_changed = false;
    while (OneReductionByMe(polynom)) {  // polynom is changing here
        was_changed = true;
    }
    return was_changed;
}

template <typename Comp>
PolynomialSet<Comp>& PolynomialSet<Comp>::MakeGroebnerBasis() noexcept {
    PolynomialOrder<LexCoefComp> comparator;
    std::list<std::pair<Polynomial<Comp>, Polynomial<Comp>>> pairs;
    for (const auto& polymon_f : PolSet()) {
        for (const auto& polymon_g : PolSet()) {
            if (comparator(polymon_f, polymon_g) && polymon_f != polymon_g) {
                pairs.push_back({polymon_f, polymon_g});
            }
        }
    }

    for (const auto& [polymon_f, polymon_g] : pairs) {
        auto s_polynomial = SPolynomial(polymon_f, polymon_g);
        ReductionToResByMe(s_polynomial);
        if (s_polynomial != 0) {
            for (const auto& polynom : PolSet()) {
                pairs.push_back({polynom, s_polynomial});
            }
            polynoms_.insert(s_polynomial);
        }
    }
    return *this;
}

template <typename Comp>
bool PolynomialSet<Comp>::IsPolynomialInMe(const Polynomial<Comp>& polynom) const noexcept {
    auto ideal = *this;
    auto tmp = polynom;
    ideal.MakeGroebnerBasis().ReductionToResByMe(tmp);
    return tmp == 0;
}

template <typename Comp>
bool IsGroebnerBasis(const PolynomialSet<Comp>& pol_set) noexcept {
    PolynomialOrder<LexCoefComp> comparator;
    for (const auto& polymon_f : pol_set.PolSet()) {
        for (const auto& polymon_g : pol_set.PolSet()) {
            if (comparator(polymon_f, polymon_g) || polymon_f == polymon_g) {
                continue;
            }
            auto s_polynomial = SPolynomial(polymon_f, polymon_g);
            pol_set.ReductionToResByMe(s_polynomial);            
            if (s_polynomial != 0) {
                return false;
            }
        }
    }
    return true;
}

template <typename Comp>
std::ostream& operator<<(std::ostream& out, const PolynomialSet<Comp>& poly_set) noexcept {
    for (auto it = poly_set.PolSet().begin(); it != poly_set.PolSet().end(); ++it) {
        if (it != poly_set.PolSet().begin()) {
            out << '\n';
        }
        out << *it;
    }
    return out;
}
