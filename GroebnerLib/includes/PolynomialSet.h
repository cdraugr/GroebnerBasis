#include <list>
#include "PolynomialOrder.h"

namespace gb {
    template <typename T, typename Comp>
    class PolynomialSet {
    public:
        using container = std::set<Polynomial<T, Comp>, PolynomialOrder<LexCoefComp>>;

        PolynomialSet();
        PolynomialSet(const Polynomial<T, Comp>&);
        PolynomialSet(const container&);

        const container& PolSet() const noexcept;
        const Polynomial<T, Comp>& LeadPolynom(const i64& = 1) const;

        bool OneReductionByMe(Polynomial<T, Comp>*) const noexcept;  // Сhanging given Polynomial.
        bool ReductionToResByMe(Polynomial<T, Comp>*) const noexcept;  // Changing given Polynomial.
        // Returns true if there was a reduction otherwise returns false.

        void AddPolynomial(const Polynomial<T, Comp>&) noexcept;

        PolynomialSet<T, Comp>& MakeGroebnerBasis() noexcept;

        bool IsPolynomialInMyIdeal(const Polynomial<T, Comp>&) const noexcept;

        template <typename OtherT, typename OtherComp>
        friend std::list<Polynomial<OtherT, OtherComp>> AllSPolynoms(const PolynomialSet<OtherT, OtherComp>& pol_set) noexcept;

        template <typename OtherT, typename OtherComp>
        friend bool IsGroebnerBasis(const PolynomialSet<OtherT, OtherComp>&) noexcept;

        template <typename OtherT, typename OtherComp>
        friend PolynomialSet<OtherT, OtherComp> GiveSigmaSet(const i64&);

        template <typename OtherT, typename OtherComp>
        friend PolynomialSet<OtherT, OtherComp> GiveGroebnerSigmaSet(const i64&);

        template <typename OtherT, typename OtherComp>
        friend std::ostream& operator<<(std::ostream&, const PolynomialSet<OtherT, OtherComp>&) noexcept;

    private:
        container polynoms_{};
    };

    template <typename T, typename Comp>
    PolynomialSet<T, Comp>::PolynomialSet() = default;

    template <typename T, typename Comp>
    PolynomialSet<T, Comp>::PolynomialSet(const Polynomial<T, Comp>& polynom) {
        if (polynom != Term<T>(0)) {
            polynoms_.insert(polynom);
        }
    }

    template <typename T, typename Comp>
    PolynomialSet<T, Comp>::PolynomialSet(const PolynomialSet<T, Comp>::container& poly_set) {
        for (const auto& polynom : poly_set) {
            if (polynom != Term<T>(0)) {
                polynoms_.insert(polynom);
            }
        }
    }

    template <typename T, typename Comp>
    const typename PolynomialSet<T, Comp>::container& PolynomialSet<T, Comp>::PolSet() const noexcept {
        return polynoms_;
    }

    template <typename T, typename Comp>
    const Polynomial<T, Comp>& PolynomialSet<T, Comp>::LeadPolynom(const i64& index) const {
        assert(1 <= index);  // Firstly check negative and zero.
        assert(static_cast<size_t>(index) <= PolSet().size());

        auto it = PolSet().begin();
        std::advance(it, index - 1);
        return *it;
    }

    template <typename T, typename Comp>
    bool PolynomialSet<T, Comp>::OneReductionByMe(Polynomial<T, Comp>* polynom) const noexcept {
        bool was_changed = false;
        for (const auto& redu_poly : PolSet()) {
            while (polynom->TryReduceOnceBy(redu_poly)) {  // Polynom is changing here.
                was_changed = true;
            }
        }
        return was_changed;
    }

    template <typename T, typename Comp>
    bool PolynomialSet<T, Comp>::ReductionToResByMe(Polynomial<T, Comp>* polynom) const noexcept {
        bool was_changed = false;
        while (OneReductionByMe(polynom)) {  // Polynom is changing here.
            was_changed = true;
        }
        return was_changed;
    }

    template <typename T, typename Comp>
    void PolynomialSet<T, Comp>::AddPolynomial(const Polynomial<T, Comp>& poly) noexcept {
        polynoms_.insert(poly);
    }

    template <typename T, typename Comp>
    std::list<Polynomial<T, Comp>> AllSPolynoms(const PolynomialSet<T, Comp>& pol_set) noexcept {
        PolynomialOrder<LexCoefComp> comparator;
        std::list<Polynomial<T, Comp>> s_polys;
        for (const auto& polymon_f : pol_set.PolSet()) {
            for (const auto& polymon_g : pol_set.PolSet()) {
                if (comparator(polymon_f, polymon_g) && polymon_f != polymon_g) {
                    s_polys.push_back(SPolynomial(polymon_f, polymon_g));
                }
            }
        }
        return s_polys;
    }

    template <typename T, typename Comp>
    PolynomialSet<T, Comp>& PolynomialSet<T, Comp>::MakeGroebnerBasis() noexcept {
        auto s_polys = std::move(AllSPolynoms(*this));
        for (auto& s_polynomial : s_polys) {
            ReductionToResByMe(&s_polynomial);
            if (s_polynomial != Term<T>(0)) {
                for (const auto& polynom : PolSet()) {
                    s_polys.push_back(SPolynomial(polynom, s_polynomial));
                }
                polynoms_.insert(s_polynomial);
            }
        }
        return *this;
    }

    template <typename T, typename Comp>
    bool PolynomialSet<T, Comp>::IsPolynomialInMyIdeal(const Polynomial<T, Comp>& polynom) const noexcept {
        auto ideal = *this;
        auto tmp = polynom;
        ideal.MakeGroebnerBasis().ReductionToResByMe(&tmp);
        return tmp == Term<T>(0);
    }

    template <typename T, typename Comp>
    bool IsGroebnerBasis(const PolynomialSet<T, Comp>& pol_set) noexcept {
        PolynomialOrder<LexCoefComp> comparator;
        for (const auto& polymon_f : pol_set.PolSet()) {
            for (const auto& polymon_g : pol_set.PolSet()) {
                if (comparator(polymon_f, polymon_g) || polymon_f == polymon_g) {
                    continue;
                }
                auto s_polynomial = SPolynomial(polymon_f, polymon_g);
                pol_set.ReductionToResByMe(&s_polynomial);
                if (s_polynomial != Term<T>(0)) {
                    return false;
                }
            }
        }
        return true;
    }

    template <typename T, typename Comp>
    PolynomialSet<T, Comp> GiveSigmaSet(const i64& variable_count) {
        PolynomialSet<T, Comp> answer(GiveSigma<T, Comp>(variable_count, variable_count) - Term<T>(pow(static_cast<T>(-1), variable_count - 1)));
        for (i64 i = 1; i < variable_count; ++i) {
            answer.AddPolynomial(GiveSigma<T, Comp>(i, variable_count));
        }
        return answer;
    }

    template <typename T, typename Comp>
    PolynomialSet<T, Comp> GiveGroebnerSigmaSet(const i64& variable_count) {
        return GiveSigmaSet<T, Comp>(variable_count).MakeGroebnerBasis();
    }

    template <typename T, typename Comp>
    std::ostream& operator<<(std::ostream& out, const PolynomialSet<T, Comp>& poly_set) noexcept {
        for (auto it = poly_set.PolSet().begin(); it != poly_set.PolSet().end(); ++it) {
            if (it != poly_set.PolSet().begin()) {
                out << '\n';
            }
            out << *it;
        }
        return out;
    }
}
