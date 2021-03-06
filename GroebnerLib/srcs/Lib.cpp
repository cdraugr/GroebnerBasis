#include "Modular.h"

bool is_prime(const u64& number) {
    if (number == 2) {
        return true;
    }
    if (number < 2 || number % 2 == 0) {
        return false;
    }
    for(u64 i = 3, root = std::sqrt(number); i <= root; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

static void make_combi_util(std::vector<std::vector<i64>> *ans, std::vector<i64> *tmp,
        const i64& n, const i64& left, const i64& k) {
    if (k == 0) {
        ans->push_back(*tmp);
        return ;
    }

    for (i64 i = left; i < n; ++i) {
        tmp->push_back(i);
        make_combi_util(ans, tmp, n, i + 1, k - 1);
        tmp->pop_back();
    }
}

std::vector<std::vector<i64>> make_combinations(const i64& k, const i64& n) {
    std::vector<std::vector<i64>> ans;
    std::vector<i64> tmp;
    make_combi_util(&ans, &tmp, n, 0, k);
    return ans;
}
