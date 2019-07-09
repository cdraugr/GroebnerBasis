#include <algorithm>
#include <numeric>
#include "../includes/Monomial.h"

Monomial::Monomial() = default;

Monomial::Monomial(double value)
    : count_{value} {}

Monomial::Monomial(const std::vector<i32>& arguments, const double value) {
    count_ = value;
    if (count() != 0 && !arguments.empty()) {
        for (size_t i = 0; i != arguments.size(); ++i) {
            if (arguments[i] != 0) {
                data_[static_cast<i32>(i)] = arguments[i];
            }
        }
    }
}

Monomial::Monomial(const container& arguments, const double value) {
    count_ = value;
    if (count() != 0) {
        for (const auto& [num, degree] : arguments) {
            if (num >= 0 && degree > 0) {
                data_[num] = degree;
            }
        }
    }
}

double Monomial::count() const noexcept {
    return count_;
}

const Monomial::container& Monomial::degrees() const noexcept {
    return data_;
}

Monomial& Monomial::operator*=(const Monomial& other) noexcept {
    count_ *= other.count();
    for (const auto& [num, degree] : other.degrees()) {
        data_[num] += degree;
    }
    return *this;
}

Monomial operator*(Monomial left, const Monomial& right) noexcept {
    left *= right;
    return left;
}

bool operator==(const Monomial& left, const Monomial& right) noexcept {
    return left.count() == right.count() && left.degrees() == right.degrees();
}

bool operator!=(const Monomial& left, const Monomial& right) noexcept {
    return !(left == right);
}

Monomial operator,(const Monomial& left, const Monomial& right) noexcept {  // gcd
    Monomial result(
        std::gcd(
            static_cast<i32>(left.count()),
            static_cast<i32>(right.count())
        )
    );
    for (const auto& [num, degree] : left.degrees()) {
        if (right.degrees().find(num) != right.degrees().end()) {
            result.data_[num] = std::min(degree, right.degrees().at(num));
        } else {
            result.data_.erase(num);
        }
    }
    return result;
}

Monomial lcm(const Monomial& left, const Monomial& right) noexcept {
    Monomial result = left;
    result.count_ = std::lcm(
            static_cast<i32>(left.count()),
            static_cast<i32>(right.count())
        );
    for (const auto& [num, degree] : right.degrees()) {
        result.data_[num] = std::max(result.data_[num], degree);
    }
    return result;
}

i32 deg(const Monomial& monom) noexcept {
    i32 sum = 0;
    for (const auto& [num, degree] : monom.degrees()) {
        sum += degree;
    }
    return sum;
}

std::ostream& operator<<(std::ostream& out, const Monomial& monom) noexcept {
    if (monom.degrees().empty()) {
        return out << monom.count();
    }

    if (monom.count() == -1) {
        out << '-';
    } else if (monom.count() != 1) {
        out << monom.count() << '*';
    }

    for (const auto& [num, degree] : monom.degrees()) {
        out << "x_(" << num + 1 << ')';
        if (degree > 1) {
            out << "^(" << degree << ')';
        }
        if (num < (*monom.degrees().crbegin()).first) {
            out << '*';
        }
    }
    return out;
}
