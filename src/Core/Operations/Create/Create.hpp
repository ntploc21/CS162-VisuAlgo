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
    // std::vector< int > CreateInput(CreateOperation::ID opType,
    //                                std::map< std::string, std::string >
    //                                params);

protected:
    int Rand(int lower, int upper);

public:
    std::vector< int > Empty();
    std::vector< int > Random();

    std::vector< int > RandomFixedSize(int nSize);

    std::vector< int > UserDefined(std::string input);

    std::vector< int > ReadFromFile(std::string inputFile);

    // void InitCreateOperations();
    // void RegisterCreateOperation(CreateOperation::ID id, );

private:
    // std::map< CreateOperation::ID, std::function< std::vector< int >(
    //                                    std::map< std::string, std::string >)
    //                                    > >
    //     mCreateOperations;
};

#endif  // CORE_OPERATIONS_CREATE_CREATE_HPP