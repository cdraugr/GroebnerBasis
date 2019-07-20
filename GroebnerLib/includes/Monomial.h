#include <map>
#include <vector>
#include "Rational.h"

namespace gb {
    class Monomial {
    public:
        using container = std::map<i32, i32>;
        using type_name = Rational;

        Monomial();
        Monomial(i32);
        Monomial(const type_name&);
        Monomial(const std::vector<i32>&, const type_name& = 1);
        Monomial(const container&, const type_name& = 1);

        const type_name& coefficient() const noexcept;
        const container& degrees() const noexcept;  // x_(i)^{j} = {i - 1, j} [numeration starts from 0].

        i32 GetDegree(i32) const noexcept;
        friend i32 deg(const Monomial&) noexcept;

        bool IsDividedBy(const Monomial&) const noexcept;

        Monomial operator+() const noexcept;
        Monomial operator-() const noexcept;

        Monomial& operator*=(const Monomial&) noexcept;
        friend Monomial operator*(Monomial, const Monomial&) noexcept;

        Monomial& operator/=(const Monomial&);
        friend Monomial operator/(Monomial, const Monomial&);

        friend bool operator==(const Monomial&, const Monomial&) noexcept;
        friend bool operator!=(const Monomial&, const Monomial&) noexcept;

        friend Monomial operator,(const Monomial&, const Monomial&) noexcept;  // gcd
        friend Monomial lcm(const Monomial&, const Monomial&) noexcept;

        friend std::ostream& operator<<(std::ostream&, const Monomial&) noexcept;

    private:
        type_name coefficient_{};
        container data_{};  // (variable number) && (power)
    };
}
