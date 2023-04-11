#include "Card.hpp"

Card::Card(std::string text, Texture thumbnail, FontHolder* fonts)
    : thumbnail(thumbnail), fonts(fonts), isHover(false) {
    title = text;
}

Card::Card() : isHover(false) {}

Card::~Card() {}

void Card::Draw(Vector2 base) {
    bool gotoLink = false;
    if (DrawImage(base)) gotoLink = true;
    if (DrawTitle(base)) gotoLink = true;
    UpdateHover(hoverBounds, isHover, gotoLink);
    if (gotoLink) toLink(stateID);
}

bool Card::DrawImage(Vector2 base) {
    float x = base.x + position.x;
    float y = base.y + position.y;
    // return false;
    // ImageResize(&thumbnail, 250, 160);
    DrawTexture(thumbnail, x, y, WHITE);

    hoverBounds["image-bound"] = (Rectangle){x, y, 250, 160};
    return (
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), hoverBounds["image-bound"]));
}

bool Card::DrawTitle(Vector2 base) {
    float x = base.x + position.x;
    float y = base.y + position.y;
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

void Card::SetLink(std::function< void(States::ID) > link) { toLink = link; }

void Card::SetStateID(States::ID id) { stateID = id; }

void Card::SetText(std::string text) { title = text; }

bool Card::isSelectable() const { return false; }