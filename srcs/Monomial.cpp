/* ********************************************************************************************** */
/*                                                                                                */
/*   Monomial.cpp                                        :::     :::    :::::::::     :::::::::   */
/*                                                      :+:     :+:   :+:       +:   :+:          */
/*   By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+           */
/*                <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#        */
/*                                                   +#+     +#+           +#+    +#+             */
/*   Created: 2019/07/07 15:33:22 by cdraugr-       #+#     #+#   +#       #+#   #+#              */
/*   Updated: 2019/07/08 08:56:54 by cdraugr-      ###     ###     #########    #########.ru      */
/*                                                                                                */
/* ********************************************************************************************** */

#include "../includes/Monomial.h"

Monomial::Monomial() = default;

Monomial::Monomial(i32 value) {
    if (value) {
        data_[0] = value;
    }
}

Monomial::Monomial(const std::vector<i32>& arguments) {
    if (arguments.size() && arguments[0]) {
        for (size_t i = 0; i != arguments.size(); ++i) {
            if (arguments[i]) {
                data_[static_cast<i32>(i)] = arguments[i];
            }
        }
    }
}

Monomial::Monomial(const container& arguments) {
    if (arguments.find(0) != arguments.end() && (data_[0] = arguments.at(0))) {
        for (const auto& [num, degree] : arguments) {
            if (num > 0 && degree > 0) {
                data_[num] = degree;
            }
        }
    }
}

Monomial& Monomial::operator*=(const Monomial& other) noexcept {
    if (data().empty() || other.data().empty()) {
        return *this = {};
    }

    data_[0] *= other.data().at(0);
    for (const auto& [num, degree] : other.data()) {
        if (num) {
            data_[num] += degree;
        }
    }
    return *this;
}

Monomial operator*(const Monomial& left, const Monomial& right) noexcept {
    Monomial composition = left;
    return composition *= right;
}

bool operator==(const Monomial& left, const Monomial& right) noexcept {
    return left.data() == right.data();
}

bool operator!=(const Monomial& left, const Monomial& right) noexcept {
    return !(left == right);
}

Monomial operator,(const Monomial& left, const Monomial& right) noexcept {  // gcd
    if (left.data().empty() || right.data().empty()) {
        return {};
    }

    Monomial result(std::gcd(left.data().at(0), right.data().at(0)));
    for (const auto& [num, degree] : left.data()) {
        if (num) {
            if (right.data().find(num) != right.data().end()) {
                result.data_[num] = std::min(degree, right.data().at(num));
            } else {
                result.data_.erase(num);
            }
        }
    }
    return result;
}

Monomial lcm(const Monomial& left, const Monomial& right) noexcept {
    if (left.data().empty() || right.data().empty()) {
        return {};
    }

    Monomial result = left;
    for (const auto& [num, degree] : right.data()) {
        result.data_[num] = num ?
            std::max(result.data_[num], degree) :
            std::lcm(result.data().at(0), right.data().at(0));
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Monomial& monom) noexcept {
    if (monom.data().empty()) {
        return out << 0;
    }

    for (const auto& [num, degree] : monom.data()) {
        if (num > 0) {
            out << "x_(" << num << ')';
            if (degree > 1) {
                out << "^(" << degree << ')';
            }
            if (num < (*monom.data().crbegin()).first) {
                out << '*';
            }
        } else {
            if (degree == -1) {
                out << '-';
            } else if (degree != 1) {
                out << degree << '*';
            }
        }
    }
    return out;
}

const Monomial::container& Monomial::data() const noexcept {  // private
    return data_;
}
