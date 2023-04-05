#include "CategoryInfo.hpp"

void CategoryInfo::Register(Category::ID id, Info info) {
    std::unique_ptr< Info > _info(&info);
    auto inserted = mFactories.insert(std::make_pair(id, std::move(_info)));
    assert(inserted.second);
}

const CategoryInfo::Info& CategoryInfo::Get(Category::ID id) const {
    auto found = mFactories.find(id);
    assert(found != mFactories.end());
    return *found->second.get();
}

CategoryInfo::Info::Info(Category::ID categoryID,
                         std::vector< DataStructures::ID > mDS)
    : categoryID(categoryID), mDS(mDS) {}
