#include "Random.hpp"

#include <iostream>

int Random::Rand(int lower, int upper) {
    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    if (lower > upper) std::__throw_domain_error("Invalid range");
    std::cout << lower << " " << upper << " -> "
              << lower + rng() % (upper - lower + 1) << std::endl;
    return lower + rng() % (upper - lower + 1);
}