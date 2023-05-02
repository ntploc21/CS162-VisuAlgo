#include "OptionInputField.hpp"

#include <iostream>

#include "Button.hpp"
#include "Settings.hpp"

GUI::OptionInputField::OptionInputField(FontHolder* fonts)
    : fonts(fonts), hasInputField(false), mInputField(new GUI::Container()) {}

GUI::OptionInputField::~OptionInputField() {}

void GUI::OptionInputField::SetOption(
    std::string content, Core::Deque< InputField::Ptr > fields,
    std::function< void(std::map< std::string, std::string >) > action) {
    auto genButton = [&, this](
                         std::string content,
                         std::function< void() > action) -> GUI::Button::Ptr {
        GUI::Button::Ptr button(new GUI::Button(content, fonts));

        button.get()->SetFontSize(20);
        button.get()->EnableFitContent();
        button.get()->SetAction(action);
        button.get()->SetButtonColor(ColorTheme::ActionList_Background);

        return button;
    };

    /* */
    UnpackAll();
    mInputField.get()->UnpackAll();
    mInputField.get()->SetVisible(false);

    auto actionOnSubmit = [action, this]() { action(mInput); };

    hasInputField = !fields.empty();
    if (fields.empty()) {
        GUI::Button::Ptr button(genButton(content, actionOnSubmit));
        pack(button);
        return;
    }

    auto actionToggle = [this]() { ToggleInputFields(); };
    GUI::Button::Ptr button(genButton(content, actionToggle));
    pack(button);

    /* */

    for (auto& inputField : fields) {
        AddInputField(inputField);
    }

    AddSubmitField(action);

    pack(mInputField);
}

void GUI::OptionInputField::SetNoFieldOption(std::string content,
                                             std::function< void() > action) {
    SetOption(
        content, {},
        [action](std::map< std::string, std::string > input) { action(); });
}

void GUI::OptionInputField::ToggleInputFields() {
    mInputField.get()->ToggleVisible();
}

void GUI::OptionInputField::DrawCurrent(Vector2 base) {
    const Color buttonColor =
        Settings::getInstance().getColor(ColorTheme::ActionList_Background);

    base.x += mPosition.x;
    base.y += mPosition.y;
    Vector2 size = GetSize();
    // std::cout << size.x << " " << size.y << std::endl;
    Rectangle bound = (Rectangle){base.x, base.y, size.x, size.y};
    DrawRectangleRec(bound, buttonColor);
}

void GUI::OptionInputField::SetVisible(bool visible) {
    if (!visible) mInputField.get()->SetVisible(false);
    mVisible = visible;
}

Vector2 GUI::OptionInputField::GetSize() {
    if (mChildren.empty()) return (Vector2){0, 0};
    float width = 0;
    float height = 0;
    int i = 0;
    for (auto child : mChildren) {
        if (!child.get()->GetVisible()) continue;
        width = std::max(width, child.get()->GetSize().x);
        height += child.get()->GetSize().y;
    }
    return (Vector2){width + 5 * mInputField.get()->GetVisible(), height};
}

std::map< std::string, std::string > GUI::OptionInputField::ExtractInput() {
    std::map< std::string, std::string > inputs;
    auto inputFields = mInputField.get()->GetChildren();
    for (auto it = inputFields.begin(); it + 1 != inputFields.end(); it++) {
        InputField* input = dynamic_cast< InputField* >(it->get());
        inputs[input->GetLabel()] = input->ExtractValue();
    }
    return inputs;
}

void GUI::OptionInputField::AddInputField(InputField::Ptr inputField) {
    Vector2 lastInputFieldPos = mChildren.front().get()->GetPosition();
    lastInputFieldPos.y += mChildren.front().get()->GetSize().y;
    if (!mInputField.get()->GetChildren().empty()) {
        GUI::Component::Ptr lastInputField =
            mInputField.get()->GetChildren().back();
        lastInputFieldPos.x = lastInputField.get()->GetPosition().x +
                              lastInputField.get()->GetSize().x;
    }
    inputField.get()->SetPosition(lastInputFieldPos);

    mInputField.get()->pack(inputField);
}

void GUI::OptionInputField::AddSubmitField(
    std::function< void(std::map< std::string, std::string >) > action) {
    auto genButton = [&, this](
                         std::string content,
                         std::function< void() > action) -> GUI::Button::Ptr {
        GUI::Button::Ptr button(new GUI::Button(content, fonts));

        button.get()->SetFontSize(20);
        button.get()->EnableFitContent();
        button.get()->SetAction(action);
        button.get()->SetButtonColor(ColorTheme::ActionList_Background);

        return button;
    };
    /* */
    GUI::Button::Ptr buttonSubmit(
        genButton("Go", [action, this]() { action(ExtractInput()); }));
    GUI::Component::Ptr prevChild = mInputField.get()->GetChildren().back();

    buttonSubmit.get()->SetPosition((Vector2){
        prevChild.get()->GetPosition().x + prevChild.get()->GetSize().x + 3,
        prevChild.get()->GetPosition().y +
            (prevChild.get()->GetSize().y - buttonSubmit.get()->GetSize().y) /
                2});

    mInputField.get()->pack(buttonSubmit);
}

bool GUI::OptionInputField::HasInputField() { return hasInputField; }
