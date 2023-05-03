#ifndef STATES_ARRAY_STATICARRAYSTATE_HPP
#define STATES_ARRAY_STATICARRAYSTATE_HPP

#include "Algorithms/Array/StaticArray.hpp"
#include "ArrayState.hpp"

namespace State {
    /**
     * @brief The state class that is used to represent the static array
     * state/scene of the application.
     * @note This Static Array state is using the Dynamic Array Animation
     * Controller as it can be visualized using the same animation controller
     * (by hiding all the inaccessible element/reserved element in dynamic
     * array).
     */
    class StaticArrayState : public ArrayState< DArrayAnimationController > {
    private:
        /**
         * @brief The algorithm of the static array.
         */
        Algorithm::StaticArray mStaticArray;

    private:
        /**
         * @brief Add an insert operation to the static array algorithm.
         */
        void AddInsertOperation();

        /**
         * @brief Add an initialize operation to the static array algorithm.
         */
        void AddInitializeOperation();

        /**
         * @brief Add an update operation to the static array algorithm.
         */
        void AddUpdateOperation();

        /**
         * @brief Add a delete operation to the static array algorithm.
         */
        void AddDeleteOperation();

        /**
         * @brief Add a search operation to the static array algorithm.
         */
        void AddSearchOperation();

        /**
         * @brief Add an access operation to the static array algorithm.
         */
        void AddAccessOperation();

    public:
        /**
         * @brief Construct a new StaticArrayState object
         * @param stack The state stack where the static array state is pushed
         * to.
         * @param context The context of the application.
         */
        StaticArrayState(StateStack& stack, Context context);

        /**
         * @brief Destroy the StaticArrayState object
         */
        ~StaticArrayState();
    };
};      // namespace State

#endif  // STATES_ARRAY_STATICARRAYSTATE_HPP