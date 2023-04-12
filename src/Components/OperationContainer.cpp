#include "OperationContainer.hpp"

#include <iostream>

OperationContainer::OperationContainer(FontHolder *fonts) : isHide(true) {
    toggleButton = Button("<", fonts);
    toggleButton.SetTextAlignment(toggleButton.Center);
    toggleButton.SetFontSize(32);
    toggleButton.SetButtonHoverColor(GREEN);
}
OperationContainer::~OperationContainer() {}

void OperationContainer::Draw(Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    toggleButton.Draw(base);
    if (!isHide) {
        buttons.Draw(base);
        // optionContainers.Draw();
    }
}

OperationContainer::OperationContainer() {}

void OperationContainer::AddOperation(Button::Ptr action,
                                      GUI::Container::Ptr optionContainer) {
    float buttonHeight = 30;
    Vector2 lastOperationPos = (Vector2){43, -buttonHeight};
    if (!buttons.GetChildren().empty()) {
        lastOperationPos = buttons.GetChildren().back().get()->GetPosition();
    }
    lastOperationPos.y += buttonHeight;

    action.get()->SetPosition(lastOperationPos.x, lastOperationPos.y);
    action.get()->SetSize(150, buttonHeight);
    action.get()->SetFontSize(24);
    action.get()->SetButtonHoverColor((Color){214, 87, 117, 255});
    // action.get()->SetButtonColor(GREEN);
    // action.get()->SetTextColor(WHITE);
    // (*action).
    // (*optionContainer)
    //     .SetPosition(lastOperationPos.x + 150, lastOperationPos.y);

    buttons.pack(action);
    optionContainers.pack(optionContainer);
    action.get()->SetAction([&, this]() {
        HideAllOptions();
        optionContainer.get()->SetVisible(true);
    });
    toggleButton.SetSize(40, lastOperationPos.y + buttonHeight);
}

void OperationContainer::HideAllOptions() {
    for (auto options : optionContainers.GetChildren()) {
        if (options.get() == nullptr) continue;
        options.get()->SetVisible(false);
    }
}

void OperationContainer::ToggleOperations() {
    if (isHide)
        isHide = false;
    else
        isHide = true;

    if (isHide)
        toggleButton.SetText("<");
    else
        toggleButton.SetText(">");
}

void OperationContainer::InitActionBar() {
    toggleButton.SetAction([this]() {
        this->ToggleOperations();
        if (isHide) {
            this->HideAllOptions();
        }
    });
}
