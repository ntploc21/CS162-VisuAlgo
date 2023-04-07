#include "HomepageState.hpp"

#include <iostream>

#include "Global.hpp"

HomepageState::HomepageState(StateStack& stack, Context context)
    : State(stack, context) {
    InitCards();
}

HomepageState::~HomepageState() {}

void HomepageState::Draw() {
    DrawIntroduction();
    navigation.Draw();
    for (auto& it : mCards) {
        it.second->Draw();
    }
}

bool HomepageState::Update(float dt) { return true; }

void HomepageState::DrawIntroduction() {
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

    DrawTextEx(font, "Visu", {x, y}, fontSize, 0, BLACK);
    DrawTextEx(font, "Algo", {x + fSpanWidth, y}, fontSize, 0, ORANGE);

    // Draw description
    std::string msg =
        "visualising data structures and algorithms through animation";
    font = GetContext().fonts->Get(Fonts::Default_Italic);
    fontSize = 24;
    fullTextWidth = MeasureTextEx(font, msg.c_str(), fontSize, 0).x;

    x = (global::SCREEN_WIDTH - fullTextWidth) / 2;
    y = 220;
    DrawTextEx(font, msg.c_str(), {x, y}, fontSize, 0, BLACK);
    // Draw small note (this project is the CS162 solo project...)
    msg = "CS162 Solo Project";
    font = GetContext().fonts->Get(Fonts::Silkscreen);
    fontSize = 48;

    fSpanWidth = MeasureTextEx(font, "CS162 ", fontSize, 0).x;
    fullTextWidth = MeasureTextEx(font, msg.c_str(), fontSize, 0).x;
    x = (global::SCREEN_WIDTH - fullTextWidth) / 2;
    y = 140;
    DrawTextEx(font, "CS162", {x, y}, fontSize, 0, BLACK);
    DrawTextEx(font, "Solo Project", {x + fSpanWidth, y}, fontSize, 0, ORANGE);
    // Author
    msg = "@ntploc21 - 22TT2 - 22125050";
    font = GetContext().fonts->Get(Fonts::Default_Bold);
    fontSize = 24;
    fullTextWidth = MeasureTextEx(font, msg.c_str(), fontSize, 0).x;

    x = (global::SCREEN_WIDTH - fullTextWidth) / 2;
    y = 190;
    DrawTextEx(font, msg.c_str(), {x, y}, fontSize, 0, BLACK);
}

void HomepageState::CreateCard(States::ID stateID, std::string title,
                               Textures::ID textureID, int x, int y) {
    std::unique_ptr< Card > card(new Card(title.c_str(),
                                          GetContext().textures->Get(textureID),
                                          GetContext().fonts));
    card->SetPosition(x, y);
    card->SetLink([this](States::ID stateID) { RequestStackPush(stateID); });
    card->SetStateID(stateID);
    auto inserted = mCards.insert(std::make_pair(stateID, std::move(card)));
    // mCards[stateID] = std::move(card);
}

void HomepageState::InitCards() {
    CreateCard(States::StaticArray, "Static Array", Textures::StaticArray, 40,
               300);
    CreateCard(States::DynamicArray, "Dynamic Array", Textures::DynamicArray,
               330, 300);
    CreateCard(States::SinglyLinkedList, "Singly Linked List",
               Textures::SinglyLinkedList, 620, 300);
    CreateCard(States::DoublyLinkedList, "Doubly Linked List",
               Textures::DoublyLinkedList, 910, 300);
    CreateCard(States::CircularLinkedList, "Circular Linked List",
               Textures::CircularLinkedList, 185, 540);
    CreateCard(States::Stack, "Stack", Textures::Stack, 475, 540);
    CreateCard(States::Queue, "Queue", Textures::Queue, 765, 540);
}
