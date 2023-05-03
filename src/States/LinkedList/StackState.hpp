#ifndef STATES_LINKEDLIST_STACKSTATE_HPP
#define STATES_LINKEDLIST_STACKSTATE_HPP

#include "Algorithms/LinkedList/Stack.hpp"
#include "LLState.hpp"

namespace State {
    /**
     * @brief The state class that is used to represent the stack state/scene of
     * the application.
     * @note This Stack state is using the Singly Linked List Animation
     * Controller as it can be visualized using the same animation controller.
     */
    class StackState : public LLState< SLLAnimationController > {
    private:
        /**
         * @brief The algorithm of the stack.
         */
        Algorithm::Stack mStackAlgorithm;

    public:
        /**
         * @brief Add an insert operation to the stack algorithm.
         */
        void AddInsertOperation();

        /**
         * @brief Add an initialize operation to the stack algorithm.
         */
        void AddInitializeOperation();

        /**
         * @brief Add an update operation to the stack algorithm.
         */
        void AddDeleteOperation();

        /**
         * @brief Add a delete operation to the stack algorithm.
         */
        void AddSearchOperation();

    public:
        /**
         * @brief Construct a new StackState object
         * @param stack The state stack where the stack state is pushed to.
         * @param context The context of the application.
         */
        StackState(StateStack& stack, Context context);

        /**
         * @brief Destroy the StackState object
         */
        ~StackState();
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_STACKSTATE_HPP