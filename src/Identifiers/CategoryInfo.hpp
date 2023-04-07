#ifndef CATEGORYINFO_HPP
#define CATEGORYINFO_HPP

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "CategoryIdentifiers.hpp"
#include "DSIdentifiers.hpp"
#include "NonCopyable.hpp"

class CategoryInfo : private NonCopyable< CategoryInfo > {
private:
    struct Info {
        Info(Category::ID categoryID, std::vector< DataStructures::ID > mDS,
             std::string name);
        Category::ID categoryID;
        std::string categoryName;
        std::vector< DataStructures::ID > mDS;
    };
    std::map< Category::ID, Info > mFactories;

public:
    void Register(Category::ID, Info info);
    const Info& Get(Category::ID id) const;
};

#endif  // CATEGORYINFO_HPP