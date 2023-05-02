#include "StringInputField.hpp"

#include <string.h>

#include "Settings.hpp"

GUI::StringInputField::StringInputField(FontHolder* fonts)
    : GUI::InputField(fonts) {}
GUI::StringInputField::~StringInputField() {}
std::string GUI::StringInputField::ExtractValue() { return content; }

void GUI::StringInputField::DrawField(Vector2 base) {
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

bool GUI::StringInputField::isSelectable() const { return false; }
