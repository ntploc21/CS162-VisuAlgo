#ifndef CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"

namespace Algorithm {
    /**
     * @brief The algorithm class that is used to generate step-by-step
     * instructions for the visualization of the singly linked list.
     */
    class SinglyLinkedList
        : public Algorithm< GUIVisualizer::SinglyLinkedList, SLLAnimation > {
    public:
        /**
         * @brief The maximum number of elements that the singly linked list can
         * hold.
         */
        static constexpr int maxN = 16;

    public:
        /**
         * @brief The constructor of the singly linked list algorithm.
         */
        SinglyLinkedList();

        /**
         * @brief The constructor of the singly linked list algorithm.
         * @param codeHighlighter The code highlighter of the singly linked list
         * algorithm.
         * @param animController The animation controller of the singly linked
         * list algorithm.
         * @param fonts The fonts of the singly linked list algorithm.
         */
        SinglyLinkedList(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
                         SLLAnimationController::Ptr animController,
                         FontHolder* fonts);

        /**
         * @brief The destructor of the singly linked list algorithm.
         * @note This destructor is not virtual because this class is not
         * designed to be inherited.
         */
        ~SinglyLinkedList();

        /**
         * @brief Return the size of the singly linked list.
         * @return The size of the singly linked list.
         */
        std::size_t size() const;

    public:
        /**
         * @brief Insert a new element before the head of the singly linked
         * list.
         * @param value The value of the new element.
         */
        void InsertHead(int value);

        /**
         * @brief Insert a new element after the tail of the singly linked list.
         * @param value The value of the new element.
         */
        void InsertAfterTail(int value);

        /**
         * @brief Insert a new element at the middle (not before the head or
         * after the tail) of the singly linked list.
         * @param index The index of the new element.
         * @param value The value of the new element.
         * @note This function is written as the visualization of inserting a
         * new element at the middle of the singly linked list is different from
         * inserting a new element at the head or tail of the singly linked
         * list.
         */
        void InsertMiddle(int index, int value);

    public:
        /**
         * @brief Delete the head of the singly linked list.
         */
        void DeleteHead();

        /**
         * @brief Delete the tail of the singly linked list.
         */
        void DeleteTail();

        /**
         * @brief Delete the middle (not the head or tail) of the singly linked
         * list.
         * @param index The index of the element to be deleted.
         * @note This function is written as the visualization of deleting an
         * element at the middle of the singly linked list is different from
         * deleting an element at the head or tail of the singly linked list.
         */
        void DeleteMiddle(int index);

    public:
        /**
         * @brief Update the value of the head of the singly linked list.
         * @param value The new value of the head of the singly linked list.
         */
        void Update(int index, int value);

    public:
        /**
         * @brief Search for an element in the singly linked list.
         * @param value The value of the element to be searched.
         */
        void Search(int value);

    private:
        /**
         * @brief Generate a highlight arrow from the node at the given index to
         * the next node.
         * @param index The index of the node to be highlighted.
         * @param drawVisualizer Whether to draw the visualizer, this is set to
         * true by default.
         * @param reverse Whether to reverse the animation (play the animation
         * in reverse), this is set to false by default.
         * @return The animation of the highlight arrow.
         */
        std::function< GUIVisualizer::SinglyLinkedList(
            GUIVisualizer::SinglyLinkedList, float, Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);

    private:
        /**
         * @brief Reset the visualizer of the singly linked list algorithm.
         * @note This function is used to reset all of the effects that are only
         * used to visualize the algorithm (i.e highlight the elements that are
         * currently iterated).
         */
        void ResetVisualizer();
    };
};      // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP