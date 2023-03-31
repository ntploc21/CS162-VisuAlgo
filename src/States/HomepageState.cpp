#include "HomepageState.hpp"

HomepageState::HomepageState(StateStack& stack, Context context)
    : State(stack, context) {}

HomepageState::~HomepageState() {}

void HomepageState::Draw() {}

bool HomepageState::Update(float dt) { return true; }