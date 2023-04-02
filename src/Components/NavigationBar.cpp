#include "NavigationBar.hpp"

#include "../Global.hpp"
// #include "raylib.h"
// #define RAYGUI_STATIC
#include <iostream>

NavigationBar::NavigationBar(FontHolder* fonts) : fonts(fonts) {}

NavigationBar::NavigationBar() {}

void NavigationBar::DrawCurrent() {
    Rectangle rec = (Rectangle){0, 0, global::SCREEN_WIDTH, 40};
    DrawRectangleRec(rec, BLACK);
    if (DrawLogo()) toHomepage();
    if (DrawSettings()) toSettings();
}

void NavigationBar::SetHomepageLink(std::function< void() > homepageLink) {
    toHomepage = homepageLink;
}

void NavigationBar::SetSettings(std::function< void() > settingsLink) {
    toSettings = settingsLink;
}

bool NavigationBar::DrawLogo() {
    // render
    Font logoFont = fonts->Get(Fonts::Silkscreen);
    float fSpanWidth = MeasureTextEx(logoFont, "Visu", 32, 1).x;
    DrawTextEx(logoFont, "Visu", {10, 4}, 32, 1, WHITE);
    DrawTextEx(logoFont, "Algo", {10 + fSpanWidth, 4}, 32, 1, ORANGE);
    float logoWidth = MeasureTextEx(logoFont, "VisuAlgo", 32, 1).x;
    Rectangle logoBond = (Rectangle){10, 4, logoWidth, 32};

    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), logoBond));
}

bool NavigationBar::DrawSettings() {
    Font settingsFont = fonts->Get(Fonts::Silkscreen);
    float spanWidth = MeasureTextEx(settingsFont, "Settings", 24, -0.1).x;
    Color settingsColor = (Color){25, 125, 84, 255};

    float paddingX = 8, paddingY = 2;
    float posX = 1075, posY = 8;
    Rectangle settingsBound =
        (Rectangle){posX - paddingX, posY - paddingY, spanWidth + paddingX * 2,
                    24 + 2 * paddingY};

    // render
    Color textColor = settingsColor;
    if (CheckCollisionPointRec(GetMousePosition(), settingsBound)) {
        textColor = (Color){10, 88, 202, 255};
    }
    DrawTextEx(settingsFont, "Settings", {posX, posY}, 24, -0.1, textColor);
    DrawRectangleLinesEx(settingsBound, 1, settingsColor);

    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), settingsBound));
}

NavigationBar::~NavigationBar() {}