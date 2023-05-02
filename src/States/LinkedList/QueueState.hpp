#ifndef STATES_LINKEDLIST_QUEUESTATE_HPP
#define STATES_LINKEDLIST_QUEUESTATE_HPP

#include "Algorithms/LinkedList/Queue.hpp"
#include "LLState.hpp"

class QueueState : public LLState< SLLAnimationController > {
private:
    Algorithm::Queue queue;

public:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddDeleteOperation();
    void AddSearchOperation();

public:
    QueueState(StateStack& stack, Context context);
    ~QueueState();
};

#endif  // STATES_LINKEDLIST_QUEUESTATE_HPP