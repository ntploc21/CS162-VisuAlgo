#ifndef STATES_LINKEDLIST_STACKSTATE_HPP
#define STATES_LINKEDLIST_STACKSTATE_HPP

#include "LLState.hpp"

class StackState : public LLState< SLLAnimationController > {
public:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddDeleteOperation();
    void AddSearchOperation();

public:
    StackState(StateStack& stack, Context context);
    ~StackState();
    void Draw();
};

#endif  // STATES_LINKEDLIST_STACKSTATE_HPP