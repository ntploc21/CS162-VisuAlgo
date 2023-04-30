#ifndef UTILS_HPP
#define UTILS_HPP

#include <cassert>
#include <chrono>
#include <random>

#include "raylib.h"

namespace Utils {

    int Rand(int lower, int upper);

    void DrawTextBoxed(
        Font font, const char* text, Rectangle rec, float fontSize,
        float spacing, bool wordWrap,
        Color tint);  // Draw text using font inside rectangle limits
    void DrawTextBoxedSelectable(
        Font font, const char* text, Rectangle rec, float fontSize,
        float spacing, bool wordWrap, Color tint, int selectStart,
        int selectLength, Color selectTint,
        Color selectBackTint);  // Draw text using font inside rectangle
                                // limits with support for text selection};
    bool DrawIcon(int iconID, int x, int y, int pixelSize, Color color,
                  Color hoverColor);
};  // namespace Utils

#endif  // UTILS_HPP