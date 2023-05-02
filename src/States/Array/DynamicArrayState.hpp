#ifndef STATES_ARRAY_DYNAMICARRAYSTATE_HPP
#define STATES_ARRAY_DYNAMICARRAYSTATE_HPP

#include "Algorithms/Array/DynamicArray.hpp"
#include "ArrayState.hpp"

class DynamicArrayState : public ArrayState< DArrayAnimationController > {
private:
    Algorithm::DynamicArray mDynamicArray;

private:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddUpdateOperation();
    void AddDeleteOperation();
    void AddSearchOperation();
    void AddAccessOperation();

public:
    DynamicArrayState(StateStack& stack, Context context);
    ~DynamicArrayState();
};

#endif  // STATES_ARRAY_DYNAMICARRAYSTATE_HPP