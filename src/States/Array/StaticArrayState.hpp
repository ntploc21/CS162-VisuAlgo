#ifndef STATES_ARRAY_STATICARRAYSTATE_HPP
#define STATES_ARRAY_STATICARRAYSTATE_HPP

#include "ArrayState.hpp"

class StaticArrayState : public ArrayState {
private:
public:
    StaticArrayState(StateStack& stack, Context context);
    ~StaticArrayState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_ARRAY_STATICARRAYSTATE_HPP