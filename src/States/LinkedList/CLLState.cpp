#include "CLLState.hpp"

CLLState::CLLState(StateStack& stack, Context context)
    : State(stack, context) {}

CLLState::~CLLState() {}

void CLLState::Draw() { navigation.Draw(); }

bool CLLState::Update(float dt) { return true; }