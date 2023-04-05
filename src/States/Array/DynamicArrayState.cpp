#include "DynamicArrayState.hpp"

DynamicArrayState::DynamicArrayState(StateStack& stack, Context context)
    : ArrayState(stack, context, DataStructures::DynamicArray) {}

DynamicArrayState::~DynamicArrayState() {}

void DynamicArrayState::Draw() { navigation.Draw(); }

bool DynamicArrayState::Update(float dt) { return true; }
