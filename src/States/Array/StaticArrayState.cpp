#include "StaticArrayState.hpp"

StaticArrayState::StaticArrayState(StateStack& stack, Context context)
    : State(stack, context) {}

StaticArrayState::~StaticArrayState() {}

void StaticArrayState::Draw() {}

bool StaticArrayState::Update(float dt) { return true; }
