#include "ArrayState.hpp"

ArrayState::ArrayState(StateStack& stack, Context context,
                       DataStructures::ID activeDS)
    : State(stack, context), activeDS(activeDS) {
    InitNavigationBar();
}

ArrayState::~ArrayState() {}

void ArrayState::InitNavigationBar() {
    navigation.SetVisableTitle(true);
    auto info = GetContext().categories->Get(Category::Array);
    navigation.SetCategory(info.categoryName);
    navigation.SetActiveTitle(activeDS);
    for (auto dsID : info.mDS) {
        auto dsInfo = GetContext().dsInfo->Get(dsID);
        navigation.InsertTitle(dsID, dsInfo.stateID, dsInfo.abbr, dsInfo.name);
    };
}
