#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

namespace gb {
    using std::pow;  // I want to do Term<i32> and smf like.

    using u64 = std::uint64_t;
    using i64 = std::int64_t;

    namespace utils {
        void make_combinations_util_(std::vector<std::vector<i64>> *, std::vector<i64> *, const i64&, const i64&, const i64&);
        std::vector<std::vector<i64>> make_combinations(const i64&, const i64&);
    }
}
