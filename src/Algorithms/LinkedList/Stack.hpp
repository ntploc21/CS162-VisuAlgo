#ifndef CORE_ALGORITHMS_LINKEDLIST_STACK_HPP
#define CORE_ALGORITHMS_LINKEDLIST_STACK_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"

using ArrowType = GUIVisualizer::SinglyLinkedList::ArrowType;
using Orientation = GUIVisualizer::LinkedList::Orientation;

namespace Algorithm {
    /**
     * @brief The algorithm class that is used to generate step-by-step
     * instructions for the visualization of the stack.
     */
    class Stack
        : public Algorithm< GUIVisualizer::SinglyLinkedList, SLLAnimation > {
    public:
        /**
         * @brief The maximum number of elements that the stack can hold.
         */
        static constexpr int maxN = 10;

        /**
         * @brief The orientation of the stack, which is vertical.
         */
        static constexpr Orientation mStackOrientation = Orientation::Vertical;

    public:
        /**
         * @brief The constructor of the stack algorithm.
         * @param codeHighlighter The code highlighter of the stack algorithm.
         * @param animController The animation controller of the stack
         * algorithm.
         * @param fonts The fonts of the stack algorithm.
         */
        Stack(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
              SLLAnimationController::Ptr animController, FontHolder* fonts);

        /**
         * @brief The constructor of the stack algorithm.
         */
        Stack();

        /**
         * @brief The destructor of the stack algorithm.
         * @note This destructor is not virtual because this class is not
         * designed to be inherited.
         */
        ~Stack();

        /**
         * @brief Return the size of the stack.
         * @return The size of the stack.
         */
        std::size_t size() const;

    public:
        /**
         * @brief Insert a new element before the head of the stack.
         * @param value The value of the new element.
         */
        void Push(int value);

    public:
        /**
         * @brief Remove the element at the head of the stack.
         */
        void Pop();

    public:
        /**
         * @brief Return the value of the element at the head of the stack.
         * @return The value of the element at the head of the stack.
         */
        void Peek();

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
    };
};      // namespace Algorithm

#endif  // CORE_ALGORITHMS_LINKEDLIST_STACK_HPP