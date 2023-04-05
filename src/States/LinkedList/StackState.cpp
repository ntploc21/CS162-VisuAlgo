#include "StackState.hpp"

StackState::StackState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Stack) {}

StackState::~StackState() {}

void StackState::Draw() { navigation.Draw(); }

bool StackState::Update(float dt) { return true; }
