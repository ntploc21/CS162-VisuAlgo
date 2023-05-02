#ifndef STATES_LINKEDLIST_CLLSTATE_HPP
#define STATES_LINKEDLIST_CLLSTATE_HPP

#include "Algorithms/LinkedList/CircularLinkedList.hpp"
#include "LLState.hpp"

namespace State {
    class CLLState : public LLState< CLLAnimationController > {
    private:
        Algorithm::CircularLinkedList CLL;

    public:
        void AddInsertOperation();
        void AddInitializeOperation();
        void AddUpdateOperation();
        void AddDeleteOperation();
        void AddSearchOperation();

    public:
        CLLState(StateStack& stack, Context context);
        ~CLLState();
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_CLLSTATE_HPP