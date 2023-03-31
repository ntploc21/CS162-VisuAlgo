#include "StackState.hpp"

StackState::StackState(StateStack& stack, Context context)
    : State(stack, context) {}

StackState::~StackState() {}

void StackState::Draw() {}

bool StackState::Update(float dt) { return true; }
