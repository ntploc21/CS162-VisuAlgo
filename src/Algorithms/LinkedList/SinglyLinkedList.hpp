#ifndef CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"

namespace Algorithm {
    class SinglyLinkedList
        : public Algorithm< GUIVisualizer::SinglyLinkedList, SLLAnimation > {
    public:
        static constexpr int maxN = 10;

    public:
        SinglyLinkedList();
        SinglyLinkedList(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
                         SLLAnimationController::Ptr animController,
                         FontHolder* fonts);
        ~SinglyLinkedList();
        std::size_t size() const;

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
        std::function< GUIVisualizer::SinglyLinkedList(
            GUIVisualizer::SinglyLinkedList, float, Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);

    private:
        void ResetVisualizer();
    };
};      // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP