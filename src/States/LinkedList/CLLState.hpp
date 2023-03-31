#ifndef STATES_LINKEDLIST_CLLSTATE_HPP
#define STATES_LINKEDLIST_CLLSTATE_HPP

#include "../../State.hpp"

class CLLState : public State {
private:
public:
    CLLState(StateStack& stack, Context context);
    ~CLLState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_CLLSTATE_HPP