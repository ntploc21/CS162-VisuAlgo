#ifndef CORE_DATASTRUCTURES_LINKEDLIST_CIRCULARLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_CIRCULARLINKEDLIST_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Components/Visualization/CircularLinkedList.hpp"
#include "Core/Algorithms/Algorithm.hpp"

namespace Algorithm {
    class CircularLinkedList
        : public Algorithm< GUI::CircularLinkedList, CLLAnimation > {
    public:
        static constexpr int maxN = 10;

    public:
        CircularLinkedList();
        CircularLinkedList(GUI::CodeHighlighter::Ptr codeHighlighter,
                           CLLAnimationController::Ptr animController,
                           FontHolder* fonts);
        ~CircularLinkedList();

    public:
        void InsertHead(int value);
        void InsertAfterTail(int value);
        void InsertMiddle(int index, int value);

    public:
        void DeleteHead();
        void DeleteTail();
        void DeleteMiddle(int index);

    public:
        void Update(int index, int value);

    public:
        void Search(int value);

    private:
        std::function< GUI::CircularLinkedList(GUI::CircularLinkedList, float,
                                               Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);
        std::function< GUI::CircularLinkedList(GUI::CircularLinkedList, float,
                                               Vector2) >
        HighlightCircularArrow(bool drawVisualizer = true,
                               bool reverse = false);

    private:
        void ResetVisualizer();
    };
};  // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_CIRCULARLINKEDLIST_HPP