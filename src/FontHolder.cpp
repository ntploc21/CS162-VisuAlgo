#include "FontHolder.hpp"

void FontHolder::Load(Fonts::ID id, const std::string& filename) {
    std::unique_ptr< Font > font(new Font());
    // *font = LoadFont(filename.c_str());
    *font = LoadFontEx(filename.c_str(), 72, NULL, 0);
    InsertResource(id, std::move(font));
}

Font& FontHolder::Get(Fonts::ID id) {
    auto found = mFontMap.find(id);
    assert(found != mFontMap.end());
    return *found->second.get();
    // return mFontMap[Fonts::Default];
}

const Font& FontHolder::Get(Fonts::ID id) const {
    auto found = mFontMap.find(id);
    assert(found != mFontMap.end());
    return *found->second.get();
}

void FontHolder::InsertResource(Fonts::ID id, std::unique_ptr< Font > font) {
    auto inserted = mFontMap.insert(std::make_pair(id, std::move(font)));
    assert(inserted.second);
}

FontHolder::FontHolder() {}

FontHolder::~FontHolder() {
    for (auto& pair : mFontMap) {
        UnloadFont(*pair.second);
    }
}