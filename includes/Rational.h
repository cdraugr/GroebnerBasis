#include <cstdint>
#include <iostream>

using i32 = int32_t;

class Rational {
public:
    Rational(const i32& = 0, const i32& = 1);

    const i32& numerator() const noexcept;
    const i32& denominator() const noexcept;

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

    Rational& operator/=(const Rational&) noexcept;
    friend Rational operator/(Rational, const Rational&) noexcept;

    friend Rational operator,(const Rational&, const Rational&) noexcept;
    friend Rational lcm(const Rational&, const Rational&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Rational&) noexcept;

private:
    void Reduce() noexcept;

    i32 numerator_{};
    i32 denominator_{};
};
