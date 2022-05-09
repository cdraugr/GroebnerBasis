#include "Modular.hpp"

namespace gb {
namespace utils {

void make_combinations_util_(std::vector<std::vector<gb::i64>> *ans, std::vector<gb::i64> *tmp,
        const gb::i64& n, const gb::i64& left, const gb::i64& k) {
    if (k == 0) {
        ans->push_back(*tmp);
        return ;
    }

    for (auto i = left; i < n; ++i) {
        tmp->push_back(i);
        make_combinations_util_(ans, tmp, n, i + 1, k - 1);
        tmp->pop_back();
    }
}

std::vector<std::vector<gb::i64>> make_combinations(const gb::i64& k, const gb::i64& n) {
    std::vector<std::vector<gb::i64>> ans;
    std::vector<gb::i64> tmp;
    make_combinations_util_(&ans, &tmp, n, 0, k);
    return ans;
}

}  // namespace utils
}  // namespace gb
