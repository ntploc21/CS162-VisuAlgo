#include "Button.hpp"

#include <iostream>

GUI::Button::Button(std::string text, FontHolder* fonts)
    : content(text), fonts(fonts), buttonColor(GREEN), buttonHoverColor(BLACK),
      textColor(WHITE), isHover(false), alignment(Left), fontSize(16),
      mActionOnHover(false) {
    DisableFitContent();
}

GUI::Button::Button()
    : buttonColor(GREEN), buttonHoverColor(BLACK), textColor(WHITE),
      isHover(false), content("test"), fontSize(16), mActionOnHover(false) {
    DisableFitContent();
}

GUI::Button::~Button() {}

void GUI::Button::SetText(std::string text) { content = text; }

void GUI::Button::Draw(Vector2 base) {
    if (!mVisible) return;
    float x = base.x + mPosition.x;
    float y = base.y + mPosition.y;
    bound.x = x, bound.y = y;

    bound.height--;
    UpdateMouseCursorWhenHover(bound, isHover, false);
    isHover = GetHoverStatus(bound, isHover, false);
    if (IsClicked() || (mActionOnHover && isHover)) action();
    bound.height++;

    DrawRectangleRec(bound, (isHover ? buttonHoverColor : buttonColor));

    DrawButtonText();
}

void GUI::Button::SetSize(float width, float height) {
    bound.width = width;
    bound.height = height;
}

void GUI::Button::SetTextColor(Color color) { textColor = color; }

void GUI::Button::SetAction(std::function< void() > clickedAction) {
    action = clickedAction;
}

bool GUI::Button::isSelectable() const { return false; }

void GUI::Button::SetFontSize(float textFontSize) { fontSize = textFontSize; }

float GUI::Button::GetFontSize() const { return fontSize; }

void GUI::Button::SetTextAlignment(TextAlignment textAlignment) {
    alignment = textAlignment;
}

void GUI::Button::EnableFitContent() {
    fitContent = true;

    FitContent();
}

void GUI::Button::DisableFitContent() { fitContent = false; }

Vector2 GUI::Button::GetSize() { return (Vector2){bound.width, bound.height}; }

void GUI::Button::SetActionOnHover(bool actionOnHover) {
    mActionOnHover = actionOnHover;
}

bool GUI::Button::IsClicked() {
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), bound));
}

void GUI::Button::DrawButtonText() {
    Font font = fonts->Get(Fonts::Default);

    DrawTextEx(font, content.c_str(), GetContentPos(), fontSize, 0, textColor);
}

Vector2 GUI::Button::GetContentPos() {
    float textWidth = GetContentSize().x;
    float x = bound.x;
    float y = bound.y + (bound.height - fontSize) / 2;
    switch (alignment) {
        case Left:
            x = bound.x + 5;
            break;
        case Center:
            x = bound.x + (bound.width - textWidth) / 2;
            break;
        case Right:
            x = bound.x + bound.width - textWidth - 5;
            break;
        default:
            break;
    }
    return (Vector2){x, y};
}

Vector2 GUI::Button::GetContentSize() {
    Font font = fonts->Get(Fonts::Default);
    return MeasureTextEx(font, content.c_str(), fontSize, 0);
}

void GUI::Button::FitContent() {
    if (!fitContent) return;
    Vector2 textSize = GetContentSize();
    bound.width = textSize.x + 10;
    bound.height = textSize.y + 6;
}

void GUI::Button::SetButtonHoverColor(Color color) { buttonHoverColor = color; }

void GUI::Button::SetButtonColor(Color color) { buttonColor = color; }
