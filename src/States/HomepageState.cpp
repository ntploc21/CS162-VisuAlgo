#include "HomepageState.hpp"

#include <iostream>

#include "../Components/NavigationBar.hpp"

HomepageState::HomepageState(StateStack& stack, Context context)
    : State(stack, context) {}

HomepageState::~HomepageState() {}

void HomepageState::Draw() {
    NavigationBar nav =
        NavigationBar(&GetContext().fonts->Get(Fonts::Silkscreen));
    // NavigationBar nav = NavigationBar();
    nav.DrawCurrent();
    // std::cout << (GetContext().fonts == NULL) << std::endl;
    // GetContext().fonts->Get(Fonts::Silkscreen);

    // if (nav.MoveToSettings()) {
    //     RequestStackPush(States::Settings);
    // }
}

bool HomepageState::Update(float dt) { return true; }