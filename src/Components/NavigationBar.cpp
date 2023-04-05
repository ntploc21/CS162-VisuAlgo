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
    if (DrawLogo()) toLink(homepageID);
    if (DrawSettings()) toLink(settingsID);
    States::ID directID = DrawTitles();
    if (directID != States::None) {
        toLink(directID);
    }
}

void NavigationBar::SetHomepageID(States::ID id) { homepageID = id; }

void NavigationBar::SetSettingsID(States::ID id) { settingsID = id; }

void NavigationBar::SetDirectLink(std::function< void(States::ID) > link) {
    toLink = link;
}

void NavigationBar::SetCategory(std::string category) {
    currentCategory = category;
}

void NavigationBar::InsertTitle(DataStructures::ID titleID, States::ID stateID,
                                std::string abbrTitle, std::string titleName) {
    TitleInfo info = {stateID, abbrTitle, titleName};
    auto inserted = mTitles.insert(std::make_pair(titleID, info));
    assert(inserted.second);
}
void NavigationBar::SetActiveTitle(DataStructures::ID titleID) {
    activeTitle = titleID;
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

States::ID NavigationBar::DrawTitles() {
    float x = 230, y = 8;
    float padding = 2;
    float margin = 2;
    for (auto title : mTitles) {
        Font font = fonts->Get(Fonts::Default);
        std::string displayedName = title.second.abbrTitle;
        Color color = (Color){170, 170, 170, 255};
        if (title.first == activeTitle) {
            font = fonts->Get(Fonts::Default_Bold);
            displayedName = title.second.titleName;
            color = WHITE;
        }
        displayedName = TextToUpper(displayedName.c_str());

        float textWidth = MeasureTextEx(font, displayedName.c_str(), 24, 0).x;
        DrawTextEx(font, displayedName.c_str(), {x, y}, 24, 0, color);
        Rectangle buttonBound =
            (Rectangle){x - padding, y - padding, textWidth + padding * 2,
                        32 + padding * 2};
        x += buttonBound.width + margin + padding;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), buttonBound))
            return title.second.stateID;
    }
    return States::None;
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