#ifndef IMAGEHOLDER_HPP
#define IMAGEHOLDER_HPP

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "Identifiers/ResourceIdentifiers.hpp"
#include "NonCopyable.hpp"
#include "raygui.h"

class TextureHolder : private NonCopyable< TextureHolder > {
public:
    TextureHolder();
    ~TextureHolder();
    void Load(Textures::ID id, const std::string& filename);
    void Load(Textures::ID id, const std::string& filename, int width,
              int height);
    void LoadFromImage(Textures::ID id, Image& image);
    void LoadFromImage(Textures::ID id, Image& image, int width, int height);
    Texture& Get(Textures::ID id);
    const Texture& Get(Textures::ID id) const;

private:
    void InsertResource(Textures::ID id, std::unique_ptr< Texture > texture);

private:
    std::map< Textures::ID, std::unique_ptr< Texture > > mTextureMap;
};

#endif  // IMAGEHOLDER_HPP