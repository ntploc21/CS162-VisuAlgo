#include "LLState.hpp"

#include <iostream>

LLState::LLState(StateStack& stack, Context context) : State(stack, context) {
    InitNavigationBar();
}

LLState::~LLState() {}

void LLState::InitNavigationBar() {}