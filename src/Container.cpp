#include "Container.hpp"

GUI::Container::Container() : mChildren() { SetVisible(true); }

void GUI::Container::pack(Component::Ptr component) {
    mChildren.push_back(component);
}

void GUI::Container::UnpackAll() { mChildren.clear(); }

void GUI::Container::Draw(Vector2 base) {
    if (!mVisible) return;
    DrawCurrent(base);
    base.x += mPosition.x, base.y += mPosition.y;
    for (const Component::Ptr child : mChildren) {
        child->Draw(base);
    }
}

bool GUI::Container::isSelectable() const { return false; }

std::vector< GUI::Component::Ptr > GUI::Container::GetChildren() {
    return mChildren;
}

void GUI::Container::DrawCurrent(Vector2 base = (Vector2){0, 0}) {}

Vector2 GUI::Container::GetSize() {
    Vector2 minPosition = (Vector2){10000, 10000};
    Vector2 maxPosition = (Vector2){0, 0};

    for (auto child : mChildren) {
        if (!child.get()->GetVisible()) continue;
        minPosition.x = std::min(minPosition.x, child.get()->GetPosition().x);
        minPosition.y = std::min(minPosition.y, child.get()->GetPosition().y);
        maxPosition.x = std::max(maxPosition.x, child.get()->GetPosition().x +
                                                    child.get()->GetSize().x);
        maxPosition.y = std::max(maxPosition.y, child.get()->GetPosition().y +
                                                    child.get()->GetSize().y);
    }

    return (Vector2){maxPosition.x - minPosition.x,
                     maxPosition.y - minPosition.y};

    return (Vector2){0, 0};
}
