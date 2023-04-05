#include "SLLState.hpp"

#include <iostream>

SLLState::SLLState(StateStack& stack, Context context)
    : LLState(stack, context) {}

SLLState::~SLLState() {}

void SLLState::Draw() { navigation.Draw(); }

bool SLLState::Update(float dt) { return true; }