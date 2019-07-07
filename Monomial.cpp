/* ********************************************************************************************** */
/*                                                                                                */
/*   Monomial.cpp                                        :::     :::    :::::::::     :::::::::   */
/*                                                      :+:     :+:   :+:       +:   :+:          */
/*   By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+           */
/*                <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#        */
/*                                                   +#+     +#+           +#+    +#+             */
/*   Created: 2019/07/07 15:33:22 by cdraugr-       #+#     #+#   +#       #+#   #+#              */
/*   Updated: 2019/07/07 22:47:29 by cdraugr-      ###     ###     #########    #########.ru      */
/*                                                                                                */
/* ********************************************************************************************** */

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <numeric>
#include <stdexcept>
#include <vector>

using i32 = int32_t;
using container = std::map<i32, i32>;

class Monomial {
public:
    Monomial() = default;

    Monomial(i32 value) {
        if (value) {
            data_[0] = value;
        }
    }

    Monomial(const std::vector<i32>& arguments) {
        if (arguments.size() && arguments[0]) {
            for (size_t i = 0; i != arguments.size(); ++i) {
                if (arguments[i]) {
                    data_[static_cast<i32>(i)] = arguments[i];
                }
            }
        }
    }

    Monomial(const container& arguments) {
        try {
            if ((data_[0] = arguments.at(0))) {
                for (const auto& [num, degree] : arguments) {
                    if (num > 0 && degree > 0) {
                        data_[num] = degree;
                    }
                }
            }
        } catch (std::out_of_range) {
            data_ = {};
        }
    }

    const container& data() const {
        return data_;
    }

    friend Monomial operator*(const Monomial& left, const Monomial& right) {
        if (left.data().empty() || right.data().empty()) {
            return {};
        }

        Monomial composition = left;
        composition.data_[0] *= right.data().at(0);
        for (const auto& [num, degree] : right.data()) {
            if (num) {
                composition.data_[num] += degree;
            }
        }
        return composition;
    }

    friend Monomial operator*=(Monomial& left, const Monomial& right) {
        return left = left * right;
    }

    friend bool operator==(const Monomial& left, const Monomial& right) {
        return left.data() == right.data();
    }

    friend bool operator!=(const Monomial& left, const Monomial& right) {
        return left.data() != right.data();
    }

    friend Monomial operator,(const Monomial& left, const Monomial& right) {  // gcd
        if (left.data().empty() || right.data().empty()) {
            return {};
        }

        Monomial result(std::gcd(left.data().at(0), right.data().at(0)));
        for (const auto& [num, degree] : left.data()) {
            if (num) {
                try {
                    result.data_[num] = std::min(degree, right.data().at(num));
                } catch (std::out_of_range) {
                    result.data_.erase(num);
                }
            }
        }
        return result;
    }

    Monomial lcm(const Monomial& other) const {
        if (data().empty() || other.data().empty()) {
            return {};
        }

        Monomial result = *this;
        for (const auto& [num, degree] : other.data()) {
            result.data_[num] = num ?
                std::max(result.data_[num], degree) :
                std::lcm(result.data().at(0), other.data().at(0));
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const Monomial& monom) {
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

private:
    container data_{};  // (variable number) && (power)
};

int main() {
    Monomial monom1({15, 1, 4, 0, 0, 0, 0, 1, 0, 0, 12});
    Monomial monom2({{0, 7}, {1, 2}, {3, 1}, {7, 1}, {10, 17}});
    std::cout << "m1 = " << monom1 << '\n' << "m2 = " << monom2 << '\n';

    std::cout << "lcm(m1, m2) = " << monom1.lcm(monom2) << '\n';
    std::cout << "gcd(m1, m2) = " << (monom1, monom2) << '\n';
    std::cout << "-----------------------------------------------\n";

    Monomial monom3({{0, 2}, {2, 5}, {4, 2}});
    Monomial monom4({{0, -1}, {2, 12}, {3, 1}});
    std::cout << "m3 = " << monom3 << '\n' << "m4 = " << monom4 << "\n\n";
    std::cout << "m3 * m4 =\t" << monom3 * monom4 << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "m3 *= m4 =\t" << (monom3 *= monom4) << '\n';
    std::cout << "m3 =\t\t" << monom3 << '\n';
    std::cout << "-----------------------------------------------\n";

    Monomial monom5({2, 3, 0, 4});
    Monomial monom6({1, 3, 0, 4});
    std::cout << (monom5 == monom6) << '\t'
            << (monom5 == 2 * monom6) << '\t'
            << (3 * monom5 == monom6 * 6) << '\n';
}
