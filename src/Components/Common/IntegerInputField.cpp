#include "IntegerInputField.hpp"

#include <string.h>

GUI::IntegerInputField::IntegerInputField(FontHolder* fonts)
    : GUI::InputField(fonts), input(0), mMinValue(0), mMaxValue(0) {}
GUI::IntegerInputField::~IntegerInputField() {}
std::string GUI::IntegerInputField::ExtractValue() {
    return std::to_string(input);
}

void GUI::IntegerInputField::DrawField(Vector2 base) {
    Rectangle inputBound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};
    GuiValueBox(inputBound, nullptr, &input, mMinValue, mMaxValue,
                GetEditMode());
    // GuiSpinner(inputBound, nullptr, &input, mMinValue, mMaxValue, true);
}

void GUI::IntegerInputField::SetConstraint(int minValue, int maxValue) {
    mMinValue = minValue;
    mMaxValue = maxValue;
}

bool GUI::IntegerInputField::isSelectable() const { return false; }
