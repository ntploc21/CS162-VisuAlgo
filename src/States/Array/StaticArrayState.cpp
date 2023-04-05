#include "StaticArrayState.hpp"

StaticArrayState::StaticArrayState(StateStack& stack, Context context)
    : ArrayState(stack, context, DataStructures::StaticArray) {}

StaticArrayState::~StaticArrayState() {}

void StaticArrayState::Draw() { navigation.Draw(); }

bool StaticArrayState::Update(float dt) { return true; }
