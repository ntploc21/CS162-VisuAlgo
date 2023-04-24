#ifndef CORE_ALGORITHMS_LINKEDLIST_STACK_HPP
#define CORE_ALGORITHMS_LINKEDLIST_STACK_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"
#include "Core/Algorithms/Algorithm.hpp"

using ArrowType = GUI::SinglyLinkedList::ArrowType;
using Orientation = GUI::SinglyLinkedList::Orientation;

namespace Algorithm {
    class Stack : public Algorithm< GUI::SinglyLinkedList, SLLAnimation > {
    public:
        static constexpr int maxN = 10;
        static constexpr Orientation mStackOrientation = Orientation::Vertical;

    public:
        Stack(GUI::CodeHighlighter::Ptr codeHighlighter,
              SLLAnimationController::Ptr animController, FontHolder* fonts);
        Stack();
        ~Stack();

    public:
        void Push(int value);

    public:
        void Pop();

    public:
        void Peek();

    private:
        std::function< GUI::SinglyLinkedList(GUI::SinglyLinkedList, float,
                                             Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);
    };
};  // namespace Algorithm

#endif  // CORE_ALGORITHMS_LINKEDLIST_STACK_HPP