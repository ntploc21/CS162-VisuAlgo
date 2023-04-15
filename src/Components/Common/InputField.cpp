#include "InputField.hpp"

#include <cstring>
#include <iostream>

InputField::InputField(FontHolder* fonts)
    : fonts(fonts), labelFontSize(20), mFieldIndex(InputField::fields.size()) {
    if (InputField::fields.empty()) {
        InputField::fields = std::vector< bool >(1, false);
    } else
        InputField::fields.push_back(false);
}

InputField::~InputField() {}

void InputField::Draw(Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;

    Font font = fonts->Get(Fonts::Default);
    Vector2 inputBound = GetSize();
    Rectangle bound = (Rectangle){base.x, base.y, inputBound.x, inputBound.y};

    DrawRectangleRec(bound, (Color){82, 188, 105, 255});

    float yLabel = base.y + (inputBound.y - labelFontSize) / 2;
    DrawTextEx(font, label.c_str(), (Vector2){base.x + 5, yLabel},
               labelFontSize, 0, WHITE);
    base.x += 8 + MeasureTextEx(font, label.c_str(), labelFontSize, 0).x;
    base.y += 3;

    if (IsClicked(base)) {
        AllFieldDisableEdit();
        InputField::fields[mFieldIndex] = true;
    }
    SetEditMode(InputField::fields[mFieldIndex]);
    DrawField(base);
}

bool InputField::isSelectable() const { return false; }

void InputField::SetLabelSize(float fontSize) { labelFontSize = fontSize; }

void InputField::SetInputFieldSize(Vector2 size) { inputFieldSize = size; }

Vector2 InputField::GetSize() {
    assert(labelFontSize <= inputFieldSize.y);
    Font font = fonts->Get(Fonts::Default);

    float labelWidth = MeasureTextEx(font, label.c_str(), labelFontSize, 0).x;
    float width = labelWidth + inputFieldSize.x + 13;
    float height = inputFieldSize.y + 6;

    // std::cout << width << " " << height << std::endl;

    return (Vector2){width, height};
}

bool InputField::IsClicked(Vector2 base) const {
    Rectangle bound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), bound));
}

void InputField::SetEditMode(bool canEdit) { editMode = canEdit; }

bool InputField::GetEditMode() const { return editMode; }

void InputField::AllFieldDisableEdit() {
    std::fill(InputField::fields.begin(), InputField::fields.end(), false);
}

void InputField::SetLabel(std::string labelContent) { label = labelContent; }

std::string InputField::GetLabel() const { return label; }
