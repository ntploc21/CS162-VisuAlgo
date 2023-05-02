#ifndef STATES_LINKEDLIST_STACKSTATE_HPP
#define STATES_LINKEDLIST_STACKSTATE_HPP

#include "Algorithms/LinkedList/Stack.hpp"
#include "LLState.hpp"

namespace State {
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
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_STACKSTATE_HPP