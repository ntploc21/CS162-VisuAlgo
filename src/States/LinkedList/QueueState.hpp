#ifndef STATES_LINKEDLIST_QUEUESTATE_HPP
#define STATES_LINKEDLIST_QUEUESTATE_HPP

#include "Algorithms/LinkedList/Queue.hpp"
#include "LLState.hpp"

namespace State {
    /**
     * @brief The state that is used to visualize the queue.
     * @note This Queue state is using the Singly Linked List Animation
     * Controller as it can be visualized using the same animation controller.
     */
    class QueueState : public LLState< SLLAnimationController > {
    private:
        /**
         * @brief The algorithm of the queue.
         */
        Algorithm::Queue queue;

    public:
        /**
         * @brief Add an insert operation to the queue algorithm.
         */
        void AddInsertOperation();

        /**
         * @brief Add an initialize operation to the queue algorithm.
         */
        void AddInitializeOperation();

        /**
         * @brief Add an update operation to the queue algorithm.
         */
        void AddDeleteOperation();

        /**
         * @brief Add a delete operation to the queue algorithm.
         */
        void AddSearchOperation();

    public:
        /**
         * @brief Construct a new QueueState object
         * @param stack The state stack where the queue state is pushed to.
         * @param context The context of the application.
         */
        QueueState(StateStack& stack, Context context);

        /**
         * @brief Destroy the QueueState object
         */
        ~QueueState();
    };
};      // namespace State

#endif  // STATES_LINKEDLIST_QUEUESTATE_HPP