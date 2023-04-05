#ifndef DSINFO_HPP
#define DSINFO_HPP

#include <cassert>
#include <map>
#include <memory>
#include <string>

#include "CategoryIdentifiers.hpp"
#include "DSIdentifiers.hpp"
#include "NonCopyable.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"

class DSInfo : private NonCopyable< DSInfo > {
private:
    struct Info {
        Info(DataStructures::ID ID, States::ID stateID, Category::ID categoryID,
             Textures::ID thumbnail, std::string name, std::string abbr);
        DataStructures::ID ID;
        States::ID stateID;
        Category::ID categoryID;
        Textures::ID thumbnail;
        std::string name;
        std::string abbr;
    };
    std::map< DataStructures::ID, std::unique_ptr< Info > > mFactories;

public:
    void Register(DataStructures::ID, Info info);
    const Info& Get(DataStructures::ID id) const;
};

#endif  // DSINFO_HPP