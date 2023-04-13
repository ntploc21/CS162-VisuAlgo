#include "IntegerInputField.hpp"

#include <string.h>

IntegerInputField::IntegerInputField(FontHolder* fonts)
    : InputField(fonts), input(0), mMinValue(0), mMaxValue(0) {}
IntegerInputField::~IntegerInputField() {}
std::string IntegerInputField::ExtractValue() { return std::to_string(input); }

void IntegerInputField::DrawField(Vector2 base) {
    Rectangle inputBound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};
    GuiValueBox(inputBound, nullptr, &input, mMinValue, mMaxValue,
                GetEditMode());
    // GuiSpinner(inputBound, nullptr, &input, mMinValue, mMaxValue, true);
}

void IntegerInputField::SetConstraint(int minValue, int maxValue) {
    mMinValue = minValue;
    mMaxValue = maxValue;
}

bool IntegerInputField::isSelectable() const { return false; }
