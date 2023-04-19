#ifndef STATES_LINKEDLIST_QUEUESTATE_HPP
#define STATES_LINKEDLIST_QUEUESTATE_HPP

#include "LLState.hpp"

class QueueState : public LLState< SLLAnimationController > {
public:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddDeleteOperation();
    void AddSearchOperation();

public:
    QueueState(StateStack& stack, Context context);
    ~QueueState();
    void Draw();
};

#endif  // STATES_LINKEDLIST_QUEUESTATE_HPP