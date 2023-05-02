#include "StringInputField.hpp"

#include <string.h>

#include "Settings.hpp"

GUIComponent::StringInputField::StringInputField(FontHolder* fonts)
    : GUIComponent::InputField(fonts) {}
GUIComponent::StringInputField::~StringInputField() {}
std::string GUIComponent::StringInputField::ExtractValue() { return content; }

void GUIComponent::StringInputField::DrawField(Vector2 base) {
    const Color inactiveColor =
        Settings::getInstance().getColor(ColorTheme::InputField_Inactive);

    Rectangle inputBound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};

    char* input = new char[100];
    strcpy(input, content.c_str());

    DrawRectangleRec(inputBound, inactiveColor);
    GuiTextBox(inputBound, input, labelFontSize, GetEditMode());
    content = input;
    delete[] input;
}

bool GUIComponent::StringInputField::isSelectable() const { return false; }
