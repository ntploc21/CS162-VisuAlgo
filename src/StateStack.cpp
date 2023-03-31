#include "StateStack.hpp"

#include <cassert>
#include <iostream>

StateStack::StateStack(State::Context context)
    : mStack(), mPendingList(), mContext(context), mFactories() {}

void StateStack::Update(float dt) {
    for (auto it = mStack.rbegin(); it != mStack.rend(); it++) {
        if (!(*it)->Update(dt)) break;
    }
    ApplyPendingChanges();
}

void StateStack::Draw() {
    auto it = mStack.rbegin();
    (*it)->Draw();
}

State::Ptr StateStack::createState(States::ID stateID) {
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());
    return found->second();
}

void StateStack::PushState(States::ID stateID) {
    mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::PopState() {
    mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::ClearStates() {
    mPendingList.push_back(PendingChange(Action::Clear));
}

void StateStack::ApplyPendingChanges() {
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

bool StateStack::IsEmpty() const { return mPendingList.empty(); }

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action), stateID(stateID) {}