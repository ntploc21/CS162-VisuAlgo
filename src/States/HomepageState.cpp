#include "HomepageState.hpp"

#include <iostream>

#include "../Components/NavigationBar.hpp"

HomepageState::HomepageState(StateStack& stack, Context context)
    : State(stack, context) {}

HomepageState::~HomepageState() {}

void HomepageState::Draw() { navigation.DrawCurrent(); }

bool HomepageState::Update(float dt) { return true; }