#ifndef STATES_LINKEDLIST_CLLSTATE_HPP
#define STATES_LINKEDLIST_CLLSTATE_HPP

#include "LLState.hpp"

class CLLState : public LLState {
public:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddUpdateOperation();
    void AddDeleteOperation();
    void AddSearchOperation();

public:
    CLLState(StateStack& stack, Context context);
    ~CLLState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_CLLSTATE_HPP