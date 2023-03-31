#ifndef STATES_ARRAY_DYNAMICARRAYSTATE_HPP
#define STATES_ARRAY_DYNAMICARRAYSTATE_HPP

#include "../../State.hpp"

class DynamicArrayState : public State {
private:
public:
    DynamicArrayState(StateStack& stack, Context context);
    ~DynamicArrayState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_ARRAY_DYNAMICARRAYSTATE_HPP