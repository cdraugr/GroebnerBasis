#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

using i32 = int32_t;

class Monomial {
public:
    using container = std::map<i32, i32>;

    Monomial();
    Monomial(double);
    Monomial(const std::vector<i32>&, const double = 0);
    Monomial(const container&, const double = 0);

    double count() const noexcept;
    const container& degrees() const noexcept;

    Monomial& operator*=(const Monomial&) noexcept;
    friend Monomial operator*(Monomial, const Monomial&) noexcept;

    friend bool operator==(const Monomial&, const Monomial&) noexcept;
    friend bool operator!=(const Monomial&, const Monomial&) noexcept;

    friend Monomial operator,(const Monomial&, const Monomial&) noexcept;  // gcd
    friend Monomial lcm(const Monomial&, const Monomial&) noexcept;

    friend i32 deg(const Monomial&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Monomial&) noexcept;

private:
    double count_{};
    container data_{};  // (variable number) && (power)
};
