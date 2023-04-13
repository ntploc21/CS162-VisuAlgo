#include "StackState.hpp"

#include <iostream>

#include "../../Global.hpp"

StackState::StackState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Stack) {
    AddOperations();
}

StackState::~StackState() {}

void StackState::Draw() {
    DrawRectangle(0, global::SCREEN_HEIGHT - 40, global::SCREEN_WIDTH, 40,
                  BLACK);
    DrawRectangle(0, 0, 40, global::SCREEN_HEIGHT, BLACK);

    DrawRectangle(global::SCREEN_WIDTH - 40, 0, 40, global::SCREEN_HEIGHT,
                  BLACK);

    operationList.Draw();
    navigation.Draw();
}

bool StackState::Update(float dt) { return true; }

void StackState::AddInsertOperation() {
    Button::Ptr buttonInsert(new Button("Push", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Push */
    AddIntFieldOperationOption(
        container, "Push v = … to the top of the stack", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Push v = … to the top of the stack" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void StackState::AddInitializeOperation() {
    Button::Ptr buttonInitialize(new Button("Create", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty",
                              [this]() { std::cout << "Empty" << std::endl; });

    /* Random */

    AddNoFieldOperationOption(container, "Random",
                              [this]() { std::cout << "Random" << std::endl; });

    /* Random Sorted */
    AddNoFieldOperationOption(container, "Random Sorted", [this]() {
        std::cout << "Random Sorted" << std::endl;
    });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"i = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Random Fixed Size parameters:" << std::endl;

            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    /* User defined */
    AddStringFieldOption(
        container, "--- User defined list ---",
        "arr = ", [this](std::map< std::string, std::string > input) {
            std::cout << "--- User defined list --- parameters:" << std::endl;

            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void StackState::AddDeleteOperation() {
    Button::Ptr buttonDelete(new Button("Pop", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Pop */

    AddNoFieldOperationOption(container, "Pop",
                              [this]() { std::cout << "Pop" << std::endl; });
    operationList.AddOperation(buttonDelete, container);
}

void StackState::AddSearchOperation() {
    Button::Ptr buttonSearch(new Button("Peek", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Peek (return top of the stack) */

    AddNoFieldOperationOption(container, "Peek",
                              [this]() { std::cout << "Peek" << std::endl; });

    operationList.AddOperation(buttonSearch, container);
}