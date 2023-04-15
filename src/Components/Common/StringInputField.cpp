#include "StringInputField.hpp"

#include <string.h>

StringInputField::StringInputField(FontHolder* fonts) : InputField(fonts) {}
StringInputField::~StringInputField() {}
std::string StringInputField::ExtractValue() { return content; }

void StringInputField::DrawField(Vector2 base) {
    Rectangle inputBound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};

    char* input = new char[content.size()];
    strcpy(input, content.c_str());

    GuiTextBox(inputBound, input, labelFontSize, GetEditMode());
    content = input;
}

bool StringInputField::isSelectable() const { return false; }
