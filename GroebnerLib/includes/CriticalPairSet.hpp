#pragma once

#include "CriticalPair.hpp"

namespace gb {

template <typename T, typename Comp = LexCoefComp>
class CriticalPairSet {
public:
    using container = std::set<CriticalPair<T, Comp>>;
    using iterator = typename container::iterator;

    explicit CriticalPairSet();
    explicit CriticalPairSet(const PolynomialSet<T, Comp>&);

    const container& GetCriticalPairs() const noexcept;
    container& GetCriticalPairs() noexcept;

    bool empty() const noexcept;

    void insert(const CriticalPair<T, Comp>&);
    iterator erase(iterator);

private:
    container critical_pairs_;
};

template <typename T, typename Comp>
CriticalPairSet<T, Comp>::CriticalPairSet() = default;

template <typename T, typename Comp>
CriticalPairSet<T, Comp>::CriticalPairSet(const PolynomialSet<T, Comp>& polynomial_set) {
    for (auto it = polynomial_set.GetPolynomials().begin(); it != polynomial_set.GetPolynomials().end(); ++it) {
        for (auto jt = polynomial_set.GetPolynomials().begin(); jt != it; ++jt) {
            critical_pairs_.insert(CriticalPair(*it, *jt));
        }
    }
}

template <typename T, typename Comp>
typename CriticalPairSet<T, Comp>::container& CriticalPairSet<T, Comp>::GetCriticalPairs() noexcept {
    return critical_pairs_;
}

template <typename T, typename Comp>
const typename CriticalPairSet<T, Comp>::container& CriticalPairSet<T, Comp>::GetCriticalPairs() const noexcept {
    return critical_pairs_;
}

template <typename T, typename Comp>
bool CriticalPairSet<T, Comp>::empty() const noexcept {
    return GetCriticalPairs().empty();
}

template <typename T, typename Comp>
void CriticalPairSet<T, Comp>::insert(const CriticalPair<T, Comp>& critical_pair) {
    GetCriticalPairs().insert(critical_pair);
}

template <typename T, typename Comp>
typename CriticalPairSet<T, Comp>::iterator
CriticalPairSet<T, Comp>::erase(typename CriticalPairSet<T, Comp>::iterator it) {
    return GetCriticalPairs().erase(it);
}

template <typename T, typename Comp>
std::ostream& operator<<(std::ostream& out, const CriticalPairSet<T, Comp>& critical_pairs) {
    for (auto it = critical_pairs.GetCriticalPairs().begin(); it != critical_pairs.GetCriticalPairs().end(); ++it) {
        if (it != critical_pairs.GetCriticalPairs().begin()) {
            out << '\n';
        }
        out << *it;
    }
    return out;
}

}  // namespace gb
