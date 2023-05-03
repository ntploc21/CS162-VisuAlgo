#ifndef CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP
#define CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP

#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"

namespace Algorithm {
    /**
     * @brief The algorithm class that is used to generate step-by-step
     * instructions for the visualization of the queue.
     */
    class Queue
        : public Algorithm< GUIVisualizer::SinglyLinkedList, SLLAnimation > {
    public:
        /**
         * @brief The maximum number of elements that the queue can hold.
         */
        static constexpr int maxN = 16;

    public:
        /**
         * @brief The constructor of the queue algorithm.
         * @param codeHighlighter The code highlighter of the queue algorithm.
         * @param animController The animation controller of the queue
         * algorithm.
         * @param fonts The fonts of the queue algorithm.
         */
        Queue(GUIComponent::CodeHighlighter::Ptr _codeHighlighter,
              SLLAnimationController::Ptr animController, FontHolder* fonts);

        /**
         * @brief The destructor of the queue algorithm.
         * @note This destructor is not virtual because this class is not
         * designed to be inherited.
         */
        Queue();

        /**
         * @brief Return the size of the queue.
         * @return The size of the queue.
         */
        ~Queue();

        /**
         * @brief Return the size of the queue.
         * @return The size of the queue.
         */
        std::size_t size() const;

    public:
        /**
         * @brief Insert a new element when the queue is empty.
         * @param value The value of the new element.
         */
        void EnqueueEmpty(int value);

        /**
         * @brief Insert a new element at the back of the queue (after the tail
         * of the singly linked list).
         * @param value The value of the new element.
         */
        void Enqueue(int value);

    public:
        /**
         * @brief Remove the element at the front of the queue (the head
         * of the singly linked list).
         */
        void Dequeue();

    public:
        /**
         * @brief Return the value of the element at the front of the queue
         * (the head of the singly linked list).
         * @return The value of the element at the front of the queue.
         */
        void PeekFront();

        /**
         * @brief Return the value of the element at the back of the queue
         * (the tail of the singly linked list).
         * @return The value of the element at the back of the queue.
         */
        void PeekBack();

    private:
        /**
         * @brief Reset the visualizer of the singly linked list algorithm.
         * @note This function is used to reset all of the effects that are only
         * used to visualize the algorithm (i.e highlight the elements that are
         * currently iterated).
         */
        std::function< GUIVisualizer::SinglyLinkedList(
            GUIVisualizer::SinglyLinkedList, float, Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);
    };
};      // namespace Algorithm

#endif  // CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP