#include "QueueState.hpp"

QueueState::QueueState(StateStack& stack, Context context)
    : State(stack, context) {}

QueueState::~QueueState() {}

void QueueState::Draw() { navigation.Draw(); }

bool QueueState::Update(float dt) { return true; }
