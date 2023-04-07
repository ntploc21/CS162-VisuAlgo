#include "Card.hpp"

Card::Card(std::string text, Texture thumbnail, FontHolder* fonts)
    : thumbnail(thumbnail), fonts(fonts) {
    title = text;
}

Card::Card() {}

Card::~Card() {}

void Card::Draw(Vector2 base) {
    if (DrawImage(base)) toLink(stateID);
    if (DrawTitle(base)) toLink(stateID);
}

bool Card::DrawImage(Vector2 base) {
    // return false;
    // ImageResize(&thumbnail, 250, 160);
    DrawTexture(thumbnail, position.x, position.y, WHITE);

    Rectangle imageBound = (Rectangle){position.x, position.y, 250, 160};
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), imageBound));
}

bool Card::DrawTitle(Vector2 base) {
    // Draw background
    DrawRectangle(position.x, position.y + 160, 250, 40, LIGHTGRAY);
    // Draw title
    Font font = fonts->Get(Fonts::Default);
    float fontSize = 24;
    float fullTextWidth = MeasureTextEx(font, title.c_str(), fontSize, 0).x;

    float x = position.x + (250 - fullTextWidth) / 2;
    float y = position.y + 168;
    Rectangle titleBound = (Rectangle){x, y, fullTextWidth, 24};

    DrawTextEx(font, title.c_str(), {x, y}, fontSize, 0, BLACK);

    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), titleBound));
}

void Card::SetLink(std::function< void(States::ID) > link) { toLink = link; }

void Card::SetStateID(States::ID id) { stateID = id; }

void Card::SetText(std::string text) { title = text; }

bool Card::isSelectable() const { return false; }