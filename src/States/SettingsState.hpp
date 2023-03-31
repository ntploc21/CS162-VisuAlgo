#ifndef STATES_SETTINGSSTATE_HPP
#define STATES_SETTINGSSTATE_HPP

#include "../State.hpp"

class SettingsState : public State {
private:
public:
    SettingsState(StateStack& stack, Context context);
    ~SettingsState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_SETTINGSSTATE_HPP