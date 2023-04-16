#include "StringInputField.hpp"

#include <string.h>

GUI::StringInputField::StringInputField(FontHolder* fonts)
    : GUI::InputField(fonts) {}
GUI::StringInputField::~StringInputField() {}
std::string GUI::StringInputField::ExtractValue() { return content; }

void GUI::StringInputField::DrawField(Vector2 base) {
    Rectangle inputBound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};

    char* input = new char[content.size()];
    strcpy(input, content.c_str());

    DrawRectangleRec(inputBound, BLACK);
    GuiTextBox(inputBound, input, labelFontSize, GetEditMode());
    content = input;
}

bool GUI::StringInputField::isSelectable() const { return false; }
