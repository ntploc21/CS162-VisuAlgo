#include "Container.hpp"

GUI::Container::Container() : mChildren() { SetVisible(true); }

void GUI::Container::pack(Component::Ptr component) {
    mChildren.push_back(component);
}

void GUI::Container::Draw(Vector2 base) {
    if (!mVisible) return;
    base.x += mPosition.x, base.y += mPosition.y;
    for (const Component::Ptr child : mChildren) {
        child->Draw(base);
    }
}

bool GUI::Container::isSelectable() const { return false; }

std::vector< GUI::Component::Ptr > GUI::Container::GetChildren() {
    return mChildren;
}
