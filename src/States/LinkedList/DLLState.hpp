#ifndef STATES_LINKEDLIST_DLLSTATE_HPP
#define STATES_LINKEDLIST_DLLSTATE_HPP

#include "Algorithms/LinkedList/DoublyLinkedList.hpp"
#include "LLState.hpp"

namespace State {
    /**
     * @brief The state that is used to visualize the doubly linked list.
     */
    class DLLState : public LLState< DLLAnimationController > {
    private:
        /**
         * @brief The algorithm of the doubly linked list.
         */
        Algorithm::DoublyLinkedList mDLL;

    public:
        /**
         * @brief Add an insert operation to the doubly linked list algorithm.
         */
        void AddInsertOperation();

        /**
         * @brief Add an initialize operation to the doubly linked list
         * algorithm.
         */
        void AddInitializeOperation();

        /**
         * @brief Add an update operation to the doubly linked list algorithm.
         */
        void AddUpdateOperation();

        /**
         * @brief Add a delete operation to the doubly linked list algorithm.
         */
        void AddDeleteOperation();

        /**
         * @brief Add a search operation to the doubly linked list algorithm.
         */
        void AddSearchOperation();

    public:
        /**
         * @brief Construct a new DLLState object
         * @param stack The state stack where the doubly linked list state is
         * pushed to.
         * @param context The context of the application.
         */
        DLLState(StateStack& stack, Context context);

        /**
         * @brief Destroy the DLLState object
         */
        ~DLLState();
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_DLLSTATE_HPP