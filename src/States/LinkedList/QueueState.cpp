#include "QueueState.hpp"

#include <iostream>

#include "../../Global.hpp"

QueueState::QueueState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Queue) {
    AddOperations();
}

QueueState::~QueueState() {}

void QueueState::Draw() {
    DrawRectangle(0, global::SCREEN_HEIGHT - 40, global::SCREEN_WIDTH, 40,
                  BLACK);
    DrawRectangle(0, 0, 40, global::SCREEN_HEIGHT, BLACK);

    DrawRectangle(global::SCREEN_WIDTH - 40, 0, 40, global::SCREEN_HEIGHT,
                  BLACK);

    operationList.Draw();
    navigation.Draw();
}

bool QueueState::Update(float dt) { return true; }

void QueueState::AddInsertOperation() {
    Button::Ptr buttonInsert(new Button("Enqueue", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Enqueue */
    AddIntFieldOperationOption(
        container, "Enqueue v = … to the front of the queue",
        {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Enqueue v = … to the front of the queue" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void QueueState::AddInitializeOperation() {
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

void QueueState::AddDeleteOperation() {
    Button::Ptr buttonDelete(new Button("Dequeue", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Dequeue */

    AddNoFieldOperationOption(container, "Dequeue the front", [this]() {
        std::cout << "Dequeue the front" << std::endl;
    });
    operationList.AddOperation(buttonDelete, container);
}

void QueueState::AddSearchOperation() {
    Button::Ptr buttonSearch(new Button("Peek", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Peek */

    AddNoFieldOperationOption(container, "Peek front", [this]() {
        std::cout << "Peek front" << std::endl;
    });

    operationList.AddOperation(buttonSearch, container);
}