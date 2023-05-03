#ifndef STATES_ARRAY_DYNAMICARRAYSTATE_HPP
#define STATES_ARRAY_DYNAMICARRAYSTATE_HPP

#include "Algorithms/Array/DynamicArray.hpp"
#include "ArrayState.hpp"

namespace State {
    /**
     * @brief The state class that is used to represent the dynamic array
     * state/scene of the application.
     */
    class DynamicArrayState : public ArrayState< DArrayAnimationController > {
    private:
        /**
         * @brief The algorithm of the dynamic array.
         */
        Algorithm::DynamicArray mDynamicArray;

    private:
        /**
         * @brief Add an insert operation to the dynamic array algorithm.
         */
        void AddInsertOperation();

        /**
         * @brief Add an initialize operation to the dynamic array algorithm.
         */
        void AddInitializeOperation();

        /**
         * @brief Add an update operation to the dynamic array algorithm.
         */
        void AddUpdateOperation();

        /**
         * @brief Add a delete operation to the dynamic array algorithm.
         */
        void AddDeleteOperation();

        /**
         * @brief Add a search operation to the dynamic array algorithm.
         */
        void AddSearchOperation();

        /**
         * @brief Add an access operation to the dynamic array algorithm.
         */
        void AddAccessOperation();

    public:
        /**
         * @brief Construct a new DynamicArrayState object
         * @param stack The state stack where the dynamic array state is pushed
         * to.
         * @param context The context of the application.
         */
        DynamicArrayState(StateStack& stack, Context context);

        /**
         * @brief Destroy the DynamicArrayState object
         */
        ~DynamicArrayState();
    };
};      // namespace State

#endif  // STATES_ARRAY_DYNAMICARRAYSTATE_HPP