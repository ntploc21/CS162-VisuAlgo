#include "Container.hpp"

GUI::Container::Container() : mChildren() {}

void GUI::Container::pack(Component::Ptr component) {
    mChildren.push_back(component);
}

void GUI::Container::Draw(Vector2 base) {
    base.x += position.x, base.y += position.y;
    for (const Component::Ptr child : mChildren) {
        child->Draw(base);
    }
}

bool GUI::Container::isSelectable() const { return false; }
