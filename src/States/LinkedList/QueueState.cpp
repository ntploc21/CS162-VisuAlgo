#include "QueueState.hpp"

QueueState::QueueState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Queue) {}

QueueState::~QueueState() {}

void QueueState::Draw() { navigation.Draw(); }

bool QueueState::Update(float dt) { return true; }
