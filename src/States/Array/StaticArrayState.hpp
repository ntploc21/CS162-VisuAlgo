#ifndef STATES_ARRAY_STATICARRAYSTATE_HPP
#define STATES_ARRAY_STATICARRAYSTATE_HPP

#include "ArrayState.hpp"

class StaticArrayState : public ArrayState< SLLAnimationController > {
private:
    void AddInitializeOperation();
    void AddUpdateOperation();
    void AddSearchOperation();

public:
    StaticArrayState(StateStack& stack, Context context);
    ~StaticArrayState();
    void Draw();
};

#endif  // STATES_ARRAY_STATICARRAYSTATE_HPP