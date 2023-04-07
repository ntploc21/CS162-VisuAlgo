#include "CategoryInfo.hpp"

void CategoryInfo::Register(Category::ID id, Info info) {
    auto inserted = mFactories.insert(std::make_pair(id, info));
    assert(inserted.second);
}

const CategoryInfo::Info& CategoryInfo::Get(Category::ID id) const {
    auto found = mFactories.find(id);
    assert(found != mFactories.end());
    return found->second;
}

CategoryInfo::Info::Info(Category::ID categoryID,
                         std::vector< DataStructures::ID > mDS,
                         std::string name)
    : categoryID(categoryID), mDS(mDS), categoryName(name) {}
