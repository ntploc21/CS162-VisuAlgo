#ifndef CORE_DATASTRUCTURES_LINKEDLIST_DOUBLYLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_DOUBLYLINKEDLIST_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/DoublyLinkedList.hpp"

namespace Algorithm {
    class DoublyLinkedList
        : public Algorithm< GUI::DoublyLinkedList, DLLAnimation > {
    public:
        static constexpr int maxN = 10;

    public:
        DoublyLinkedList();
        DoublyLinkedList(GUI::CodeHighlighter::Ptr codeHighlighter,
                         DLLAnimationController::Ptr animController,
                         FontHolder* fonts);
        ~DoublyLinkedList();

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
        std::function< GUI::DoublyLinkedList(GUI::DoublyLinkedList, float,
                                             Vector2) >
        HighlightArrowNext(int index, bool drawVisualizer = true,
                           bool reverse = false);

        std::function< GUI::DoublyLinkedList(GUI::DoublyLinkedList, float,
                                             Vector2) >
        HighlightArrowPrev(int index, bool drawVisualizer = true,
                           bool reverse = false);

        std::function< GUI::DoublyLinkedList(GUI::DoublyLinkedList, float,
                                             Vector2) >
        HighlightArrowBoth(int index, bool drawVisualizer = true,
                           bool reverse = false);

    private:
        void ResetVisualizer();
    };
};  // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_DOUBLYLINKEDLIST_HPP