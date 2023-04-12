#include "LLState.hpp"

#include <iostream>

#include "../../Global.hpp"

LLState::LLState(StateStack& stack, Context context,
                 DataStructures::ID activeDS)
    : State(stack, context), activeDS(activeDS) {
    InitNavigationBar();
    operationList = OperationList(context.fonts);
}

LLState::~LLState() {}

void LLState::InitNavigationBar() {
    navigation.SetVisableTitle(true);
    auto info = GetContext().categories->Get(Category::LinkedList);
    navigation.SetCategory(info.categoryName);
    navigation.SetActiveTitle(activeDS);
    for (auto dsID : info.mDS) {
        auto dsInfo = GetContext().dsInfo->Get(dsID);
        navigation.InsertTitle(dsID, dsInfo.stateID, dsInfo.abbr, dsInfo.name);
    };
}

void LLState::AddOperations() {
    AddInitializeOperation();
    AddInsertOperation();
    AddDeleteOperation();
    AddUpdateOperation();
    AddSearchOperation();

    operationList.SetPosition(
        0, global::SCREEN_HEIGHT - 60 - operationList.GetSize().y);
    operationList.InitActionBar();
}

void LLState::AddInitializeOperation() {}

void LLState::AddInsertOperation() {}

void LLState::AddDeleteOperation() {}

void LLState::AddUpdateOperation() {}

void LLState::AddSearchOperation() {}
