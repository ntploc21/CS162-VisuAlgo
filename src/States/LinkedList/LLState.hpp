#ifndef STATES_LINKEDLIST_LLSTATE_HPP
#define STATES_LINKEDLIST_LLSTATE_HPP

#include "../../State.hpp"

class LLState : public State {
private:
public:
    LLState(StateStack& stack, Context context);
    ~LLState();
    virtual void Draw() = 0;
    virtual bool Update(float dt) = 0;

protected:
    void InitNavigationBar();
    Context mContext;
};

#endif  // STATES_LINKEDLIST_LLSTATE_HPP