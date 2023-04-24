#ifndef CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP
#define CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"
#include "Core/Algorithms/Algorithm.hpp"

using ArrowType = GUI::SinglyLinkedList::ArrowType;

namespace Algorithm {
    class StaticArray
        : public Algorithm< GUI::SinglyLinkedList, SLLAnimation > {
    public:
        static constexpr int maxN = 10;
        static constexpr ArrowType defaultArrowType = ArrowType::Hidden;
        static constexpr GUI::Node::Shape defaultShape =
            GUI::Node::Shape::Square;

    public:
        StaticArray();
        StaticArray(GUI::CodeHighlighter::Ptr codeHighlighter,
                    SLLAnimationController::Ptr animController,
                    FontHolder* fonts);
        ~StaticArray();

    public:
        void Update(int index, int value);

    public:
        void Search(int value);

    private:
        void ResetVisualizer();
    };
};  // namespace Algorithm

#endif  // CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP