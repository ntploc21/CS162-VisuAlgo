#ifndef FONTHOLDER_HPP
#define FONTHOLDER_HPP

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "Identifiers/ResourceIdentifiers.hpp"
#include "NonCopyable.hpp"
#include "raygui.h"

/**
 * @brief The font holder class that is used to store the fonts.
 * @details The font holder class is used to store the fonts. Also, this class
 * is using the flyweight pattern to store the fonts.
 * @see NonCopyable
 * @see Font
 */
class FontHolder : private NonCopyable< FontHolder > {
public:
    /**
     * @brief The constructor.
     * @details The constructor that is used to initialize the font holder.
     */
    FontHolder();

    /**
     * @brief The destructor.
     * @details The destructor that is used to destroy the font holder.
     */
    ~FontHolder();

    /**
     * @brief Load the font from the file.
     * @details This function is used to load the font from the file.
     * @param id The font ID.
     * @param filename The font filename.
     * @see Font::ID
     */
    void Load(Fonts::ID id, const std::string& filename);

    /**
     * @brief Retrieve the font.
     * @details This function is used to retrieve the font.
     * @param id The font ID.
     * @return The font.
     * @see Font::ID
     */
    Font& Get(Fonts::ID id);

    /**
     * @brief Retrieve the font.
     * @details This function is used to retrieve the font.
     * @param id The font ID.
     * @return The font.
     * @see Font::ID
     */
    const Font& Get(Fonts::ID id) const;

private:
    /**
     * @brief Insert the font.
     * @details This function is used to insert the font.
     * @param id The font ID.
     * @param font The font.
     * @see Font::ID
     */
    void InsertResource(Fonts::ID id, std::unique_ptr< Font > font);

private:
    /**
     * @brief The font map.
     * @details The font map that is used to store the fonts. As the flyweight
     * pattern is used, the fonts are stored as the pointers and should be
     * stored in the map.
     */
    std::map< Fonts::ID, std::unique_ptr< Font > > mFontMap;
};
#endif  // FONTHOLDER_HPP