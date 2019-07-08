/* ********************************************************************************************** */
/*                                                                                                */
/*   Monomial.h                                          :::     :::    :::::::::     :::::::::   */
/*                                                      :+:     :+:   :+:       +:   :+:          */
/*   By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+           */
/*                <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#        */
/*                                                   +#+     +#+           +#+    +#+             */
/*   Created: 2019/07/08 06:59:23 by cdraugr-       #+#     #+#   +#       #+#   #+#              */
/*   Updated: 2019/07/08 08:58:11 by cdraugr-      ###     ###     #########    #########.ru      */
/*                                                                                                */
/* ********************************************************************************************** */

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using i32 = int32_t;

class Monomial {
public:
    using container = std::map<i32, i32>;

    Monomial();
    Monomial(i32);
    Monomial(const std::vector<i32>&);
    Monomial(const container&);

    Monomial& operator*=(const Monomial&) noexcept;
    friend Monomial operator*(const Monomial&, const Monomial&) noexcept;

    friend bool operator==(const Monomial&, const Monomial&) noexcept;
    friend bool operator!=(const Monomial&, const Monomial&) noexcept;

    friend Monomial operator,(const Monomial&, const Monomial&) noexcept;  // gcd
    friend Monomial lcm(const Monomial&, const Monomial&) noexcept;

    friend std::ostream& operator<<(std::ostream&, const Monomial&) noexcept;

private:
    container data_{};  // (variable number) && (power)
    const container& data() const noexcept;
};
