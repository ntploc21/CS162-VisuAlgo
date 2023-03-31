#ifndef STATES_LINKEDLIST_STACKSTATE_HPP
#define STATES_LINKEDLIST_STACKSTATE_HPP

#include "../../State.hpp"

class StackState : public State {
private:
public:
    StackState(StateStack& stack, Context context);
    ~StackState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_STACKSTATE_HPP