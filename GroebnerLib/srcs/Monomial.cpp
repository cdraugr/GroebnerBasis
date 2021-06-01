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
    for (const auto& [idx, degree] : arguments) {
        if (idx >= 0 && degree > 0) {
            data_[idx] = degree;
        }
    }
}

const Monomial::container& Monomial::degrees() const noexcept {
    return data_;
}

i64 Monomial::GetDegree(const i64& index) const noexcept {
    return degrees().find(index) != degrees().end() ? degrees().at(index) : 0;
}

i64 Monomial::GetLastVariableIndex() const noexcept {
    return IsOne() ? 0 : degrees().crbegin()->first;
}

i64 deg(const Monomial& monomial) noexcept {
    i64 sum = 0;
    for (const auto& idx_degree : monomial.degrees()) {
        sum += idx_degree.second;
    }
    return sum;
}

static std::list<Monomial> _GetAllDivisors(const Monomial& monomial, i64 start_index) {
    if (monomial.IsOne()) {
        return {monomial};
    }
    std::list<Monomial> result({monomial});
    for (const auto& idx_degree : monomial.degrees()) {
        if (start_index > idx_degree.first) {
            continue;
        }
        auto sub_degrees = monomial.degrees();
        sub_degrees[idx_degree.first] -= 1;
        result.splice(result.end(), _GetAllDivisors(Monomial(sub_degrees), idx_degree.first));
    }
    return result;
}

std::list<Monomial> GetAllDivisors(const Monomial& monomial) {
    return _GetAllDivisors(monomial, 0);
}

bool Monomial::IsOne() const noexcept {
    return degrees().empty();
}

bool Monomial::IsDivisibleBy(const Monomial& other) const noexcept {
    for (const auto& [idx, degree] : other.degrees()) {
        if (GetDegree(idx) < degree) {
            return false;
        }
    }
    return true;
}

Monomial& Monomial::operator*=(const Monomial& other) noexcept {
    for (const auto& [idx, degree] : other.degrees()) {
        data_[idx] += degree;
    }
    return *this;
}

Monomial operator*(Monomial left, const Monomial& right) noexcept {
    left *= right;
    return left;
}

Monomial& Monomial::operator/=(const Monomial& other) {
    for (const auto& [idx, degree] : other.degrees()) {
        data_[idx] -= degree;
        if (data_[idx] == 0) {
            data_.erase(idx);
        } else if (data_[idx] < 0) {
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
    for (const auto& [idx, degree] : left.degrees()) {
        if (right.degrees().find(idx) != right.degrees().end()) {
            result.data_[idx] = std::min(degree, right.degrees().at(idx));
        }
    }
    return result;
}

Monomial lcm(const Monomial& left, const Monomial& right) noexcept {
    Monomial result = left;
    for (const auto& [idx, degree] : right.degrees()) {
        result.data_[idx] = std::max(result.data_[idx], degree);
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
