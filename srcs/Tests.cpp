/* ********************************************************************************************** */
/*                                                                                                */
/*   Tests.cpp                                           :::     :::    :::::::::     :::::::::   */
/*                                                      :+:     :+:   :+:       +:   :+:          */
/*   By: cdraugr- <kvm2014@bk.ru>                      +:+     +:+   +:+            +:+           */
/*                <vmkuznetsov@edu.hse.ru>            #:#+#:#+#:#    +#:#+#:#      #+#:#+#        */
/*                                                   +#+     +#+           +#+    +#+             */
/*   Created: 2019/07/08 08:23:29 by cdraugr-       #+#     #+#   +#       #+#   #+#              */
/*   Updated: 2019/07/08 08:23:42 by cdraugr-      ###     ###     #########    #########.ru      */
/*                                                                                                */
/* ********************************************************************************************** */

#include "../includes/Tests.h"

void test_Monomials() {
    Monomial monom1({15, 1, 4, 0, 0, 0, 0, 1, 0, 0, 12});
    Monomial monom2({{0, 7}, {1, 2}, {3, 1}, {7, 1}, {10, 17}});
    std::cout << "m1 = " << monom1 << '\n' << "m2 = " << monom2 << '\n';

    std::cout << "lcm(m1, m2) = " << lcm(monom1, monom2) << '\n';
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
