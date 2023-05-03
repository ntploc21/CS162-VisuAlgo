#ifndef CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP
#define CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP

#include <string>

// #include "BaseNode.hpp"
#include "Algorithms/Algorithm.hpp"
#include "Components/Visualization/DynamicArray.hpp"

namespace Algorithm {
    /**
     * @brief The algorithm class that is used to generate step-by-step
     * instructions for the visualization of the static array.
     * @note In this Static Array algorithm class, the visualizer I use for the
     * static array is a dynamic array with a fixed size (and hide all the
     * inaccesible elements). This is because the visualzation of the static
     * array and the dynamic array have a lot in common.
     */
    class StaticArray
        : public Algorithm< GUIVisualizer::DynamicArray, DArrayAnimation > {
    public:
        /**
         * @brief The maximum size of the static array.
         */
        static constexpr int maxN = 16;

    public:
        /**
         * @brief The constructor of the static array algorithm.
         */
        StaticArray();

        /**
         * @brief The constructor of the static array algorithm.
         * @param codeHighlighter The code highlighter of the static array
         * algorithm.
         * @param animController The animation controller of the static array
         * algorithm.
         * @param fonts The fonts of the static array algorithm.
         */
        StaticArray(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
                    DArrayAnimationController::Ptr animController,
                    FontHolder* fonts);

        /**
         * @brief The destructor of the static array algorithm.
         * @note This destructor is not virtual because this class is not
         * designed to be inherited.
         */
        ~StaticArray();

        /**
         * @brief Return the size of the static array.
         * @return The size of the static array.
         */
        std::size_t size() const;

    public:
        /**
         * @brief Push a new element to the static array.
         * @param value The value of the new element.
         * @note The new element can only be pushed to the static
         * array if the static array is not full (which I will check if the last
         * element's value is 0).
         */
        void Insert(int index, int value);

    public:
        /**
         * @brief Erase an element with the given index from the static array.
         * @param index The index of the element to be erased.
         * @note The actual erasing process is done by setting the value of the
         * element to 0, and then shifting all the elements after it to the
         * left.
         */
        void Delete(int index);

    public:
        /**
         * @brief Update the value of an element with the given index.
         * @param index The index of the element to be updated.
         * @param value The new value of the element.
         */
        void Update(int index, int value);

    public:
        /**
         * @brief Access an element with the given index.
         * @param index The index of the element to be accessed.
         */
        void Access(int index);

    public:
        /**
         * @brief Search for an element with the given value.
         * @param value The value of the element to be searched.
         */
        void Search(int value);

    private:
        /**
         * @brief Apply an input to the static array.
         * @note As the Static Array algorithm use a dynamic array as its
         * visualizer, I need to hide all the elements that are not accessible
         * when it is initialized.
         */
        void ApplyInput(std::vector< int > input, std::size_t nMaxSize);

    private:
        /**
         * @brief Reset the visualizer of the static array.
         * @note This function is used to reset all of the effects that are only
         * used to visualize the algorithm (i.e highlight the elements that are
         * currently iterated).
         */
        void ResetVisualizer();
    };
};      // namespace Algorithm

#endif  // CORE_ALGORITHMS_ARRAY_STATICARRAY_HPP