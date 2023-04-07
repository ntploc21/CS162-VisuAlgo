#include "Create.hpp"

#include <sstream>

Create::Create() { InitCreateOperations(); }

Create::~Create() {}

std::vector< int > Create::CreateInput(
    CreateOperation::ID opType, std::map< std::string, std::string > params) {
    return mCreateOperations[opType](params);
}

int Create::Rand(int lower, int upper) {
    std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());
    assert(lower <= upper);
    return lower + rng() % (upper - lower + 1);
}

std::vector< int > Create::Empty(std::map< std::string, std::string > params) {
    return std::vector< int >();
}

std::vector< int > Create::Random(std::map< std::string, std::string > params) {
    int nSize = Rand(1, 10);
    params["nSize"] = (char)(nSize + '0');
    return RandomFixedSize(params);
}

std::vector< int > Create::RandomFixedSize(
    std::map< std::string, std::string > params) {
    int nSize = atoi(params["nSize"].c_str());
    std::vector< int > answer(nSize);
    for (int& v : answer) v = Rand(1, 99);
    return answer;
}

std::vector< int > Create::UserDefined(
    std::map< std::string, std::string > params) {
    std::vector< int > answer;

    std::istringstream f(params["input"]);
    std::string s;
    while (std::getline(f, s, ',')) {
        try {
            answer.push_back(atoi(s.c_str()));
        } catch (char* e) {
        }
    }
    return answer;
}

std::vector< int > Create::ReadFromFile(
    std::map< std::string, std::string > params) {
    // will be implemented later
    return std::vector< int >();
}

void Create::InitCreateOperations() {
    mCreateOperations.insert(
        std::make_pair(CreateOperation::Empty,
                       [this](std::map< std::string, std::string > params) {
                           return Empty(params);
                       }));
    mCreateOperations.insert(
        std::make_pair(CreateOperation::Random,
                       [this](std::map< std::string, std::string > params) {
                           return Random(params);
                       }));
    mCreateOperations.insert(
        std::make_pair(CreateOperation::RandomFixedSize,
                       [this](std::map< std::string, std::string > params) {
                           return RandomFixedSize(params);
                       }));
    mCreateOperations.insert(
        std::make_pair(CreateOperation::UserDefined,
                       [this](std::map< std::string, std::string > params) {
                           return UserDefined(params);
                       }));
    mCreateOperations.insert(
        std::make_pair(CreateOperation::ReadFromFile,
                       [this](std::map< std::string, std::string > params) {
                           return ReadFromFile(params);
                       }));
}
