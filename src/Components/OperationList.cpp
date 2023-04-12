#include "OperationList.hpp"

#include <iostream>

OperationList::OperationList(FontHolder *fonts) : isHide(true) {
    toggleButton = Button("<", fonts);
    toggleButton.SetTextAlignment(toggleButton.Center);
    toggleButton.SetFontSize(32);
    toggleButton.SetButtonHoverColor(GREEN);
}
OperationList::~OperationList() {}

void OperationList::Draw(Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    toggleButton.Draw(base);
    if (!isHide) {
        buttons.Draw(base);
        optionContainers.Draw(base);
    }
}

OperationList::OperationList() {}

void OperationList::AddOperation(Button::Ptr action,
                                 GUI::Container::Ptr optionContainer) {
    float buttonHeight = 30;
    Vector2 lastOperationPos = (Vector2){43, -buttonHeight};
    if (!buttons.GetChildren().empty()) {
        lastOperationPos = buttons.GetChildren().back().get()->GetPosition();
    }
    lastOperationPos.y += buttonHeight;

    action.get()->SetPosition(lastOperationPos.x, lastOperationPos.y);
    action.get()->SetSize(150, buttonHeight);
    action.get()->SetFontSize(20);
    // action.get()->SetButtonHoverColor((Color){214, 87, 117, 255});
    // action.get()->SetButtonColor(GREEN);
    // action.get()->SetTextColor(WHITE);

    optionContainer.get()->SetPosition(lastOperationPos.x + 150,
                                       lastOperationPos.y);
    optionContainer.get()->SetVisible(false);

    buttons.pack(action);
    optionContainers.pack(optionContainer);
    std::size_t index = optionContainers.GetChildren().size() - 1;
    action.get()->SetAction([this, index]() {
        HideAllOptions();
        ShowOptions(index);
    });
    toggleButton.SetSize(40, lastOperationPos.y + buttonHeight);
}

void OperationList::ShowOptions(std::size_t index) {
    optionContainers.GetChildren().at(index).get()->SetVisible(true);
}

void OperationList::HideAllOptions() {
    for (auto options : optionContainers.GetChildren()) {
        if (options.get() == nullptr) continue;
        options.get()->SetVisible(false);
    }
}

void OperationList::ToggleOperations() {
    if (isHide)
        isHide = false;
    else
        isHide = true;

    if (isHide)
        toggleButton.SetText("<");
    else
        toggleButton.SetText(">");
}

void OperationList::InitActionBar() {
    toggleButton.SetAction([this]() {
        this->ToggleOperations();
        if (isHide) {
            this->HideAllOptions();
        }
    });
}
