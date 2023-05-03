#ifndef STATES_LINKEDLIST_CLLSTATE_HPP
#define STATES_LINKEDLIST_CLLSTATE_HPP

#include "Algorithms/LinkedList/CircularLinkedList.hpp"
#include "LLState.hpp"

namespace State {
    /**
     * @brief The state class that is used to represent the circular linked list
     * state/scene of the application.
     */
    class CLLState : public LLState< CLLAnimationController > {
    private:
        /**
         * @brief The algorithm of the circular linked list.
         */
        Algorithm::CircularLinkedList CLL;

    public:
        /**
         * @brief Add an insert operation to the circular linked list algorithm.
         */
        void AddInsertOperation();

        /**
         * @brief Add an initialize operation to the circular linked list
         * algorithm.
         */
        void AddInitializeOperation();

        /**
         * @brief Add an update operation to the circular linked list algorithm.
         */
        void AddUpdateOperation();

        /**
         * @brief Add a delete operation to the circular linked list algorithm.
         */
        void AddDeleteOperation();

        /**
         * @brief Add a search operation to the circular linked list algorithm.
         */
        void AddSearchOperation();

    public:
        /**
         * @brief Construct a new CLLState object
         * @param stack The state stack where the circular linked list state is
         * pushed to.
         * @param context The context of the application.
         */
        CLLState(StateStack& stack, Context context);

        /**
         * @brief Destroy the CLLState object
         */
        ~CLLState();
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_CLLSTATE_HPP