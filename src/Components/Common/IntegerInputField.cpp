#include "IntegerInputField.hpp"

#include <string.h>

#include "Settings.hpp"
#include "Utils/Utils.hpp"

GUI::IntegerInputField::IntegerInputField(FontHolder* fonts)
    : GUI::InputField(fonts), input(0), mMinValue(0), mMaxValue(0) {}
GUI::IntegerInputField::~IntegerInputField() {}
std::string GUI::IntegerInputField::ExtractValue() {
    return std::to_string(input);
}

void GUI::IntegerInputField::DrawField(Vector2 base) {
    const Color inactiveColor =
        Settings::getInstance().getColor(ColorTheme::InputField_Inactive);

    Rectangle inputBound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};
    DrawRectangleRec(inputBound, inactiveColor);
    GuiValueBox(inputBound, nullptr, &input, mMinValue, mMaxValue,
                GetEditMode());
    // GuiSpinner(inputBound, nullptr, &input, mMinValue, mMaxValue, true);
}

void GUI::IntegerInputField::SetConstraint(int minValue, int maxValue) {
    mMinValue = minValue;
    mMaxValue = maxValue;
}

bool GUI::IntegerInputField::isSelectable() const { return false; }

void GUI::IntegerInputField::Randomize() {
    input = Utils::Rand(mMinValue, mMaxValue);
}
