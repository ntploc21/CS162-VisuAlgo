#include "State.hpp"

#include "StateStack.hpp"

State::State(StateStack& stack, Context context)
    : mStack(&stack), mContext(context) {
    InitNavigationBar();
}

State::~State() {}

void State::RequestStackPush(States::ID stateID) { mStack->PushState(stateID); }

void State::RequestStackPop() { mStack->PopState(); }

void State::RequestStackClear() { mStack->ClearStates(); }

State::Context State::GetContext() const { return mContext; }

void State::InitNavigationBar() {
    navigation = NavigationBar(GetContext().fonts);
    navigation.SetHomepageLink(
        [this]() { RequestStackPush(States::Homepage); });
    navigation.SetSettings([this]() { RequestStackPush(States::Settings); });
}

State::Context::Context() {}

State::Context::Context(FontHolder* fonts, TextureHolder* textures,
                        CategoryInfo* categories, DSInfo* dsInfo)
    : fonts(fonts), textures(textures), categories(categories), dsInfo(dsInfo) {
}
