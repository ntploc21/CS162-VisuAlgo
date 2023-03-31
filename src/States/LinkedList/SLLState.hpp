#ifndef STATES_LINKEDLIST_SLLSTATE_HPP
#define STATES_LINKEDLIST_SLLSTATE_HPP

#include "../../State.hpp"

class SLLState : public State {
private:
public:
    SLLState(StateStack& stack, Context context);
    ~SLLState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_SLLSTATE_HPP