#include "CLLState.hpp"

CLLState::CLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::CircularLinkedList) {}

CLLState::~CLLState() {}

void CLLState::Draw() { navigation.Draw(); }

bool CLLState::Update(float dt) { return true; }