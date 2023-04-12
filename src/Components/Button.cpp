#include "Button.hpp"

#include <iostream>

Button::Button(std::string text, FontHolder* fonts)
    : content(text), fonts(fonts), buttonColor(GREEN), buttonHoverColor(BLACK),
      textColor(WHITE), isHover(false), alignment(Left), fontSize(16) {}

Button::Button()
    : buttonColor(GREEN), buttonHoverColor(BLACK), textColor(WHITE),
      isHover(false), content("test"), fontSize(16) {}

Button::~Button() {}

void Button::SetText(std::string text) { content = text; }

void Button::Draw(Vector2 base) {
    float x = base.x + mPosition.x;
    float y = base.y + mPosition.y;
    bound.x = x, bound.y = y;

    UpdateMouseCursorWhenHover(bound, isHover, false);
    isHover = GetHoverStatus(bound, isHover, false);
    if (IsClicked()) action();

    DrawRectangleRec(bound, (isHover ? buttonHoverColor : buttonColor));

    DrawButtonText();
}

void Button::SetSize(float width, float height) {
    bound.width = width;
    bound.height = height;
}

void Button::SetTextColor(Color color) { textColor = color; }

void Button::SetAction(std::function< void() > clickedAction) {
    action = clickedAction;
}

bool Button::isSelectable() const { return false; }

void Button::SetFontSize(float textFontSize) { fontSize = textFontSize; }

float Button::GetFontSize() const { return fontSize; }

void Button::SetTextAlignment(TextAlignment textAlignment) {
    alignment = textAlignment;
}

bool Button::IsClicked() {
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), bound));
}

void Button::DrawButtonText() {
    Font font = fonts->Get(Fonts::Default);

    DrawTextEx(font, content.c_str(), GetTextPos(), fontSize, 0, textColor);
}

Vector2 Button::GetTextPos() {
    Font font = fonts->Get(Fonts::Default);
    float textWidth = MeasureTextEx(font, content.c_str(), fontSize, 0).x;
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

void Button::SetButtonHoverColor(Color color) { buttonHoverColor = color; }

void Button::SetButtonColor(Color color) { buttonColor = color; }
