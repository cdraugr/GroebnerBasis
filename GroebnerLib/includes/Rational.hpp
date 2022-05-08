#pragma once

#include "Lib.hpp"

namespace gb {
namespace fields {

class Rational {
public:
    Rational(const gb::i64& = 0, const gb::i64& = 1);

    const gb::i64& GetNumerator() const noexcept;
    const gb::i64& GetDenominator() const noexcept;

    bool IsInteger() const noexcept;

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

    friend Rational pow(const Rational&, const gb::i64&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Rational&) noexcept;

private:
    void Reduce_() noexcept;

    gb::i64 numerator_{};
    gb::i64 denominator_{};
};

}  // namespace fields
}  // namespace gb
