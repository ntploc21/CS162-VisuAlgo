#ifndef STATES_HOMEPAGESTATE_HPP
#define STATES_HOMEPAGESTATE_HPP

#include "../State.hpp"

class HomepageState : public State {
private:
public:
    HomepageState(StateStack& stack, Context context);
    ~HomepageState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_HOMEPAGESTATE_HPP