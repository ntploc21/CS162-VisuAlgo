#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include "FontHolder.hpp"
#include "StateIdentifiers.hpp"

class StateStack;

class State {
public:
    typedef std::unique_ptr< State > Ptr;
    struct Context {
        Context(FontHolder* fonts);
        FontHolder* fonts;
    };

public:
    State(StateStack& stack, Context context);
    virtual ~State();
    virtual void Draw() = 0;
    virtual bool Update(float dt) = 0;
    // virtual bool handleEvent(Event event) = 0;

protected:
    void RequestStackPush(States::ID stateID);
    void RequestStackPop();
    void RequestStackClear();
    Context GetContext() const;

private:
    StateStack* mStack;
    Context mContext;
};

#endif  // STATE_HPP