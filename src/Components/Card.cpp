#include "Card.hpp"

Card::Card(int cornerX, int cornerY, std::string text, Texture thumbnail,
           FontHolder* fonts)
    : cornerX(cornerX), cornerY(cornerY), thumbnail(thumbnail), fonts(fonts) {
    title = text;
}

Card::Card() {}

Card::~Card() {}

void Card::DrawCurrent() {
    if (DrawImage()) toLink(stateID);
    if (DrawTitle()) toLink(stateID);
}

bool Card::DrawImage() {
    // return false;
    // ImageResize(&thumbnail, 250, 160);
    DrawTexture(thumbnail, cornerX, cornerY, WHITE);

    Rectangle imageBound = (Rectangle){cornerX, cornerY, 250, 160};
    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), imageBound));
}

bool Card::DrawTitle() {
    // Draw background
    DrawRectangle(cornerX, cornerY + 160, 250, 40, LIGHTGRAY);
    // Draw title
    Font font = fonts->Get(Fonts::Default);
    float fontSize = 24;
    float fullTextWidth = MeasureTextEx(font, title.c_str(), fontSize, 0).x;

    float x = cornerX + (250 - fullTextWidth) / 2;
    float y = cornerY + 168;
    Rectangle titleBound = (Rectangle){x, y, fullTextWidth, 24};

    DrawTextEx(font, title.c_str(), {x, y}, fontSize, 0, BLACK);

    return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), titleBound));
}

void Card::SetLink(std::function< void(States::ID) > link) { toLink = link; }

void Card::SetStateID(States::ID id) { stateID = id; }

void Card::SetText(std::string text) { title = text; }