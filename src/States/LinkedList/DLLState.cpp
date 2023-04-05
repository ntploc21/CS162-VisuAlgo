#include "DLLState.hpp"

DLLState::DLLState(StateStack& stack, Context context)
    : LLState(stack, context) {}

DLLState::~DLLState() {}

void DLLState::Draw() { navigation.Draw(); }

bool DLLState::Update(float dt) { return true; }