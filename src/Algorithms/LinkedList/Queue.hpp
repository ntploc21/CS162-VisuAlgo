#ifndef CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP
#define CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP

#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"

namespace Algorithm {
    class Queue
        : public Algorithm< GUIVisualizer::SinglyLinkedList, SLLAnimation > {
    public:
        static constexpr int maxN = 10;

    public:
        Queue(GUIComponent::CodeHighlighter::Ptr _codeHighlighter,
              SLLAnimationController::Ptr animController, FontHolder* fonts);
        Queue();
        ~Queue();
        std::size_t size() const;

    public:
        void EnqueueEmpty(int value);
        void Enqueue(int value);

    public:
        void Dequeue();

    public:
        void PeekFront();
        void PeekBack();

    private:
        std::function< GUIVisualizer::SinglyLinkedList(
            GUIVisualizer::SinglyLinkedList, float, Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);
    };
};      // namespace Algorithm

#endif  // CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP