#ifndef STATES_LINKEDLIST_DLLSTATE_HPP
#define STATES_LINKEDLIST_DLLSTATE_HPP

#include "LLState.hpp"

class DLLState : public LLState {
public:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddUpdateOperation();
    void AddDeleteOperation();
    void AddSearchOperation();

public:
    DLLState(StateStack& stack, Context context);
    ~DLLState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_DLLSTATE_HPP