#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "../includes/Rational.h"

Rational::Rational(i32 numerator, i32 denominator) {
    numerator_ = denominator < 0 ? -numerator : numerator;
    denominator_ = denominator < 0 ? -denominator : denominator;
    Reduce();
}

i32 Rational::numerator() const noexcept {
    return numerator_;
}

i32 Rational::denominator() const noexcept {
    return denominator_;
}

bool operator<(const Rational& left, const Rational& right) noexcept {
    return (left - right).numerator() < 0;
}

bool operator>(const Rational& left, const Rational& right) noexcept {
    return right < left;
}

bool operator<=(const Rational& left, const Rational& right) noexcept {
    return !(left > right);
}

bool operator>=(const Rational& left, const Rational& right) noexcept {
    return !(left < right);
}

bool operator==(const Rational& left, const Rational& right) noexcept {
    return left.numerator() == right.numerator() && left.denominator() == right.denominator();
}

bool operator!=(const Rational& left, const Rational& right) noexcept {
    return !(left == right);
}

Rational::operator bool() const noexcept {
    return numerator() != 0;
}

bool Rational::operator!() const noexcept {
    return !(static_cast<bool>(*this));
}

Rational Rational::operator+() const noexcept {
    return Rational(numerator(), denominator());
}

Rational Rational::operator-() const noexcept {
    return Rational(-numerator(), denominator());
}

Rational& Rational::operator+=(const Rational& other) noexcept {
    numerator_ = numerator() * other.denominator() + other.numerator() * denominator();
    denominator_ *= other.denominator();
    Reduce();
    return *this;
}

Rational operator+(Rational left, const Rational& right) noexcept {
    left += right;
    return left;
}

Rational& Rational::operator-=(const Rational& other) noexcept {
    *this += -other;
    return *this;
}

Rational operator-(Rational left, const Rational& right) noexcept {
    left -= right;
    return left;
}

Rational& Rational::operator*=(const Rational& other) noexcept {
    numerator_ *= other.numerator();
    denominator_ *= other.denominator();
    Reduce();
    return *this;
}

Rational operator*(Rational left, const Rational& right) noexcept {
    left *= right;
    return left;
}

Rational& Rational::operator/=(const Rational& other) {
    if (other == 0) {
        throw std::runtime_error("Division by zero.");
    }
    *this *= Rational(other.denominator(), other.numerator());
    Reduce();
    return *this;
}

Rational operator/(Rational left, const Rational& right) {
    left /= right;
    return left;
}

Rational operator,(const Rational& left, const Rational& right) noexcept {
    return left.denominator() == 1 && right.denominator() == 1 ?
        Rational(std::gcd(left.numerator(), right.numerator())) :
        Rational(1);
}

Rational lcm(const Rational& left, const Rational& right) noexcept {
    return left.denominator() == 1 && right.denominator() == 1 ?
        Rational(std::lcm(left.numerator(), right.numerator())) :
        left * right;
}

Rational pow(const Rational& number, i32 power) noexcept {
    if (power < 0) {
        return pow(1 / number, -power);
    } else if (power == 0) {
        return 1;
    }
    if (power % 2 != 0) {
        return number * pow(number, power - 1);
    } else {
        auto tmp = pow(number, power / 2);
        return tmp * tmp;
    }
}

std::ostream& operator<<(std::ostream& out, const Rational& rational) noexcept {
    if (rational.denominator() == 1) {
        return out << rational.numerator();
    }
    if (rational.numerator() < 0) {
        out << "-(" << -rational.numerator();
    } else {
        out << '(' << rational.numerator();
    }
    return out << " / " << rational.denominator() << ')';
}

void Rational::Reduce() noexcept {  // private
    auto gcd = std::gcd(numerator(), denominator());
    numerator_ /= gcd;
    denominator_ /= gcd;
}
