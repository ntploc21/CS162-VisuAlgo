#include "DLLState.hpp"

DLLState::DLLState(StateStack& stack, Context context)
    : State(stack, context) {}

DLLState::~DLLState() {}

void DLLState::Draw() {}

bool DLLState::Update(float dt) {}