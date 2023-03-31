#include "State.hpp"

#include "StateStack.hpp"

State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context) {}

State::~State() {}

void State::RequestStackPush(States::ID stateID) { mStack->PushState(stateID); }

void State::RequestStackPop() { mStack->PopState(); }

void State::RequestStackClear() { mStack->ClearStates(); }

State::Context State::GetContext() const { return mContext; }