#include "NavigationBar.hpp"

#include "../Global.hpp"
// #include "raylib.h"
// #define RAYGUI_STATIC
#include <iostream>

NavigationBar::NavigationBar(Font *logoFont) : logoFont(logoFont) {}

NavigationBar::NavigationBar() {}

void NavigationBar::DrawCurrent() {
    Rectangle rec = (Rectangle){0, 0, global::SCREEN_WIDTH, 40};
    DrawRectangleRec(rec, BLACK);

    DrawTextEx(*logoFont, "Visu", {10, 4}, 32, 1, WHITE);
    DrawTextEx(*logoFont, "Algo", {80, 4}, 32, 1, ORANGE);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(),
                               (Rectangle){10, 4, 141, 32})) {
        // toTheHomepage = true;
    }
}

NavigationBar::~NavigationBar() {}