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

/**
 * @brief The image holder class that is used to store the images.
 * @details The image holder class is used to store the images. Also, this class
 * is using the flyweight pattern to store the images.
 * @see NonCopyable
 * @see Image
 */
class TextureHolder : private NonCopyable< TextureHolder > {
public:
    /**
     * @brief The constructor.
     * @details The constructor that is used to initialize the image holder.
     */
    TextureHolder();

    /**
     * @brief The destructor.
     * @details The destructor that is used to destroy the image holder.
     */
    ~TextureHolder();

    /**
     * @brief Load the image from the file.
     * @details This function is used to load the image from the file.
     * @param id The image ID.
     * @param filename The image filename.
     */
    void Load(Textures::ID id, const std::string& filename);

    /**
     * @brief Load the texture from the file.
     * @details This function is used to load the texture from the file.
     * @param id The image ID.
     * @param filename The image filename.
     * @param width The image width.
     * @param height The image height.
     * @param cropCenter The flag that indicates whether the image should be
     * cropped from the center.
     * @see Texture::ID
     */
    void Load(Textures::ID id, const std::string& filename, int width,
              int height, bool cropCenter = false);

    /**
     * @brief Load the texture from the image.
     * @details This function is used to load the texture from the image.
     * @param id The image ID.
     * @param image The image.
     * @see Texture::ID
     */
    void LoadFromImage(Textures::ID id, Image& image);

    /**
     * @brief Load the texture from the image and crop it to the specified width
     * and height.
     * @details This function is used to load the texture from the image and
     * crop it to the specified width and height.
     * @param id The image ID.
     * @param image The image.
     * @param width The image width.
     * @param height The image height.
     * @see Texture::ID
     */
    void LoadFromImage(Textures::ID id, Image& image, int width, int height);

    /**
     * @brief Get the texture.
     * @details This function is used to retrieve the texture.
     * @param id The image ID.
     * @return The image.
     * @see Texture::ID
     */
    Texture& Get(Textures::ID id);

    /**
     * @brief Get the texture.
     * @details This function is used to retrieve the texture.
     * @param id The image ID.
     * @return The image.
     * @see Texture::ID
     */
    const Texture& Get(Textures::ID id) const;

private:
    /**
     * @brief Insert the texture to the map.
     * @details This function is used to insert the texture to map.
     * @param id The image ID.
     * @param texture The texture.
     * @see Texture::ID
     */
    void InsertResource(Textures::ID id, std::unique_ptr< Texture > texture);

private:
    /**
     * @brief The texture map.
     * @details The texture map that is used to store the textures. As the
     * flyweight pattern, the textures are stored in the map and the textures
     * are retrieved from the map.
     */
    std::map< Textures::ID, std::unique_ptr< Texture > > mTextureMap;
};

#endif  // IMAGEHOLDER_HPP