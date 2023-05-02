#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <cstddef>
#include <map>
#include <string>

#include "Identifiers/ColorThemeIdentifiers.hpp"
#include "NonCopyable.hpp"
#include "raylib.h"

class Settings : private NonCopyable< Settings > {
private:
    std::size_t mCurrentColorTheme;
    std::map< std::size_t, Color > mColors;

private:
    Settings() = default;

public:
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;
    ~Settings();

public:
    static Settings& getInstance();
    Color getColor(std::size_t id) const;
    void Load();
    void SwitchTheme();

private:
    void LoadDefaultColors();
    void LoadDarkColors();
    // void SaveToFile(const std::string& path);
    // void LoadFromFile(const std::string& path);
};

#endif  // SETTINGS_HPP_