#include "Component.hpp"

GUI::Component::Component() : mPosition((Vector2){0, 0}), mIsSelected(false) {}

GUI::Component::~Component() {}

void GUI::Component::Draw(Vector2 base) {}

bool GUI::Component::isSelected() const { return mIsSelected; }

void GUI::Component::select() { mIsSelected = true; }

void GUI::Component::deselect() { mIsSelected = false; }

void GUI::Component::SetVisible(bool visible) { mVisible = visible; }

void GUI::Component::SetPosition(float x, float y) {
    mPosition = (Vector2){x, y};
}
void GUI::Component::SetPosition(Vector2 position) { mPosition = position; }

Vector2 GUI::Component::GetPosition() { return mPosition; }

void GUI::Component::UpdateHover(std::map< std::string, Rectangle > bounds,
                                 bool &hover, bool noHover) {
    if (noHover) {
        hover = false;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        return;
    }
    bool noHoverBound = true;
    for (auto bound : bounds) {
        if (CheckCollisionPointRec(GetMousePosition(), bound.second)) {
            noHoverBound = false;
            break;
        }
    }
    if (!noHoverBound) {
        hover = true;
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else if (hover) {
        hover = false;
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
}
