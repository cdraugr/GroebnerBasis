#ifndef RATIONAL_H
# define RATIONAL_H

# include "Lib.h"

class Rational {
public:
    Rational(const i64& = 0, const i64& = 1);

    const i64& numerator() const noexcept;
    const i64& denominator() const noexcept;

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

    friend Rational pow(const Rational&, const i64&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Rational&) noexcept;

private:
    void Reduce() noexcept;

    i64 numerator_{};
    i64 denominator_{};
};

#endif
