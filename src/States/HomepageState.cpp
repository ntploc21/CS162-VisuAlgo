#include "HomepageState.hpp"

#include <iostream>

#include "../Components/NavigationBar.hpp"

HomepageState::HomepageState(StateStack& stack, Context context)
    : State(stack, context) {}

HomepageState::~HomepageState() {}

void HomepageState::Draw() {
    NavigationBar nav = NavigationBar(0, 0);
    nav.DrawCurrent();

    // if (nav.MoveToSettings()) {
    //     RequestStackPush(States::Settings);
    // }
}

bool HomepageState::Update(float dt) { return true; }