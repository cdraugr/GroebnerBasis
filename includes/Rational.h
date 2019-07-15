#include <cstdint>
#include <iostream>

using i32 = int32_t;

class Rational {
public:
    Rational(i32 = 0, i32 = 1);

    i32 numerator() const noexcept;
    i32 denominator() const noexcept;

    friend bool operator<(const Rational&, const Rational&) noexcept;
    friend bool operator>(const Rational&, const Rational&) noexcept;
    friend bool operator<=(const Rational&, const Rational&) noexcept;
    friend bool operator>=(const Rational&, const Rational&) noexcept;

    friend bool operator==(const Rational&, const Rational&) noexcept;
    friend bool operator!=(const Rational&, const Rational&) noexcept;

    Rational operator+() const noexcept;
    Rational operator-() const noexcept;

    Rational& operator+=(const Rational&) noexcept;
    friend Rational operator+(Rational, const Rational&) noexcept;

    Rational& operator-=(const Rational&) noexcept;
    friend Rational operator-(Rational, const Rational&) noexcept;

    Rational& operator*=(const Rational&) noexcept;
    friend Rational operator*(Rational, const Rational&) noexcept;

    Rational& operator/=(const Rational&);
    friend Rational operator/(Rational, const Rational&);

    friend Rational operator,(const Rational&, const Rational&) noexcept;  // gcd
    friend Rational lcm(const Rational&, const Rational&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Rational&) noexcept;

private:
    void Reduce() noexcept;

    i32 numerator_{};
    i32 denominator_{};
};
