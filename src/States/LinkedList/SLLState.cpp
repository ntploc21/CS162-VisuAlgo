#include "SLLState.hpp"

SLLState::SLLState(StateStack& stack, Context context)
    : State(stack, context) {}

SLLState::~SLLState() {}

void SLLState::Draw() {}

bool SLLState::Update(float dt) { return true; }