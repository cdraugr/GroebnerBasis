#include "Monomial.h"

namespace gb {

Monomial::Monomial() = default;

Monomial::Monomial(const std::vector<i64>& arguments) {
    if (arguments.empty()) {
        return ;
    }
    for (size_t i = 0; i != arguments.size(); ++i) {
        if (arguments[i] != 0) {
            data_[static_cast<i64>(i)] = arguments[i];
        }
    }
}

Monomial::Monomial(const container& arguments) {
    for (const auto& [num, degree] : arguments) {
        if (num >= 0 && degree > 0) {
            data_[num] = degree;
        }
    }
}

const Monomial::container& Monomial::degrees() const noexcept {
    return data_;
}

i64 Monomial::GetDegree(const i64& index) const noexcept {
    return degrees().find(index) != degrees().end() ?
        degrees().at(index) :
        0;
}

i64 Monomial::GetLastVariableIndex() const noexcept {
    return IsOne() ? 0 : degrees().crbegin()->first;
}

i64 deg(const Monomial& monomial) noexcept {
    i64 sum = 0;
    for (const auto& [num, degree] : monomial.degrees()) {
        sum += degree;
    }
    return sum;
}

bool Monomial::IsOne() const noexcept {
    return degrees().empty();
}

bool Monomial::IsDivisibleBy(const Monomial& other) const noexcept {
    for (const auto& [num, degree] : other.degrees()) {
        if (GetDegree(num) < degree) {
            return false;
        }
    }
    return true;
}

Monomial& Monomial::operator*=(const Monomial& other) noexcept {
    for (const auto& [num, degree] : other.degrees()) {
        data_[num] += degree;
    }
    return *this;
}

Monomial operator*(Monomial left, const Monomial& right) noexcept {
    left *= right;
    return left;
}

Monomial& Monomial::operator/=(const Monomial& other) {
    for (const auto& [num, degree] : other.degrees()) {
        data_[num] -= degree;
        if (data_[num] == 0) {
            data_.erase(num);
        } else if (data_[num] < 0) {
            data_.clear();
            throw std::runtime_error("Division is not defined.");
        }
    }
    return *this;
}

Monomial operator/(Monomial left, const Monomial& right) {
    left /= right;
    return left;
}

bool operator==(const Monomial& left, const Monomial& right) noexcept {
    return left.degrees() == right.degrees();
}

bool operator!=(const Monomial& left, const Monomial& right) noexcept {
    return !(left == right);
}

Monomial gcd(const Monomial& left, const Monomial& right) noexcept {
    Monomial result;
    for (const auto& [num, degree] : left.degrees()) {
        if (right.degrees().find(num) != right.degrees().end()) {
            result.data_[num] = std::min(degree, right.degrees().at(num));
        }
    }
    return result;
}

Monomial lcm(const Monomial& left, const Monomial& right) noexcept {
    Monomial result = left;
    for (const auto& [num, degree] : right.degrees()) {
        result.data_[num] = std::max(result.data_[num], degree);
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Monomial& monomial) noexcept {
    if (monomial.IsOne()) {
        return out << 1;
    }

    for (auto it = monomial.degrees().begin(); it != monomial.degrees().end(); ++it) {
        out << "x_(" << it->first + 1 << ')';
        if (it->second > 1) {
            out << "^{" << it->second << '}';
        }
        if (it != std::prev(monomial.degrees().end())) {
            out << '*';
        }
    }
    return out;
}

}  // namespace gb
