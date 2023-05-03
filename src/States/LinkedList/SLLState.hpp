#ifndef STATES_LINKEDLIST_SLLSTATE_HPP
#define STATES_LINKEDLIST_SLLSTATE_HPP

#include "Algorithms/LinkedList/SinglyLinkedList.hpp"
#include "LLState.hpp"

namespace State {
    /**
     * @brief The state class that is used to represent the singly linked list
     * state/scene of the application.
     */
    class SLLState : public LLState< SLLAnimationController > {
    private:
        /**
         * @brief The algorithm of the singly linked list.
         */
        Algorithm::SinglyLinkedList SLL;

    private:
        /**
         * @brief Add an insert operation to the singly linked list algorithm.
         */
        void AddInsertOperation();

        /**
         * @brief Add an initialize operation to the singly linked list
         * algorithm.
         */
        void AddInitializeOperation();

        /**
         * @brief Add an update operation to the singly linked list algorithm.
         */
        void AddUpdateOperation();

        /**
         * @brief Add a delete operation to the singly linked list algorithm.
         */
        void AddDeleteOperation();

        /**
         * @brief Add a search operation to the singly linked list algorithm.
         */
        void AddSearchOperation();

    public:
        /**
         * @brief Construct a new SLLState object
         * @param stack The state stack where the singly linked list state is
         * pushed to.
         * @param context The context of the application.
         */
        SLLState(StateStack& stack, Context context);

        /**
         * @brief Destroy the SLLState object
         */
        ~SLLState();
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_SLLSTATE_HPP