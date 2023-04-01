#include "NavigationBar.hpp"

#include "raylib.h"
#define RAYGUI_STATIC
#include <iostream>

#include "raygui.h"

NavigationBar::NavigationBar(int x, int y) : posX(x), posY(y) {}

void NavigationBar::DrawCurrent() {
    Rectangle rec = (Rectangle){posX, posY, 1200 - 2 * posX, 100};
    DrawRectangleRec(rec, BROWN);

    bool button =
        GuiButton((Rectangle){posX + 20, posY + 10, 100, 80}, "Click me!");

    if (button) {
        move = true;
        std::cout << "Clicked!" << std::endl;
    }
}

bool NavigationBar::MoveToSettings() {
    bool tmp = move;
    move = false;
    return tmp;
}

NavigationBar::~NavigationBar() {}