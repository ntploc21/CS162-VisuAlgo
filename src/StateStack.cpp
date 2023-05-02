#include "StateStack.hpp"

#include <cassert>
#include <iostream>

State::StateStack::StateStack(State::Context context)
    : mStack(), mPendingList(), mContext(context), mFactories() {}

void State::StateStack::Update(float dt) {
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++) {
        if (!(*it)->Update(dt)) break;
    }
    ApplyPendingChanges();
}

void State::StateStack::Draw() {
    auto it = mStack.rbegin();
    (*it)->Draw();
}

State::State::Ptr State::StateStack::createState(States::ID stateID) {
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second();
}

void State::StateStack::PushState(States::ID stateID) {
    mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void State::StateStack::PopState() {
    mPendingList.push_back(PendingChange(Action::Pop));
}

void State::StateStack::ClearStates() {
    mPendingList.push_back(PendingChange(Action::Clear));
}

void State::StateStack::ApplyPendingChanges() {
    for (PendingChange change : mPendingList) {
        switch (change.action) {
            case Action::Push:
                std::cerr << "Push state: " << change.stateID << std::endl;
                mStack.push_back(createState(change.stateID));
                break;
            case Action::Pop:
                std::cerr << "Pop state: " << change.stateID << std::endl;
                mStack.pop_back();
                break;
            case Action::Clear:
                std::cerr << "Clear state" << std::endl;
                mStack.clear();
                break;
        }
    }
    mPendingList.clear();
}

bool State::StateStack::IsEmpty() const { return mPendingList.empty(); }

State::StateStack::PendingChange::PendingChange(Action action,
                                                States::ID stateID)
    : action(action), stateID(stateID) {}

State::StateStack::PendingChange::PendingChange() {}
