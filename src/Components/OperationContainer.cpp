#include "OperationContainer.hpp"

#include <iostream>
OperationContainer::~OperationContainer() {}

OperationContainer::OperationContainer() {}

void OperationContainer::AddOperation(GUI::Component::Ptr option) {
    float buttonHeight = 30;
    Vector2 nextOptionPos = (Vector2){3, 2};
    if (!GetChildren().empty()) {
        nextOptionPos.x = GetChildren().back().get()->GetPosition().x +
                          GetChildren().back().get()->GetSize().x + 2;
    }
    option.get()->SetPosition(nextOptionPos);

    pack(option);
}