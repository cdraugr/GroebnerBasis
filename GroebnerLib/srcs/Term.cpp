#include "Term.hpp"

namespace gb {

Term::Term() = default;

Term::Term(const std::vector<gb::i64>& arguments) {
    if (arguments.empty()) {
        return ;
    }
    for (size_t i = 0; i != arguments.size(); ++i) {
        if (arguments[i] != 0) {
            data_[static_cast<gb::i64>(i)] = arguments[i];
        }
    }
}

inline Term Term::term_from_map(const Term::container& arguments) {
    Term term;
    for (const auto& [idx, degree] : arguments) {
        if (idx >= 0 && degree > 0) {
            term.data_[idx] = degree;
        }
    }
    return term;
}

const Term::container& Term::GetDegrees() const noexcept {
    return data_;
}

gb::i64 Term::GetDegree(const gb::i64& index) const noexcept {
    return GetDegrees().find(index) != GetDegrees().end() ? GetDegrees().at(index) : 0;
}

gb::i64 Term::GetLastVariableIndex() const noexcept {
    return IsOne() ? 0 : GetDegrees().crbegin()->first;
}

gb::i64 deg(const Term& term) noexcept {
    gb::i64 sum = 0;
    for (const auto& idx_degree : term.GetDegrees()) {
        sum += idx_degree.second;
    }
    return sum;
}

std::list<Term> GetAllDivisors_(const Term& term, const gb::i64& start_index) {
    if (term.IsOne()) {
        return {term};
    }
    std::list<Term> result({term});
    for (const auto& idx_degree : term.GetDegrees()) {
        if (start_index > idx_degree.first) {
            continue;
        }
        auto sub_degrees = term.GetDegrees();
        --sub_degrees[idx_degree.first];
        result.splice(result.end(), GetAllDivisors_(Term::term_from_map(sub_degrees), idx_degree.first));
    }
    return result;
}

std::list<Term> GetAllDivisors(const Term& term) {
    return GetAllDivisors_(term, 0);
}

bool Term::IsOne() const noexcept {
    return GetDegrees().empty();
}

bool Term::IsDivisibleBy(const Term& other) const noexcept {
    for (const auto& [idx, degree] : other.GetDegrees()) {
        if (GetDegree(idx) < degree) {
            return false;
        }
    }
    return true;
}

Term& Term::operator*=(const Term& other) noexcept {
    for (const auto& [idx, degree] : other.GetDegrees()) {
        data_[idx] += degree;
    }
    return *this;
}

Term operator*(Term left, const Term& right) noexcept {
    left *= right;
    return left;
}

Term& Term::operator/=(const Term& other) {
    for (const auto& [idx, degree] : other.GetDegrees()) {
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

Term operator/(Term left, const Term& right) {
    left /= right;
    return left;
}

bool operator==(const Term& left, const Term& right) noexcept {
    return left.GetDegrees() == right.GetDegrees();
}

bool operator!=(const Term& left, const Term& right) noexcept {
    return !(left == right);
}

Term gcd(const Term& left, const Term& right) noexcept {
    Term result;
    for (const auto& [idx, degree] : left.GetDegrees()) {
        if (right.GetDegrees().find(idx) != right.GetDegrees().end()) {
            result.data_[idx] = std::min(degree, right.GetDegrees().at(idx));
        }
    }
    return result;
}

Term lcm(const Term& left, const Term& right) noexcept {
    Term result = left;
    for (const auto& [idx, degree] : right.GetDegrees()) {
        result.data_[idx] = std::max(result.data_[idx], degree);
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Term& term) noexcept {
    if (term.IsOne()) {
        return out << 1;
    }

    for (auto it = term.GetDegrees().begin(); it != term.GetDegrees().end(); ++it) {
        out << "x_(" << it->first + 1 << ')';
        if (it->second > 1) {
            out << "^{" << it->second << '}';
        }
        if (it != std::prev(term.GetDegrees().end())) {
            out << '*';
        }
    }
    return out;
}

}  // namespace gb
