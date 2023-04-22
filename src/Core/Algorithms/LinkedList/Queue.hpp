#ifndef CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP
#define CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP

#include "Components/Visualization/SinglyLinkedList.hpp"
#include "Core/Algorithms/Algorithm.hpp"

namespace Algorithm {
    class Queue : public Algorithm< GUI::SinglyLinkedList, SLLAnimation > {
    public:
        static constexpr int maxN = 10;

    public:
        Queue(GUI::CodeHighlighter::Ptr _codeHighlighter,
              SLLAnimationController::Ptr animController, FontHolder* fonts);
        Queue();
        ~Queue();

    public:
        void EnqueueEmpty(int value);
        void Enqueue(int value);

    public:
        void Dequeue();

    public:
        void PeekFront();
        void PeekBack();

    private:
        std::function< GUI::SinglyLinkedList(GUI::SinglyLinkedList, float,
                                             Vector2) >
        HighlightArrowFromCur(int index, bool drawVisualizer = true,
                              bool reverse = false);
    };
};  // namespace Algorithm

#endif  // CORE_ALGORITHMS_LINKEDLIST_QUEUE_HPP