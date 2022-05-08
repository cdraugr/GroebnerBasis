#include "Rational.hpp"

namespace gb {
namespace fields {

Rational::Rational(const gb::i64& numerator, const gb::i64& denominator) {
    if (denominator == 0) {
        throw std::runtime_error("Division by zero.");
    }
    numerator_ = denominator < 0 ? -numerator : numerator;
    denominator_ = denominator < 0 ? -denominator : denominator;
    Reduce_();
}

const gb::i64& Rational::GetNumerator() const noexcept {
    return numerator_;
}

const gb::i64& Rational::GetDenominator() const noexcept {
    return denominator_;
}

bool Rational::IsInteger() const noexcept {
    return GetDenominator() == 1;
}

bool operator<(const Rational& left, const Rational& right) noexcept {
    return left.GetNumerator() * right.GetDenominator() < right.GetNumerator() * left.GetDenominator();
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
    return left.GetNumerator() == right.GetNumerator() && left.GetDenominator() == right.GetDenominator();
}

bool operator!=(const Rational& left, const Rational& right) noexcept {
    return !(left == right);
}

Rational Rational::operator+() const noexcept {
    return *this;
}

Rational Rational::operator-() const noexcept {
    return Rational(-GetNumerator(), GetDenominator());
}

Rational& Rational::operator+=(const Rational& other) noexcept {
    numerator_ = GetNumerator() * other.GetDenominator() + other.GetNumerator() * GetDenominator();
    denominator_ *= other.GetDenominator();
    Reduce_();
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
    numerator_ *= other.GetNumerator();
    denominator_ *= other.GetDenominator();
    Reduce_();
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
    *this *= Rational(other.GetDenominator(), other.GetNumerator());
    return *this;
}

Rational operator/(Rational left, const Rational& right) {
    left /= right;
    return left;
}

Rational pow(const Rational& number, const gb::i64& power) noexcept {
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
    if (rational.IsInteger()) {
        return out << rational.GetNumerator();
    }
    if (rational.GetNumerator() < 0) {
        out << "-(" << -rational.GetNumerator();
    } else {
        out << '(' << rational.GetNumerator();
    }
    return out << " / " << rational.GetDenominator() << ')';
}

void Rational::Reduce_() noexcept {  // private
    auto gcd = std::gcd(GetNumerator(), GetDenominator());
    numerator_ /= gcd;
    denominator_ /= gcd;
}

}  // namespace fields
}  // namespace gb
