#include "HomepageState.hpp"

#include <iostream>

#include "Global.hpp"
#include "Settings.hpp"

State::HomepageState::HomepageState(StateStack& stack, Context context)
    : State(stack, context) {
    InitCards();
}

State::HomepageState::~HomepageState() {}

void State::HomepageState::Draw() {
    DrawIntroduction();
    navigation.Draw();

    mCards.Draw();
}

bool State::HomepageState::Update(float dt) { return true; }

void State::HomepageState::DrawIntroduction() {
    const Color headingColor1 =
        Settings::getInstance().getColor(ColorTheme::Logo2FirstPart);
    const Color headingColor2 =
        Settings::getInstance().getColor(ColorTheme::Logo2SecondPart);
    const Color textColor = Settings::getInstance().getColor(ColorTheme::Text);

    float fontSize;
    float x, y, fullTextWidth;
    float fSpanWidth;
    Font font;
    // Draw heading
    font = GetContext().fonts->Get(Fonts::Silkscreen);
    fontSize = 72;

    fSpanWidth = MeasureTextEx(font, "Visu", fontSize, 0).x;
    fullTextWidth = MeasureTextEx(font, "VisuAlgo", fontSize, 1).x;

    x = (global::SCREEN_WIDTH - fullTextWidth) / 2;
    y = 70;
    DrawTextEx(font, "Visu", {x, y}, fontSize, 0, headingColor1);
    DrawTextEx(font, "Algo", {x + fSpanWidth, y}, fontSize, 0, headingColor2);

    // Draw description
    std::string msg =
        "visualising data structures and algorithms through animation";
    font = GetContext().fonts->Get(Fonts::Default_Italic);
    fontSize = 24;
    fullTextWidth = MeasureTextEx(font, msg.c_str(), fontSize, 0).x;

    x = (global::SCREEN_WIDTH - fullTextWidth) / 2;
    y = 220;
    DrawTextEx(font, msg.c_str(), {x, y}, fontSize, 0, textColor);
    // Draw small note (this project is the CS162 solo project...)
    msg = "CS162 Solo Project";
    font = GetContext().fonts->Get(Fonts::Silkscreen);
    fontSize = 48;

    fSpanWidth = MeasureTextEx(font, "CS162 ", fontSize, 0).x;
    fullTextWidth = MeasureTextEx(font, msg.c_str(), fontSize, 0).x;
    x = (global::SCREEN_WIDTH - fullTextWidth) / 2;
    y = 140;
    DrawTextEx(font, "CS162", {x, y}, fontSize, 0, headingColor1);
    DrawTextEx(font, "Solo Project", {x + fSpanWidth, y}, fontSize, 0,
               headingColor2);
    // Author
    msg = "@ntploc21 - 22TT2 - 22125050";
    font = GetContext().fonts->Get(Fonts::Default_Bold);
    fontSize = 24;
    fullTextWidth = MeasureTextEx(font, msg.c_str(), fontSize, 0).x;

    x = (global::SCREEN_WIDTH - fullTextWidth) / 2;
    y = 190;
    DrawTextEx(font, msg.c_str(), {x, y}, fontSize, 0, textColor);
}

void State::HomepageState::CreateCard(States::ID stateID, std::string title,
                                      Textures::ID textureID, int x, int y) {
    std::shared_ptr< GUIComponent::Card > card(new GUIComponent::Card(
        title.c_str(), GetContext().textures->Get(textureID),
        GetContext().fonts));
    card->SetPosition(x, y);
    card->SetLink([this](States::ID stateID) { RequestStackPush(stateID); });
    card->SetStateID(stateID);
    mCards.pack(card);
}

void State::HomepageState::InitCards() {
    mCards.SetPosition(60, 300);
    CreateCard(States::StaticArray, "Static Array", Textures::StaticArray, 0,
               0);
    CreateCard(States::DynamicArray, "Dynamic Array", Textures::DynamicArray,
               310, 0);
    CreateCard(States::SinglyLinkedList, "Singly Linked List",
               Textures::SinglyLinkedList, 620, 0);
    CreateCard(States::DoublyLinkedList, "Doubly Linked List",
               Textures::DoublyLinkedList, 930, 0);
    CreateCard(States::CircularLinkedList, "Circular Linked List",
               Textures::CircularLinkedList, 165, 240);
    CreateCard(States::Stack, "Stack", Textures::Stack, 475, 240);
    CreateCard(States::Queue, "Queue", Textures::Queue, 785, 240);
}
