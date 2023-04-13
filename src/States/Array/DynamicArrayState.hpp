#ifndef STATES_ARRAY_DYNAMICARRAYSTATE_HPP
#define STATES_ARRAY_DYNAMICARRAYSTATE_HPP

#include "ArrayState.hpp"

class DynamicArrayState : public ArrayState {
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
    bool Update(float dt);
};

#endif  // STATES_ARRAY_DYNAMICARRAYSTATE_HPP