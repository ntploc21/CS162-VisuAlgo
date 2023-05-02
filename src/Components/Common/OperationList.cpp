#include "OperationList.hpp"

#include <iostream>

#include "Settings.hpp"

GUIComponent::OperationList::OperationList(FontHolder *fonts) : isHide(true) {
    toggleButton = GUIComponent::Button("<", fonts);
    toggleButton.SetTextAlignment(toggleButton.Center);
    toggleButton.SetFontSize(32);
    toggleButton.SetButtonColor(ColorTheme::ActionList_Background);
    toggleButton.SetButtonHoverColor(ColorTheme::ActionList_Background);
}
GUIComponent::OperationList::~OperationList() {}

void GUIComponent::OperationList::Draw(Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    toggleButton.Draw(base);
    if (!isHide) {
        buttons.Draw(base);
        optionContainers.Draw(base);
    }
}

GUIComponent::OperationList::OperationList() {}

void GUIComponent::OperationList::AddOperation(
    GUIComponent::Button::Ptr action, GUI::Container::Ptr optionContainer) {
    float buttonHeight = 30;
    Vector2 lastOperationPos = (Vector2){43, -buttonHeight};
    if (!buttons.GetChildren().empty()) {
        lastOperationPos = buttons.GetChildren().back().get()->GetPosition();
    }
    lastOperationPos.y += buttonHeight;

    action.get()->SetPosition(lastOperationPos.x, lastOperationPos.y);
    action.get()->SetSize(150, buttonHeight);
    action.get()->SetFontSize(20);
    action.get()->SetButtonColor(ColorTheme::ActionList_Background);

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

void GUIComponent::OperationList::ShowOptions(std::size_t index) {
    optionContainers.GetChildren().at(index).get()->SetVisible(true);
}

void GUIComponent::OperationList::HideAllOptions() {
    for (auto options : optionContainers.GetChildren()) {
        if (options.get() == nullptr) continue;
        options.get()->SetVisible(false);
    }
}

void GUIComponent::OperationList::ToggleOperations() {
    if (isHide)
        isHide = false;
    else
        isHide = true;

    if (isHide)
        toggleButton.SetText("<");
    else
        toggleButton.SetText(">");
}

void GUIComponent::OperationList::InitActionBar() {
    toggleButton.SetAction([this]() {
        this->ToggleOperations();
        if (isHide) {
            this->HideAllOptions();
        }
    });
}

Vector2 GUIComponent::OperationList::GetSize() {
    float width = 1200;  // we dont need to width right now so dont need to
                         // calculate it precisely
    float height = toggleButton.GetSize().y;
    return (Vector2){width, height};
}
