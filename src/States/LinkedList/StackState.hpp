#ifndef STATES_LINKEDLIST_STACKSTATE_HPP
#define STATES_LINKEDLIST_STACKSTATE_HPP

#include "Core/Algorithms/LinkedList/Stack.hpp"
#include "LLState.hpp"

class StackState : public LLState< SLLAnimationController > {
private:
    Algorithm::Stack mStackAlgorithm;

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