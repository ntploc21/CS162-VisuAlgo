#ifndef STATES_LINKEDLIST_QUEUESTATE_HPP
#define STATES_LINKEDLIST_QUEUESTATE_HPP

#include "LLState.hpp"

class QueueState : public LLState {
private:
public:
    QueueState(StateStack& stack, Context context);
    ~QueueState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_QUEUESTATE_HPP