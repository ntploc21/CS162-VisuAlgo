#include "State.hpp"

#include "StateStack.hpp"

State::State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context) {
    InitNavigationBar();
}

State::State::~State() {}

void State::State::RequestStackPush(States::ID stateID) {
    mStack->PushState(stateID);
}

void State::State::RequestStackPop() { mStack->PopState(); }

void State::State::RequestStackClear() { mStack->ClearStates(); }

State::State::Context State::State::GetContext() const { return mContext; }

void State::State::InitNavigationBar() {
    navigation = GUIComponent::NavigationBar(GetContext().fonts);
    navigation.SetDirectLink(
        [this](States::ID stateID) { RequestStackPush(stateID); });
    navigation.SetHomepageID(States::Homepage);
}

State::State::Context::Context() {}

State::State::Context::Context(FontHolder* fonts, TextureHolder* textures,
                               CategoryInfo* categories, DSInfo* dsInfo)
    : fonts(fonts), textures(textures), categories(categories), dsInfo(dsInfo) {
}
