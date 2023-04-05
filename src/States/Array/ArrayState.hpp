#ifndef STATES_ARRAY_ARRAYSTATE_HPP
#define STATES_ARRAY_ARRAYSTATE_HPP

#include "../../State.hpp"

class ArrayState : public State {
private:
public:
    ArrayState(StateStack& stack, Context context, DataStructures::ID activeDS);
    ~ArrayState();
    virtual void Draw() = 0;
    virtual bool Update(float dt) = 0;

protected:
    void InitNavigationBar();
    Context mContext;

private:
    DataStructures::ID activeDS;
};

#endif  // STATES_ARRAY_ARRAYSTATE_HPP