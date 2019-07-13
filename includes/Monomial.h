#include <cstdint>
#include <iostream>
#include <map>
#include <vector>
#include "Rational.h"

class Monomial {
public:
    using container = std::map<i32, i32>;

    Monomial();
    Monomial(i32);
    Monomial(Rational);
    Monomial(const std::vector<i32>&, const Rational = 1);
    Monomial(const container&, const Rational = 1);

    Rational& coefficient() noexcept; 
    const Rational& coefficient() const noexcept;
    const container& degrees() const noexcept;

    i32 GetDegree(i32) const noexcept;
    friend i32 deg(const Monomial&) noexcept;

    bool IsDividedBy(const Monomial&) const noexcept;

    Monomial operator-() const noexcept;
    Monomial operator+() const noexcept;

    Monomial& operator*=(const Monomial&) noexcept;
    friend Monomial operator*(Monomial, const Monomial&) noexcept;

    Monomial& operator/=(const Monomial&) noexcept;
    friend Monomial operator/(Monomial, const Monomial&) noexcept;

    friend bool operator==(const Monomial&, const Monomial&) noexcept;
    friend bool operator!=(const Monomial&, const Monomial&) noexcept;

    friend Monomial operator,(const Monomial&, const Monomial&) noexcept;  // gcd
    friend Monomial lcm(const Monomial&, const Monomial&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Monomial&) noexcept;

private:
    Rational coefficient_{};
    container data_{};  // (variable number) && (power)
};
