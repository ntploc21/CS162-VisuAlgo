#ifndef CORE_ALGORITHMS_ARRAY_DYNAMICARRAY_HPP
#define CORE_ALGORITHMS_ARRAY_DYNAMICARRAY_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/DynamicArray.hpp"

namespace Algorithm {
    /**
     * @brief The algorithm class that is used to generate step-by-step
     * instructions for the visualization of the dynamic array.
     */
    class DynamicArray
        : public Algorithm< GUIVisualizer::DynamicArray, DArrayAnimation > {
    public:
        static constexpr int maxN = 16;

    public:
        /**
         * @brief The constructor of the dynamic array algorithm.
         */
        DynamicArray();

        /**
         * @brief The constructor of the dynamic array algorithm.
         * @param codeHighlighter The code highlighter of the dynamic array
         * algorithm.
         * @param animController The animation controller of the dynamic array
         * algorithm.
         * @param fonts The fonts of the dynamic array algorithm.
         */
        DynamicArray(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
                     DArrayAnimationController::Ptr animController,
                     FontHolder* fonts);

        /**
         * @brief The destructor of the dynamic array algorithm.
         * @note This destructor is not virtual because this class is not
         * designed to be inherited.
         */
        ~DynamicArray();

        /**
         * @brief Return the size of the dynamic array.
         * @return The size of the dynamic array.
         */
        std::size_t size() const;

    public:
        /**
         * @brief Push a new element to the dynamic array.
         * @param index The index of the new element.
         * @param value The value of the new element.
         * @note If the size of the dynamic array is equal to the capacity
         * (which there is not reserved space for new elements), the capacity of
         * the dynamic array will be doubled. We do this by initialize a new
         * dynamic array with the new capacity, and copy all the elements from
         * the old dynamic array to the new dynamic array.
         */
        void Push(int index, int value);

        /**
         * @brief Push a new element to the back of the dynamic array.
         * @param value The value of the new element.
         * @note If the size of the dynamic array is equal to the capacity
         * (which there is not reserved space for new elements), the capacity of
         * the dynamic array will be doubled. We do this by initialize a new
         * dynamic array with the new capacity, and copy all the elements from
         * the old dynamic array to the new dynamic array.
         */
        void PushBack(int value);

    public:
        /**
         * @brief Remove an element from the dynamic array.
         * @param index The index of the element to be removed.
         * @note This function will not change the capacity of the dynamic array
         * even if the size of the dynamic array is much smaller than the half
         * of the capacity.
         */
        void Remove(int index);

        /**
         * @brief Remove an element from the back of the dynamic array.
         * @note This function will not change the capacity of the dynamic array
         * even if the size of the dynamic array is much smaller than the half
         * of the capacity.
         */
        void PopBack();

    public:
        /**
         * @brief Update the value of an element in the dynamic array.
         * @param index The index of the element to be updated.
         * @param value The new value of the element.
         */
        void Update(int index, int value);

    public:
        /**
         * @brief Access an element in the dynamic array.
         * @param index The index of the element to be accessed.
         */
        void Access(int index);

    public:
        /**
         * @brief Search for an element in the dynamic array.
         * @param value The value of the element to be searched.
         */
        void Search(int value);

    private:
        /**
         * @brief Reset the visualizer of the dynamic array.
         * @note This function is used to reset all of the effects that are only
         * used to visualize the algorithm (i.e highlight the elements that are
         * currently iterated).
         */
        void ResetVisualizer();
    };
};      // namespace Algorithm

#endif  // CORE_ALGORITHMS_ARRAY_DYNAMICARRAY_HPP