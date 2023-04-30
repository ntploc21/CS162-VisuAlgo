#ifndef CORE_ALGORITHMS_ARRAY_DYNAMICARRAY_HPP
#define CORE_ALGORITHMS_ARRAY_DYNAMICARRAY_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/DynamicArray.hpp"

namespace Algorithm {
    class DynamicArray
        : public Algorithm< GUI::DynamicArray, DArrayAnimation > {
    public:
        static constexpr int maxN = 16;

    public:
        DynamicArray();
        DynamicArray(GUI::CodeHighlighter::Ptr codeHighlighter,
                     DArrayAnimationController::Ptr animController,
                     FontHolder* fonts);
        ~DynamicArray();
        std::size_t size() const;

    public:
        void PushBack(int value);

    public:
        void PopBack();

    public:
        void Update(int index, int value);

    public:
        void Access(int index);

    public:
        void Search(int value);

    private:
        void ResetVisualizer();
    };
};  // namespace Algorithm

#endif  // CORE_ALGORITHMS_ARRAY_DYNAMICARRAY_HPP