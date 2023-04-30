#ifndef STATES_ARRAY_STATICARRAYSTATE_HPP
#define STATES_ARRAY_STATICARRAYSTATE_HPP

#include "Algorithms/Array/StaticArray.hpp"
#include "ArrayState.hpp"
class StaticArrayState : public ArrayState< DArrayAnimationController > {
private:
    Algorithm::StaticArray mStaticArray;

private:
    void AddInitializeOperation();
    void AddUpdateOperation();
    void AddSearchOperation();
    void AddAccessOperation();

public:
    StaticArrayState(StateStack& stack, Context context);
    ~StaticArrayState();
    void Draw();
};

#endif  // STATES_ARRAY_STATICARRAYSTATE_HPP