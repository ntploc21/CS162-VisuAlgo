#ifndef STATES_LINKEDLIST_DLLSTATE_HPP
#define STATES_LINKEDLIST_DLLSTATE_HPP

#include "LLState.hpp"

class DLLState : public LLState {
private:
public:
    DLLState(StateStack& stack, Context context);
    ~DLLState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_DLLSTATE_HPP