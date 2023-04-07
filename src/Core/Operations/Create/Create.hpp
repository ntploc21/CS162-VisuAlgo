#ifndef CORE_OPERATIONS_CREATE_CREATE_HPP
#define CORE_OPERATIONS_CREATE_CREATE_HPP

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "CreateIdentifiers.hpp"

class Create {
public:
private:
    int Rand(int lower, int upper);
    std::vector< int > Empty();
    std::vector< int > Random();

    std::vector< int > RandomFixedSize(int nSize);

    std::vector< int > UserDefined(std::string input);

    std::vector< int > ReadFromFile(std::string inputFile);

private:
};

#endif  // CORE_OPERATIONS_CREATE_CREATE_HPP