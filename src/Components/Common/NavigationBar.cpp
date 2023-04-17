#include "NavigationBar.hpp"

#include "Global.hpp"
// #include "raylib.h"
// #define RAYGUI_STATIC
#include <iostream>

GUI::NavigationBar::NavigationBar(FontHolder* fonts)
    : fonts(fonts), hasTitle(false), atSettings(false) {}

GUI::NavigationBar::NavigationBar() : hasTitle(false), atSettings(false) {}

bool GUI::NavigationBar::isSelectable() const { return false; }

void GUI::NavigationBar::Draw(Vector2 base) {
    bool willGotoNextScreen = false;
    Rectangle rec = (Rectangle){0, 0, global::SCREEN_WIDTH, 40};
    DrawRectangleRec(rec, BLACK);
    if (DrawLogo()) {
        toLink(homepageID);
        willGotoNextScreen = true;
    }
    if (DrawSettings()) {
        if (atSettings)
            backToPrvState();
        else {
            toLink(settingsID);
            willGotoNextScreen = true;
        }
    }

    if (hasTitle) {
        States::ID directID = DrawTitles();
        if (directID != States::None) {
            toLink(directID);
            willGotoNextScreen = true;
        }
    }
    UpdateMouseCursorWhenHover(hoverBounds, isHover, willGotoNextScreen);
    isHover = GetHoverStatus(hoverBounds, isHover, willGotoNextScreen);
}

void GUI::NavigationBar::SetHomepageID(States::ID id) { homepageID = id; }

void GUI::NavigationBar::SetSettingsID(States::ID id) { settingsID = id; }

void GUI::NavigationBar::SetDirectLink(std::function< void(States::ID) > link) {
    toLink = link;
}

void GUI::NavigationBar::SetBackToPreviousLink(std::function< void() > link) {
    backToPrvState = link;
}

void GUI::NavigationBar::AtSettings(bool settings) { atSettings = settings; }

void GUI::NavigationBar::SetCategory(std::string category) {
    currentCategory = category;
}

void GUI::NavigationBar::InsertTitle(DataStructures::ID titleID,
                                     States::ID stateID, std::string abbrTitle,
                                     std::string titleName) {
    TitleInfo info = {stateID, abbrTitle, titleName};
    auto inserted = mTitles.insert(std::make_pair(titleID, info));
    assert(inserted.second);
}
void GUI::NavigationBar::SetActiveTitle(DataStructures::ID titleID) {
    activeTitle = titleID;
}
void GUI::NavigationBar::ClearTitle() { mTitles.clear(); }

void GUI::NavigationBar::SetVisableTitle(bool visible) { hasTitle = visible; }

bool GUI::NavigationBar::DrawLogo() {
    // render
    Font logoFont = fonts->Get(Fonts::Silkscreen);
    float fSpanWidth = MeasureTextEx(logoFont, "Visu", 32, 1).x;
    DrawTextEx(logoFont, "Visu", {10, 4}, 32, 1, WHITE);
    DrawTextEx(logoFont, "Algo", {10 + fSpanWidth, 4}, 32, 1, ORANGE);
    float logoWidth = MeasureTextEx(logoFont, "VisuAlgo", 32, 1).x;
    hoverBounds["logo-bound"] = (Rectangle){10, 4, logoWidth, 32};

    if (currentCategory.size()) {
        Font font = fonts->Get(Fonts::Default);
        float x = hoverBounds["logo-bound"].x + hoverBounds["logo-bound"].width;
        float y = hoverBounds["logo-bound"].y + 5;
        DrawTextEx(font, ("/" + currentCategory).c_str(), {x, y}, 24, 0, WHITE);
    }

    return (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), hoverBounds["logo-bound"]));
}

States::ID GUI::NavigationBar::DrawTitles() {
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

        hoverBounds["button-" + title.first] =
            (Rectangle){x - padding, y - padding, textWidth + padding * 2,
                        32 + padding * 2};
        x += hoverBounds["button-" + title.first].width + margin + padding;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(),
                                   hoverBounds["button-" + title.first]))
            return title.second.stateID;
    }
    return States::None;
}

bool GUI::NavigationBar::DrawSettings() {
    std::string text = "Settings";
    if (atSettings) text = "Back";
    Font settingsFont = fonts->Get(Fonts::Silkscreen);
    float spanWidth = MeasureTextEx(settingsFont, text.c_str(), 24, -0.1).x;
    Color settingsColor = (Color){25, 125, 84, 255};

    float paddingX = 8, paddingY = 2;
    float posX = global::SCREEN_WIDTH - 125, posY = 8;
    hoverBounds["settings-bound"] =
        (Rectangle){posX - paddingX, posY - paddingY, spanWidth + paddingX * 2,
                    24 + 2 * paddingY};

    // render
    Color textColor = settingsColor;
    if (CheckCollisionPointRec(GetMousePosition(),
                               hoverBounds["settings-bound"])) {
        textColor = (Color){10, 88, 202, 255};
    }
    DrawTextEx(settingsFont, text.c_str(), {posX, posY}, 24, -0.1, textColor);
    DrawRectangleLinesEx(hoverBounds["settings-bound"], 1, settingsColor);

    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(),
                                   hoverBounds["settings-bound"]));
}

GUI::NavigationBar::~NavigationBar() {}