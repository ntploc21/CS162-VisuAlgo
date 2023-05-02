#include "OperationContainer.hpp"

#include <iostream>
GUIComponent::OperationContainer::~OperationContainer() {}

GUIComponent::OperationContainer::OperationContainer() {}

void GUIComponent::OperationContainer::DrawCurrent(Vector2 base) {
    UpdatePosition();
}

void GUIComponent::OperationContainer::SetVisible(bool visible) {
    for (auto child : mChildren) {
        child.get()->SetVisible(visible);
    }
    mVisible = visible;
}

void GUIComponent::OperationContainer::UpdatePosition() {
    float buttonHeight = 30;
    Vector2 nextOptionPos = (Vector2){3, 2};
    for (auto child : mChildren) {
        child.get()->SetPosition(nextOptionPos);
        nextOptionPos.x =
            child.get()->GetPosition().x + child.get()->GetSize().x + 2;
    }
}
