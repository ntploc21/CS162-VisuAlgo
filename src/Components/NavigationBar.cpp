#include "NavigationBar.hpp"

#include "../Global.hpp"
// #include "raylib.h"
// #define RAYGUI_STATIC
#include <iostream>

#include "StateIdentifiers.hpp"

NavigationBar::NavigationBar(FontHolder* fonts) : fonts(fonts) {}

NavigationBar::NavigationBar() {}

void NavigationBar::DrawCurrent() {
    Rectangle rec = (Rectangle){0, 0, global::SCREEN_WIDTH, 40};
    DrawRectangleRec(rec, BLACK);
    if (DrawLogo()) toLink(homepageID);
    if (DrawSettings()) toLink(settingsID);
}

void NavigationBar::SetHomepageID(States::ID id) { homepageID = id; }

void NavigationBar::SetSettingsID(States::ID id) { settingsID = id; }

void NavigationBar::SetDirectLink(std::function< void(States::ID) > link) {
    toLink = link;
}

void NavigationBar::SetCategory(std::string category) {
    currentCategory = category;
}

void NavigationBar::InsertTitle(std::string title, States::ID stateID) {
    auto inserted = mTitles.insert(std::make_pair(title, stateID));
    assert(inserted.second);
}

void NavigationBar::ClearTitle() { mTitles.clear(); }

bool NavigationBar::DrawLogo() {
    // render
    Font logoFont = fonts->Get(Fonts::Silkscreen);
    float fSpanWidth = MeasureTextEx(logoFont, "Visu", 32, 1).x;
    DrawTextEx(logoFont, "Visu", {10, 4}, 32, 1, WHITE);
    DrawTextEx(logoFont, "Algo", {10 + fSpanWidth, 4}, 32, 1, ORANGE);
    float logoWidth = MeasureTextEx(logoFont, "VisuAlgo", 32, 1).x;
    Rectangle logoBond = (Rectangle){10, 4, logoWidth, 32};

    if (currentCategory.size()) {
        Font font = fonts->Get(Fonts::Default);
        float x = logoBond.x + logoBond.width;
        float y = logoBond.y + 5;
        DrawTextEx(font, ("/" + currentCategory).c_str(), {x, y}, 24, 0, WHITE);
    }

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