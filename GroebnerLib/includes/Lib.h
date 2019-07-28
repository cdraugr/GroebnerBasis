#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;

bool is_prime(const u64&);
std::vector<std::vector<i64>> makeCombi(const i64&, const i64&);
