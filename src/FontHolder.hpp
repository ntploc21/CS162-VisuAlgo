#ifndef FONTHOLDER_HPP
#define FONTHOLDER_HPP

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "ResourceIdentifiers.hpp"
#include "raygui.h"

class FontHolder : private NonCopyable< FontHolder > {
public:
    FontHolder();
    ~FontHolder();
    void Load(Fonts::ID id, const std::string& filename);
    Font& Get(Fonts::ID id);
    const Font& Get(Fonts::ID id) const;

private:
    void InsertResource(Fonts::ID id, std::unique_ptr< Font > font);

private:
    std::map< Fonts::ID, std::unique_ptr< Font > > mFontMap;
};
#endif  // FONTHOLDER_HPP