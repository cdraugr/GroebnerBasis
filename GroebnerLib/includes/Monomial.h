#include <map>
#include "Lib.h"

namespace gb {
    class Monomial {
    public:
        using container = std::map<i64, i64>;

        Monomial();
        Monomial(const std::vector<i64>&);
        Monomial(const container&);

        const container& degrees() const noexcept;  // x_(i)^{j} = {i - 1, j} [numeration starts from 0].

        i64 GetDegree(i64) const noexcept;
        i64 GetLastVariableIndex() const noexcept;
        friend i64 deg(const Monomial&) noexcept;

        bool IsOne() const noexcept;
        bool IsDivisibleBy(const Monomial&) const noexcept;

        Monomial& operator*=(const Monomial&) noexcept;
        friend Monomial operator*(Monomial, const Monomial&) noexcept;

        Monomial& operator/=(const Monomial&);
        friend Monomial operator/(Monomial, const Monomial&);

        friend bool operator==(const Monomial&, const Monomial&) noexcept;
        friend bool operator!=(const Monomial&, const Monomial&) noexcept;

        friend Monomial gcd(const Monomial&, const Monomial&) noexcept;  // gcd
        friend Monomial lcm(const Monomial&, const Monomial&) noexcept;

        friend std::ostream& operator<<(std::ostream&, const Monomial&) noexcept;

    private:
        container data_{};  // (variable number) && (power)
    };
}
