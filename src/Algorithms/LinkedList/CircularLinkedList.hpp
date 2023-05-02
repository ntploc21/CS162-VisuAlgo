#ifndef CORE_DATASTRUCTURES_LINKEDLIST_CIRCULARLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_CIRCULARLINKEDLIST_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/CircularLinkedList.hpp"

namespace Algorithm {
    class CircularLinkedList
        : public Algorithm< GUIVisualizer::CircularLinkedList, CLLAnimation > {
    public:
        static constexpr int maxN = 10;

    public:
        CircularLinkedList();
        CircularLinkedList(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
                           CLLAnimationController::Ptr animController,
                           FontHolder* fonts);
        ~CircularLinkedList();
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
        std::function< GUIVisualizer::CircularLinkedList(
            GUIVisualizer::CircularLinkedList, float, Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);
        std::function< GUIVisualizer::CircularLinkedList(
            GUIVisualizer::CircularLinkedList, float, Vector2) >
        HighlightCircularArrow(bool drawVisualizer = true,
                               bool reverse = false);

    private:
        void ResetVisualizer();
    };
};      // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_CIRCULARLINKEDLIST_HPP