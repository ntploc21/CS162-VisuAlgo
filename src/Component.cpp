#include "Component.hpp"

GUI::Component::Component() : position((Vector2){0, 0}), mIsSelected(false) {}

GUI::Component::~Component() {}

void GUI::Component::Draw(Vector2 base) {}

bool GUI::Component::isSelected() const { return mIsSelected; }

void GUI::Component::select() { mIsSelected = true; }

void GUI::Component::deselect() { mIsSelected = false; }

void GUI::Component::SetPosition(float x, float y) {
    position = (Vector2){x, y};
}

Vector2 GUI::Component::GetPosition() { return position; }
