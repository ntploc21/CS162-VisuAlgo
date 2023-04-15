#include "Card.hpp"

GUI::Card::Card(std::string text, Texture thumbnail, FontHolder* fonts)
    : thumbnail(thumbnail), fonts(fonts), isHover(false) {
    title = text;
}

GUI::Card::Card() : isHover(false) {}

GUI::Card::~Card() {}

void GUI::Card::Draw(Vector2 base) {
    bool gotoLink = false;
    if (DrawImage(base)) gotoLink = true;
    if (DrawTitle(base)) gotoLink = true;
    UpdateMouseCursorWhenHover(hoverBounds, isHover, gotoLink);
    isHover = GetHoverStatus(hoverBounds, isHover, gotoLink);
    if (gotoLink) toLink(stateID);
}

bool GUI::Card::DrawImage(Vector2 base) {
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

bool GUI::Card::DrawTitle(Vector2 base) {
    float x = base.x + mPosition.x;
    float y = base.y + mPosition.y;
    // Draw background
    DrawRectangle(x, y + 160, 250, 40, LIGHTGRAY);
    // Draw title
    Font font = fonts->Get(Fonts::Default);
    float fontSize = 24;
    float fullTextWidth = MeasureTextEx(font, title.c_str(), fontSize, 0).x;

    x += (250 - fullTextWidth) / 2;
    y += 168;
    hoverBounds["title-bound"] = (Rectangle){x, y, fullTextWidth, 24};

    DrawTextEx(font, title.c_str(), {x, y}, fontSize, 0, BLACK);

    return (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), hoverBounds["title-bound"]));
}

void GUI::Card::SetLink(std::function< void(States::ID) > link) {
    toLink = link;
}

void GUI::Card::SetStateID(States::ID id) { stateID = id; }

void GUI::Card::SetText(std::string text) { title = text; }

bool GUI::Card::isSelectable() const { return false; }