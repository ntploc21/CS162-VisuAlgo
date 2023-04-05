#include "SettingsState.hpp"

#include <iostream>

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    navigation.AtSettings(true);
}

SettingsState::~SettingsState() {}

void SettingsState::Draw() { navigation.Draw(); }

bool SettingsState::Update(float dt) { return true; }