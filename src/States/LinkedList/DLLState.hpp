#ifndef STATES_LINKEDLIST_DLLSTATE_HPP
#define STATES_LINKEDLIST_DLLSTATE_HPP

#include "Core/Algorithms/LinkedList/DoublyLinkedList.hpp"
#include "LLState.hpp"

class DLLState : public LLState< DLLAnimationController > {
private:
    Algorithm::DoublyLinkedList mDLL;

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
};

#endif  // STATES_LINKEDLIST_DLLSTATE_HPP