#ifndef STATES_ARRAY_DYNAMICARRAYSTATE_HPP
#define STATES_ARRAY_DYNAMICARRAYSTATE_HPP

#include "ArrayState.hpp"

class DynamicArrayState : public ArrayState< SLLAnimationController > {
private:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddUpdateOperation();
    void AddDeleteOperation();
    void AddSearchOperation();

public:
    DynamicArrayState(StateStack& stack, Context context);
    ~DynamicArrayState();
    void Draw();
};

#endif  // STATES_ARRAY_DYNAMICARRAYSTATE_HPP