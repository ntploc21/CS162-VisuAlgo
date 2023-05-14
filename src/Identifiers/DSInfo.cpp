#include "DSInfo.hpp"

void DSInfo::Register(DataStructures::ID id, Info info) {
    auto inserted = mFactories.insert(std::make_pair(id, info));
    assert(inserted.second);
}

DSInfo::Info DSInfo::Get(DataStructures::ID id) const {
    auto found = mFactories.find(id);
    assert(found != mFactories.end());
    return found->second;
}

DSInfo::Info::Info(DataStructures::ID ID, States::ID stateID,
                   Category::ID categoryID, Textures::ID thumbnail,
                   std::string name, std::string abbr)
    : ID(ID), stateID(stateID), categoryID(categoryID), thumbnail(thumbnail),
      name(name), abbr(abbr) {}
