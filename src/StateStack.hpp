#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "Core/Deque.hpp"
#include "NonCopyable.hpp"
#include "State.hpp"

namespace State {
    class StateStack : private NonCopyable< StateStack > {
    public:
        enum class Action {
            Push,
            Pop,
            Clear,
        };

    public:
        explicit StateStack(State::Context context);

        template< class T >
        void RegisterState(States::ID stateID);
        void Update(float dt);
        void Draw();
        // void handleEvent(Event event);
        void PushState(States::ID stateID);
        void PopState();
        void ClearStates();
        bool IsEmpty() const;

    private:
        State::Ptr createState(States::ID stateID);
        void ApplyPendingChanges();

    private:
        struct PendingChange {
            explicit PendingChange(Action action,
                                   States::ID stateID = States::None);
            PendingChange();
            Action action;
            States::ID stateID;
        };

    private:
        std::vector< State::Ptr > mStack;
        // Core::Deque< State::Ptr > mStack;
        // std::vector< PendingChange > mPendingList;
        Core::Deque< PendingChange > mPendingList;

        State::Context mContext;
        std::map< States::ID, std::function< State::Ptr() > > mFactories;
    };
};  // namespace State

template< class T >
void State::StateStack::RegisterState(States::ID stateID) {
    mFactories[stateID] = [this]() {
        return State::Ptr(new T(*this, mContext));
    };
}

#endif  // STATESTACK_HPP