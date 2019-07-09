#include <set>
#include "MonomialOrder.h"

template <typename Comp>
class Polynomial {
public:
    using container = std::set<Monomial, Comp>;

    Polynomial();
    Polynomial(const std::vector<std::vector>&);
    Polynomial(const std::vector<std::map>&);
    Polynomial(const Monomial&);
    Polynomial(const std::vector<Monomial>&);
    Polynomial(const container&);

    // ...
private:
    container monoms_{};
};
