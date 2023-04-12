#include "SLLState.hpp"

#include <iostream>

SLLState::SLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::SinglyLinkedList) {
    AddOperations();
}

SLLState::~SLLState() {}

void SLLState::Draw() {
    operationContainer.Draw();
    navigation.Draw();
}

bool SLLState::Update(float dt) { return true; }

void SLLState::AddInsertOperation() {
    Button::Ptr buttonInsert(new Button("Insert", GetContext().fonts));
    GUI::Container::Ptr container = GUI::Container::Ptr();
    operationContainer.AddOperation(buttonInsert, container);
}

void SLLState::AddInitializeOperation() {
    Button::Ptr buttonInitialize(new Button("Create", GetContext().fonts));
    GUI::Container::Ptr container = GUI::Container::Ptr();
    operationContainer.AddOperation(buttonInitialize, container);
}

void SLLState::AddUpdateOperation() {
    Button::Ptr buttonUpdate(new Button("Update", GetContext().fonts));
    GUI::Container::Ptr container = GUI::Container::Ptr();
    operationContainer.AddOperation(buttonUpdate, container);
}

void SLLState::AddDeleteOperation() {
    Button::Ptr buttonDelete(new Button("Delete", GetContext().fonts));
    GUI::Container::Ptr container = GUI::Container::Ptr();
    operationContainer.AddOperation(buttonDelete, container);
}

void SLLState::AddSearchOperation() {
    Button::Ptr buttonSearch(new Button("Search", GetContext().fonts));
    GUI::Container::Ptr container = GUI::Container::Ptr();
    operationContainer.AddOperation(buttonSearch, container);
}

// void SLLState::AddOperations() {
//     // operationContainer.SetPosition(0, 400);
//     // Button::Ptr buttonAdd(new Button("Add", GetContext().fonts));

//     // Button::Ptr buttonUpdate(new Button("Update", GetContext().fonts));
//     // Button::Ptr buttonDelete(new Button("Delete", GetContext().fonts));

//     // buttonAdd.get()->SetButtonColor(GREEN);
//     // buttonAdd.get()->SetTextColor(WHITE);
//     // buttonUpdate.get()->SetButtonColor(GREEN);
//     // buttonUpdate.get()->SetTextColor(WHITE);
//     // buttonDelete.get()->SetButtonColor(GREEN);
//     // buttonDelete.get()->SetTextColor(WHITE);
//     // GUI::Container::Ptr container;
//     // operationContainer.AddOperation(buttonAdd, container);
//     // operationContainer.AddOperation(buttonUpdate, container);
//     // operationContainer.AddOperation(buttonDelete, container);
//     // operationContainer.InitActionBar();
// }