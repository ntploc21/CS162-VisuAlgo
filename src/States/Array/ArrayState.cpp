#include "ArrayState.hpp"

ArrayState::ArrayState(StateStack& stack, Context context)
    : State(stack, context) {
    InitNavigationBar();
}

ArrayState::~ArrayState() {}

void ArrayState::InitNavigationBar() {
    auto info = GetContext().categories->Get(Category::LinkedList);
    navigation.SetCategory(info.categoryName);
}
