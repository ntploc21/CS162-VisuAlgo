#ifndef CORE_DATASTRUCTURES_LINKEDLIST_DOUBLYLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_DOUBLYLINKEDLIST_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/DoublyLinkedList.hpp"

namespace Algorithm {
    /**
     * @brief The algorithm class that is used to generate step-by-step
     * instructions for the visualization of the doubly linked list.
     */
    class DoublyLinkedList
        : public Algorithm< GUIVisualizer::DoublyLinkedList, DLLAnimation > {
    public:
        /**
         * @brief The maximum number of elements that the doubly linked list can
         * hold.
         */
        static constexpr int maxN = 16;

    public:
        /**
         * @brief The constructor of the doubly linked list algorithm.
         */
        DoublyLinkedList();

        /**
         * @brief The constructor of the doubly linked list algorithm.
         * @param codeHighlighter The code highlighter of the doubly linked list
         * algorithm.
         * @param animController The animation controller of the doubly linked
         * list algorithm.
         * @param fonts The fonts of the doubly linked list algorithm.
         */
        DoublyLinkedList(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
                         DLLAnimationController::Ptr animController,
                         FontHolder* fonts);

        /**
         * @brief The destructor of the doubly linked list algorithm.
         * @note This destructor is not virtual because this class is not
         * designed to be inherited.
         */
        ~DoublyLinkedList();

        /**
         * @brief Return the size of the doubly linked list.
         * @return The size of the doubly linked list.
         */
        std::size_t size() const;

    public:
        /**
         * @brief Insert a new element before the head of the doubly linked
         * list.
         * @param value The value of the new element.
         */
        void InsertHead(int value);

        /**
         * @brief Insert a new element after the tail of the doubly linked
         * list.
         * @param value The value of the new element.
         */
        void InsertAfterTail(int value);

        /**
         * @brief Insert a new element at the middle of the doubly linked
         * list.
         * @param index The index of the new element.
         * @param value The value of the new element.
         * @note This function is written as the visualization of inserting a
         * new element at the middle of the doubly linked list is different from
         * inserting a new element at the head or tail of the doubly linked
         * list.
         */
        void InsertMiddle(int index, int value);

    public:
        /**
         * @brief Delete the head of the doubly linked list.
         */
        void DeleteHead();

        /**
         * @brief Delete the tail of the doubly linked list.
         */
        void DeleteTail();

        /**
         * @brief Delete an element at the middle of the doubly linked list.
         * @param index The index of the element to be deleted.
         * @note This function is written as the visualization of deleting an
         * element at the middle of the doubly linked list is different from
         * deleting an element at the head or tail of the doubly linked list.
         */
        void DeleteMiddle(int index);

    public:
        /**
         * @brief Update the value of an element at the head of the doubly
         * linked list.
         * @param value The new value of the element.
         */
        void Update(int index, int value);

    public:
        /**
         * @brief Search for an element in the doubly linked list.
         * @param value The value of the element to be searched.
         */
        void Search(int value);

    private:
        /**
         * @brief Generate a highlight arrow from the node at the given index to
         * the next node of the doubly linked list.
         * @param index The index of the node.
         * @param drawVisualizer Whether to draw the visualizer, this is set to
         * true by default.
         * @param reverse Whether to reverse the animation, this is set to false
         * by default.
         * @return The animation of the highlight arrow.
         */
        std::function< GUIVisualizer::DoublyLinkedList(
            GUIVisualizer::DoublyLinkedList, float, Vector2) >
        HighlightArrowNext(int index, bool drawVisualizer = true,
                           bool reverse = false);

        /**
         * @brief Generate a highlight arrow from the next node at the given
         * index to the node at the given index of the doubly linked list.
         * @param index The index of the node.
         * @param drawVisualizer Whether to draw the visualizer, this is set to
         * true by default.
         * @param reverse Whether to reverse the animation, this is set to false
         * by default.
         * @return The animation of the highlight arrow.
         */
        std::function< GUIVisualizer::DoublyLinkedList(
            GUIVisualizer::DoublyLinkedList, float, Vector2) >
        HighlightArrowPrev(int index, bool drawVisualizer = true,
                           bool reverse = false);

        /**
         * @brief Generate a highlight arrow from the node at the given index to
         * the previous node of the doubly linked list (in both direction).
         * @param index The index of the node.
         * @param drawVisualizer Whether to draw the visualizer, this is set to
         * true by default.
         * @param reverse Whether to reverse the animation, this is set to false
         * by default.
         * @return The animation of the highlight arrow.
         */
        std::function< GUIVisualizer::DoublyLinkedList(
            GUIVisualizer::DoublyLinkedList, float, Vector2) >
        HighlightArrowBoth(int index, bool drawVisualizer = true,
                           bool reverse = false);

    private:
        /**
         * @brief Reset the visualizer of the doubly linked list algorithm.
         * @note This function is used to reset all of the effects that are only
         * used to visualize the algorithm (i.e highlight the elements that are
         * currently iterated).
         */
        void ResetVisualizer();
    };
};      // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_DOUBLYLINKEDLIST_HPP