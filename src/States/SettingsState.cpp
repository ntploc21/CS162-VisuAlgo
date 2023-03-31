#include "SettingsState.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {}

SettingsState::~SettingsState() {}

void SettingsState::Draw() {}

bool SettingsState::Update(float dt) { return true; }