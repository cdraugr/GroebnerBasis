#pragma once

#include "CriticalPair.h"

namespace gb {

template <typename T, typename Comp = LexCoefComp>
class CriticalPairs {
public:
    using container = std::set<CriticalPair<T, Comp>>;
    using iterator = typename container::iterator;

    explicit CriticalPairs();
    explicit CriticalPairs(const PolynomialSet<T, Comp>&);

    const container& GetSet() const noexcept;
    container& GetSet() noexcept;

    bool empty() const noexcept;

    void insert(const CriticalPair<T, Comp>&);
    iterator erase(iterator);

private:
    container critical_pairs_;
};

template <typename T, typename Comp>
CriticalPairs<T, Comp>::CriticalPairs() = default;

template <typename T, typename Comp>
CriticalPairs<T, Comp>::CriticalPairs(const PolynomialSet<T, Comp>& poly_set) {
    for (auto it = poly_set.PolSet().begin(); it != poly_set.PolSet().end(); ++it) {
        for (auto jt = poly_set.PolSet().begin(); jt != it; ++jt) {
            critical_pairs_.insert(CriticalPair(*it, *jt));
        }
    }
}

template <typename T, typename Comp>
typename CriticalPairs<T, Comp>::container& CriticalPairs<T, Comp>::GetSet() noexcept {
    return critical_pairs_;
}

template <typename T, typename Comp>
const typename CriticalPairs<T, Comp>::container& CriticalPairs<T, Comp>::GetSet() const noexcept {
    return critical_pairs_;
}

template <typename T, typename Comp>
bool CriticalPairs<T, Comp>::empty() const noexcept {
    return GetSet().empty();
}

template <typename T, typename Comp>
void CriticalPairs<T, Comp>::insert(const CriticalPair<T, Comp>& critical_pair) {
    GetSet().insert(critical_pair);
}

template <typename T, typename Comp>
typename CriticalPairs<T, Comp>::iterator
CriticalPairs<T, Comp>::erase(typename CriticalPairs<T, Comp>::iterator it) {
    return GetSet().erase(it);
}

template <typename T, typename Comp>
std::ostream& operator<<(std::ostream& out, const CriticalPairs<T, Comp>& critical_pairs) {
    for (auto it = critical_pairs.GetSet().begin(); it != critical_pairs.GetSet().end(); ++it) {
        if (it != critical_pairs.GetSet().begin()) {
            out << '\n';
        }
        out << *it;
    }
    return out;
}

}  // namespace gb
