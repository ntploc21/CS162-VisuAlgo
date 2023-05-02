#include "Card.hpp"

#include "Settings.hpp"

GUIComponent::Card::Card(std::string text, Texture thumbnail, FontHolder* fonts)
    : thumbnail(thumbnail), fonts(fonts), isHover(false) {
    title = text;
}

GUIComponent::Card::Card() : isHover(false) {}

GUIComponent::Card::~Card() {}

void GUIComponent::Card::Draw(Vector2 base) {
    bool gotoLink = false;
    if (DrawImage(base)) gotoLink = true;
    if (DrawTitle(base)) gotoLink = true;
    UpdateMouseCursorWhenHover(hoverBounds, isHover, gotoLink);
    isHover = GetHoverStatus(hoverBounds, isHover, gotoLink);
    if (gotoLink) toLink(stateID);
}

bool GUIComponent::Card::DrawImage(Vector2 base) {
    float x = base.x + mPosition.x;
    float y = base.y + mPosition.y;
    // return false;
    // ImageResize(&thumbnail, 250, 160);
    DrawTexture(thumbnail, x, y, WHITE);

    hoverBounds["image-bound"] = (Rectangle){x, y, 250, 160};
    return (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), hoverBounds["image-bound"]));
}

bool GUIComponent::Card::DrawTitle(Vector2 base) {
    const Color backgroundColor =
        Settings::getInstance().getColor(ColorTheme::Card_Background);
    const Color textColor =
        Settings::getInstance().getColor(ColorTheme::Card_Text);

    float x = base.x + mPosition.x;
    float y = base.y + mPosition.y;
    // Draw background
    DrawRectangle(x, y + 160, 250, 40, backgroundColor);
    // Draw title
    Font font = fonts->Get(Fonts::Default);
    float fontSize = 24;
    float fullTextWidth = MeasureTextEx(font, title.c_str(), fontSize, 0).x;

    x += (250 - fullTextWidth) / 2;
    y += 168;
    hoverBounds["title-bound"] = (Rectangle){x, y, fullTextWidth, 24};

    DrawTextEx(font, title.c_str(), {x, y}, fontSize, 0, textColor);

    return (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), hoverBounds["title-bound"]));
}

void GUIComponent::Card::SetLink(std::function< void(States::ID) > link) {
    toLink = link;
}

void GUIComponent::Card::SetStateID(States::ID id) { stateID = id; }

void GUIComponent::Card::SetText(std::string text) { title = text; }

bool GUIComponent::Card::isSelectable() const { return false; }