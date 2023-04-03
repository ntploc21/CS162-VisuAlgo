#include "TextureHolder.hpp"

TextureHolder::TextureHolder() {}

TextureHolder::~TextureHolder() {
    for (auto& pair : mTextureMap) {
        UnloadTexture(*pair.second);
    }
}

void TextureHolder::Load(Textures::ID id, const std::string& filename) {
    std::unique_ptr< Texture > texture(new Texture());
    *texture = LoadTexture(filename.c_str());
    InsertResource(id, std::move(texture));
}

void TextureHolder::Load(Textures::ID id, const std::string& filename,
                         int width, int height) {
    std::unique_ptr< Texture > texture(new Texture());
    Image img = LoadImage(filename.c_str());
    ImageResize(&img, width, height);
    *texture = LoadTextureFromImage(img);
    UnloadImage(img);
    InsertResource(id, std::move(texture));
}

void TextureHolder::LoadFromImage(Textures::ID id, Image& image) {
    std::unique_ptr< Texture > texture(new Texture());
    *texture = LoadTextureFromImage(image);
    InsertResource(id, std::move(texture));
}

void TextureHolder::LoadFromImage(Textures::ID id, Image& image, int width,
                                  int height) {
    std::unique_ptr< Texture > texture(new Texture());
    ImageResize(&image, width, height);
    *texture = LoadTextureFromImage(image);
    InsertResource(id, std::move(texture));
}

Texture& TextureHolder::Get(Textures::ID id) {
    auto found = mTextureMap.find(id);
    if (found != mTextureMap.end()) return *found->second.get();
    return *mTextureMap[Textures::Blank];
}

const Texture& TextureHolder::Get(Textures::ID id) const {
    auto found = mTextureMap.find(id);
    if (found != mTextureMap.end()) return *found->second.get();
    return *mTextureMap.at(Textures::Blank);
}

void TextureHolder::InsertResource(Textures::ID id,
                                   std::unique_ptr< Texture > texture) {
    auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
}