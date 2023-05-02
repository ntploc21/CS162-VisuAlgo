#include "InputField.hpp"

#include <cstring>

#include "Settings.hpp"

GUIComponent::InputField::InputField(FontHolder* fonts)
    : fonts(fonts), labelFontSize(20), mFieldIndex(InputField::fields.size()) {
    if (GUIComponent::InputField::fields.empty()) {
        GUIComponent::InputField::fields = std::vector< bool >(1, false);
    } else
        GUIComponent::InputField::fields.push_back(false);
}

GUIComponent::InputField::~InputField() {}

void GUIComponent::InputField::Draw(Vector2 base) {
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
        GUIComponent::InputField::fields[mFieldIndex] = true;
    }
    SetEditMode(GUIComponent::InputField::fields[mFieldIndex]);
    DrawField(base);
}

bool GUIComponent::InputField::isSelectable() const { return false; }

void GUIComponent::InputField::SetLabelSize(float fontSize) {
    labelFontSize = fontSize;
}

void GUIComponent::InputField::SetInputFieldSize(Vector2 size) {
    inputFieldSize = size;
}

Vector2 GUIComponent::InputField::GetSize() {
    assert(labelFontSize <= inputFieldSize.y);
    Font font = fonts->Get(Fonts::Default);

    float labelWidth = MeasureTextEx(font, label.c_str(), labelFontSize, 0).x;
    float width = labelWidth + inputFieldSize.x + 13;
    float height = inputFieldSize.y + 6;

    // std::cout << width << " " << height << std::endl;

    return (Vector2){width, height};
}

bool GUIComponent::InputField::IsClicked(Vector2 base) const {
    Rectangle bound =
        (Rectangle){base.x, base.y, inputFieldSize.x, inputFieldSize.y};
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), bound));
}

void GUIComponent::InputField::SetEditMode(bool canEdit) { editMode = canEdit; }

bool GUIComponent::InputField::GetEditMode() const { return editMode; }

void GUIComponent::InputField::AllFieldDisableEdit() {
    std::fill(GUIComponent::InputField::fields.begin(),
              GUIComponent::InputField::fields.end(), false);
}

void GUIComponent::InputField::Randomize() {}

void GUIComponent::InputField::SetLabel(std::string labelContent) {
    label = labelContent;
}

std::string GUIComponent::InputField::GetLabel() const { return label; }
