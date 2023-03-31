#ifndef STATES_LINKEDLIST_DLLSTATE_HPP
#define STATES_LINKEDLIST_DLLSTATE_HPP

#include "../../State.hpp"

class DLLState : public State {
private:
public:
    DLLState(StateStack& stack, Context context);
    ~DLLState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_DLLSTATE_HPP