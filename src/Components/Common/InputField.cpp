#include "InputField.hpp"

#include <cstring>

#include "Settings.hpp"

GUI::InputField::InputField(FontHolder* fonts)
    : fonts(fonts), labelFontSize(20), mFieldIndex(InputField::fields.size()) {
    if (GUI::InputField::fields.empty()) {
        GUI::InputField::fields = std::vector< bool >(1, false);
    } else
        GUI::InputField::fields.push_back(false);
}

GUI::InputField::~InputField() {}

void GUI::InputField::Draw(Vector2 base) {
    const Color buttonColor =
        Settings::getInstance().getColor(ColorTheme::ActionList_Background);
    const Color labelColor =
        Settings::getInstance().getColor(ColorTheme::ActionList_Text);

    base.x += mPosition.x;
    base.y += mPosition.y;

    Font font = fonts->Get(Fonts::Default);
    Vector2 inputBound = GetSize();
    Rectangle bound = (Rectangle){base.x, base.y, inputBound.x, inputBound.y};

    DrawRectangleRec(bound, buttonColor);

    float yLabel = base.y + (inputBound.y - labelFontSize) / 2;
    DrawTextEx(font, label.c_str(), (Vector2){base.x + 5, yLabel},
               labelFontSize, 0, labelColor);
    base.x += 8 + MeasureTextEx(font, label.c_str(), labelFontSize, 0).x;
    base.y += 3;

    if (IsClicked(base)) {
        AllFieldDisableEdit();
        GUI::InputField::fields[mFieldIndex] = true;
    }
    SetEditMode(GUI::InputField::fields[mFieldIndex]);
    DrawField(base);
}

bool GUI::InputField::isSelectable() const { return false; }

void GUI::InputField::SetLabelSize(float fontSize) { labelFontSize = fontSize; }

void GUI::InputField::SetInputFieldSize(Vector2 size) { inputFieldSize = size; }

Vector2 GUI::InputField::GetSize() {
    assert(labelFontSize <= inputFieldSize.y);
    Font font = fonts->Get(Fonts::Default);

    float labelWidth = MeasureTextEx(font, label.c_str(), labelFontSize, 0).x;
    float width = labelWidth + inputFieldSize.x + 13;
    float height = inputFieldSize.y + 6;

    // std::cout << width << " " << height << std::endl;

    return (Vector2){width, height};
}

bool GUI::InputField::IsClicked(Vector2 base) const {
    Rectangle bound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), bound));
}

void GUI::InputField::SetEditMode(bool canEdit) { editMode = canEdit; }

bool GUI::InputField::GetEditMode() const { return editMode; }

void GUI::InputField::AllFieldDisableEdit() {
    std::fill(GUI::InputField::fields.begin(), GUI::InputField::fields.end(),
              false);
}

void GUI::InputField::Randomize() {}

void GUI::InputField::SetLabel(std::string labelContent) {
    label = labelContent;
}

std::string GUI::InputField::GetLabel() const { return label; }
