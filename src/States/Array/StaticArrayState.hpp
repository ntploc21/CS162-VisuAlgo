#ifndef STATES_ARRAY_STATICARRAYSTATE_HPP
#define STATES_ARRAY_STATICARRAYSTATE_HPP

#include "Algorithms/Array/StaticArray.hpp"
#include "ArrayState.hpp"

namespace State {
    class StaticArrayState : public ArrayState< DArrayAnimationController > {
    private:
        Algorithm::StaticArray mStaticArray;

    private:
        void AddInsertOperation();
        void AddInitializeOperation();
        void AddUpdateOperation();
        void AddDeleteOperation();
        void AddSearchOperation();
        void AddAccessOperation();

    public:
        StaticArrayState(StateStack& stack, Context context);
        ~StaticArrayState();
    };
};      // namespace State

#endif  // STATES_ARRAY_STATICARRAYSTATE_HPP