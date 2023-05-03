#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <cstddef>
#include <map>
#include <string>

#include "Identifiers/ColorThemeIdentifiers.hpp"
#include "NonCopyable.hpp"
#include "raylib.h"

/**
 * @brief The settings class that is used to store the settings.
 * @details The settings class is used to store the settings. Also, this class
 * is using the singleton pattern to store the settings.
 * @see NonCopyable
 * @see ColorTheme::ID
 */
class Settings : private NonCopyable< Settings > {
private:
    /**
     * @brief The color struct that is used to store the color.
     * @details The color struct is used to store the color. This struct is used
     * to store the color ID, the color name, and the color.
     */
    std::size_t mCurrentColorTheme;

    /**
     * @brief The colors that are used in the application.
     * @see ColorTheme::ID
     */
    std::map< std::size_t, Color > mColors;

private:
    /**
     * @brief The constructor.
     * @details The constructor that is used to initialize the settings class.
     */
    Settings() = default;

public:
    /**
     * @brief The move constructor is deleted.
     * @details The move constructor is deleted to make the class non-copyable
     * and satisfy the singleton pattern.
     * @param other The other settings class.
     */
    Settings(Settings&&) = delete;

    /**
     * @brief The assignment move operator is deleted.
     * @details The assignment move operator is deleted to make the class
     * non-copyable and satisfy the singleton pattern.
     * @param other The other settings class.
     * @return Settings& A reference to the settings class.
     */
    Settings& operator=(Settings&&) = delete;

    /**
     * @brief The destructor.
     * @details The destructor that is used to destroy the settings class.
     */
    ~Settings();

public:
    /**
     * @brief The function that is used to get the instance of the settings
     * class.
     * @details The function that is used to get the instance of the settings
     * class.
     * @return Settings& A reference to the settings class.
     */
    static Settings& getInstance();

    /**
     * @brief The function that is used to get the color.
     * @details The function that is used to get the color.
     * @param id The color ID.
     * @return Color The color.
     * @see ColorTheme::ID
     */
    Color getColor(std::size_t id) const;

    /**
     * @brief The function that is used to load the default color theme.
     * @details The function that is used to load the default color theme.
     */
    void Load();

    /**
     * @brief The function that is used to switch the theme.
     * @details The function that is used to switch the theme.
     */
    void SwitchTheme();

private:
    void LoadDefaultColors();
    void LoadDarkColors();
    // void SaveToFile(const std::string& path);
    // void LoadFromFile(const std::string& path);
};

#endif  // SETTINGS_HPP_