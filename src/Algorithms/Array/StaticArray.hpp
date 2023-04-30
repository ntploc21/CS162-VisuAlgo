#ifndef CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP
#define CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/DynamicArray.hpp"

namespace Algorithm {
    class StaticArray : public Algorithm< GUI::DynamicArray, DArrayAnimation > {
    public:
        static constexpr int maxN = 16;

    public:
        StaticArray();
        StaticArray(GUI::CodeHighlighter::Ptr codeHighlighter,
                    DArrayAnimationController::Ptr animController,
                    FontHolder* fonts);
        ~StaticArray();
        std::size_t size() const;

    public:
        void Update(int index, int value);

    public:
        void Access(int index);

    public:
        void Search(int value);

    private:
        void ApplyInput(std::vector< int > input, std::size_t nMaxSize);

    private:
        void ResetVisualizer();
    };
};  // namespace Algorithm

#endif  // CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP