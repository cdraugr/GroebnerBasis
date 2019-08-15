#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

using u64 = uint64_t;
using i64 = int64_t;

namespace gb {
    using std::pow;  // I want to do Term<i32> and smf like.
}

bool is_prime(const u64&);
std::vector<std::vector<i64>> make_combinations(const i64&, const i64&);
