#ifndef CORE_OPERATIONS_CREATE_CREATE_HPP
#define CORE_OPERATIONS_CREATE_CREATE_HPP

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "CreateIdentifiers.hpp"

class Create {
public:
    Create();
    ~Create();
    std::vector< int > CreateInput(CreateOperation::ID opType,
                                   std::map< std::string, std::string > params);

protected:
    int Rand(int lower, int upper);

private:
    std::vector< int > Empty(std::map< std::string, std::string > params);
    std::vector< int > Random(std::map< std::string, std::string > params);

    std::vector< int > RandomFixedSize(
        std::map< std::string, std::string > params);

    std::vector< int > UserDefined(std::map< std::string, std::string > params);

    std::vector< int > ReadFromFile(
        std::map< std::string, std::string > params);

    void InitCreateOperations();
    // void RegisterCreateOperation(CreateOperation::ID id, );

private:
    std::map< CreateOperation::ID, std::function< std::vector< int >(
                                       std::map< std::string, std::string >) > >
        mCreateOperations;
};

#endif  // CORE_OPERATIONS_CREATE_CREATE_HPP