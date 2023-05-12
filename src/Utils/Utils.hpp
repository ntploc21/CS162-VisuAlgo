#ifndef UTILS_HPP
#define UTILS_HPP

#include <cassert>
#include <chrono>
#include <random>

#include "raylib.h"
#include "tinyfiledialogs.h"

namespace Utils {
    std::string OpenFileDiaglog(std::string title, std::string description,
                                std::vector< std::string > filters,
                                std::string defaultPath,
                                bool allowMultipleSelect);

    std::string ReadInputFromFile(std::string path);

    // Returns a random integer in the range [lower, upper]
    int Rand(int lower, int upper);

    // Draw text using font inside rectangle limits
    void DrawTextBoxed(Font font, const char* text, Rectangle rec,
                       float fontSize, float spacing, bool wordWrap,
                       Color tint);

    // Draw text using font inside rectangle limits with support for text
    // selection};
    void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec,
                                 float fontSize, float spacing, bool wordWrap,
                                 Color tint, int selectStart, int selectLength,
                                 Color selectTint, Color selectBackTint);
    bool DrawIcon(int iconID, int x, int y, int pixelSize, Color color,
                  Color hoverColor);
};  // namespace Utils

#endif  // UTILS_HPP