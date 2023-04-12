#include "Component.hpp"

GUI::Component::Component() : mPosition((Vector2){0, 0}), mIsSelected(false) {}

GUI::Component::~Component() {}

void GUI::Component::Draw(Vector2 base) {}

bool GUI::Component::isSelected() const { return mIsSelected; }

void GUI::Component::select() { mIsSelected = true; }

void GUI::Component::deselect() { mIsSelected = false; }

void GUI::Component::SetVisible(bool visible) { mVisible = visible; }

bool GUI::Component::GetVisible() { return mVisible; }

void GUI::Component::SetPosition(float x, float y) {
    mPosition = (Vector2){x, y};
}
void GUI::Component::SetPosition(Vector2 position) { mPosition = position; }

Vector2 GUI::Component::GetPosition() { return mPosition; }

void GUI::Component::UpdateMouseCursorWhenHover(
    std::map< std::string, Rectangle > bounds, bool hover, bool noHover) {
    bool nxtHover = GetHoverStatus(bounds, hover, noHover);
    if (hover == nxtHover) {
        if (hover) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        return;
    }
    if (nxtHover)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void GUI::Component::UpdateMouseCursorWhenHover(Rectangle bound, bool hover,
                                                bool noHover) {
    bool nxtHover = GetHoverStatus(bound, hover, noHover);
    if (hover == nxtHover) {
        if (hover) SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        return;
    }
    if (nxtHover)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

bool GUI::Component::GetHoverStatus(std::map< std::string, Rectangle > bounds,
                                    bool hover, bool noHover) {
    if (noHover) return false;
    bool noHoverBound = true;
    for (auto bound : bounds) {
        if (CheckCollisionPointRec(GetMousePosition(), bound.second)) {
            noHoverBound = false;
            break;
        }
    }
    if (!noHoverBound)
        hover = true;
    else if (hover)
        hover = false;
    return hover;
}

bool GUI::Component::GetHoverStatus(Rectangle bound, bool hover, bool noHover) {
    if (noHover) return false;
    if (CheckCollisionPointRec(GetMousePosition(), bound))
        hover = true;
    else if (hover)
        hover = false;
    return hover;
}
