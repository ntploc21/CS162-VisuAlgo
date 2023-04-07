#include "Create.hpp"

#include <sstream>

int Create::Rand(int lower, int upper) {
    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    assert(lower <= upper);
    return lower + rng() % (upper - lower + 1);
}

std::vector< int > Create::Empty() { return std::vector< int >(); }

std::vector< int > Create::Random() {
    int nSize = Rand(1, 10);
    return RandomFixedSize(nSize);
}

std::vector< int > Create::RandomFixedSize(int nSize) {
    std::vector< int > answer(nSize);
    for (int& v : answer) v = Rand(1, 99);
    return answer;
}

std::vector< int > Create::UserDefined(std::string input) {
    std::vector< int > answer;

    std::istringstream f(input);
    std::string s;
    while (std::getline(f, s, ',')) {
        try {
            answer.push_back(atoi(s.c_str()));
        } catch (char* e) {
        }
    }
    return answer;
}

std::vector< int > Create::ReadFromFile(std::string inputFile) {
    // will be implemented later
    return std::vector< int >();
}
