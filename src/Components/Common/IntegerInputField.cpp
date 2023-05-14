#include "IntegerInputField.hpp"

#include <string.h>

#include "Settings.hpp"
#include "Utils/Utils.hpp"

GUIComponent::IntegerInputField::IntegerInputField(FontHolder* fonts)
    : GUIComponent::InputField(fonts), input(0), mMinValue(0), mMaxValue(0) {}
GUIComponent::IntegerInputField::~IntegerInputField() {}
std::string GUIComponent::IntegerInputField::ExtractValue() {
    return std::to_string(input);
}

void GUIComponent::IntegerInputField::DrawField(Vector2 base) {
    const Color inactiveColor =
        Settings::getInstance().getColor(ColorTheme::InputField_Inactive);

    Rectangle inputBound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};
    DrawRectangleRec(inputBound, inactiveColor);
    GuiValueBox(inputBound, nullptr, &input, mMinValue, mMaxValue,
                GetEditMode());
}

void GUIComponent::IntegerInputField::SetConstraint(int minValue,
                                                    int maxValue) {
    mMinValue = minValue;
    mMaxValue = maxValue;
}

bool GUIComponent::IntegerInputField::isSelectable() const { return false; }

void GUIComponent::IntegerInputField::Randomize() {
    input = Utils::Rand(mMinValue, mMaxValue);
}
