#include <algorithm>
#include <numeric>
#include "../includes/Monomial.h"

namespace bg {
    Monomial::Monomial() = default;

    Monomial::Monomial(i32 value)
        : coefficient_{value} {}

    Monomial::Monomial(const Monomial::type_name& value)
        : coefficient_{value} {}

    Monomial::Monomial(const std::vector<i32>& arguments, const Monomial::type_name& value)
        : coefficient_{value} {
        if (coefficient() != 0 && !arguments.empty()) {
            for (size_t i = 0; i != arguments.size(); ++i) {
                if (arguments[i] != 0) {
                    data_[static_cast<i32>(i)] = arguments[i];
                }
            }
        }
    }

    Monomial::Monomial(const container& arguments, const Monomial::type_name& value)
        : coefficient_{value} {
        if (coefficient() != 0) {
            for (const auto& [num, degree] : arguments) {
                if (num >= 0 && degree > 0) {
                    data_[num] = degree;
                }
            }
        }
    }

    Monomial::type_name& Monomial::coefficient() noexcept {
        return coefficient_;
    }

    const Monomial::type_name& Monomial::coefficient() const noexcept {
        return coefficient_;
    }

    const Monomial::container& Monomial::degrees() const noexcept {
        return data_;
    }

    i32 Monomial::GetDegree(i32 index) const noexcept {
        return degrees().find(index) != degrees().end() ?
            degrees().at(index) :
            0;
    }

    i32 deg(const Monomial& monom) noexcept {
        i32 sum = 0;
        for (const auto& [num, degree] : monom.degrees()) {
            sum += degree;
        }
        return sum;
    }

    bool Monomial::IsDividedBy(const Monomial& other) const noexcept {
        if (other == 0) {
            return false;
        }

        for (const auto& [num, degree] : other.degrees()) {
            if (GetDegree(num) < degree) {
                return false;
            }
        }
        return true;
    }

    Monomial Monomial::operator-() const noexcept {
        return Monomial(degrees(), -coefficient());
    }

    Monomial Monomial::operator+() const noexcept {
        return Monomial(degrees(), coefficient());
    }

    Monomial& Monomial::operator*=(const Monomial& other) noexcept {
        coefficient_ *= other.coefficient();
        for (const auto& [num, degree] : other.degrees()) {
            data_[num] += degree;
        }
        return *this;
    }

    Monomial operator*(Monomial left, const Monomial& right) noexcept {
        left *= right;
        return left;
    }

    Monomial& Monomial::operator/=(const Monomial& other) noexcept {
        coefficient_ /= other.coefficient();
        for (const auto& [num, degree] : other.degrees()) {
            data_[num] -= degree;
            if (data_[num] == 0) {
                data_.erase(num);
            } else if (data_[num] < 0) {
                *this = {0};
                break;
            }
        }
        return *this;
    }

    Monomial operator/(Monomial left, const Monomial& right) noexcept {
        left /= right;
        return left;
    }

    bool operator==(const Monomial& left, const Monomial& right) noexcept {
        return left.coefficient() == right.coefficient() && left.degrees() == right.degrees();
    }

    bool operator!=(const Monomial& left, const Monomial& right) noexcept {
        return !(left == right);
    }

    Monomial operator,(const Monomial& left, const Monomial& right) noexcept {  // gcd
        Monomial result((left.coefficient(), right.coefficient()));
        for (const auto& [num, degree] : left.degrees()) {
            if (right.degrees().find(num) != right.degrees().end()) {
                result.data_[num] = std::min(degree, right.degrees().at(num));
            }
        }
        return result;
    }

    Monomial lcm(const Monomial& left, const Monomial& right) noexcept {
        Monomial result = left;
        result.coefficient_ = lcm(left.coefficient(), right.coefficient());
        for (const auto& [num, degree] : right.degrees()) {
            result.data_[num] = std::max(result.data_[num], degree);
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& out, const Monomial& monom) noexcept {
        if (monom.degrees().empty()) {
            return out << monom.coefficient();
        }

        if (monom.coefficient() == -1) {
            out << '-';
        } else if (monom.coefficient() != 1) {
            out << monom.coefficient() << '*';
        }

        for (const auto& [num, degree] : monom.degrees()) {
            out << "x_(" << num + 1 << ')';
            if (degree > 1) {
                out << "^{" << degree << '}';
            }
            if (num < (*monom.degrees().crbegin()).first) {
                out << '*';
            }
        }
        return out;
    }
}
