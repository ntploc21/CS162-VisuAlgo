#ifndef STATES_LINKEDLIST_SLLSTATE_HPP
#define STATES_LINKEDLIST_SLLSTATE_HPP

#include "Algorithms/LinkedList/SinglyLinkedList.hpp"
#include "LLState.hpp"

namespace State {
    class SLLState : public LLState< SLLAnimationController > {
    private:
        Algorithm::SinglyLinkedList SLL;

    private:
        void AddInsertOperation();
        void AddInitializeOperation();
        void AddUpdateOperation();
        void AddDeleteOperation();
        void AddSearchOperation();

    protected:
    public:
        SLLState(StateStack& stack, Context context);
        ~SLLState();
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_SLLSTATE_HPP