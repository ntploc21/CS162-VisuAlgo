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
    std::map< ColorTheme::ID, Color > mColors;

private:
    Settings() = default;

public:
    Settings(Settings&&) = delete;
    Settings& operator=(Settings&&) = delete;
    ~Settings();

public:
    static Settings& getInstance();
    void LoadDefaultColors();

    Color& getColor(ColorTheme::ID id);
    Color getColor(ColorTheme::ID id) const;

    void SaveToFile(const std::string& path);
    void LoadFromFile(const std::string& path);
};

#endif  // SETTINGS_HPP_