#include "Random.hpp"

int Random::Rand(int lower, int upper) {
    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    if (lower > upper) std::__throw_domain_error("Invalid range");
    return lower + rng() % (upper - lower + 1);
}