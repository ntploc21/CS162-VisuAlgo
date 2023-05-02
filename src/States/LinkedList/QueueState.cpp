#include "QueueState.hpp"

#include <iostream>

#include "Global.hpp"

QueueState::QueueState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Queue) {
    AddOperations();
    queue = Algorithm::Queue(codeHighlighter, animController, context.fonts);
}

QueueState::~QueueState() {}

void QueueState::AddInsertOperation() {
    GUI::Button::Ptr buttonInsert(
        new GUI::Button("Enqueue", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Enqueue */
    AddIntFieldOperationOption(
        container, "Enqueue v = … to the front of the queue",
        {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (queue.size() == queue.maxN) {
                SetCurrentError("Queue is full");
                return;
            }
            int value = std::stoi(input["v = "]);
            queue.Enqueue(value);
            SetCurrentAction("Enqueue " + input["v = "] + " at back (tail)");
            Success();
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void QueueState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty", [this]() {
        queue.Empty();
        ClearError();
    });

    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() {
        queue.Random();
        ClearError();
    });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, queue.maxN}},
        [this](std::map< std::string, std::string > input) {
            int N = std::stoi(input.begin()->second);

            queue.RandomFixedSize(N);
            ClearError();
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             try {
                                 queue.UserDefined(input.begin()->second);
                                 ClearError();
                             } catch (const std::invalid_argument& e) {
                                 SetCurrentError("Invalid input");
                             }
                         });

    /* Input from file */
    AddNoFieldOperationOption(container, "File", [this]() {
        try {
            std::string file = Utils::OpenFileDiaglog(
                "Select file with input", "Select your input file",
                {"*.txt", "*.inp"}, "", false);
            queue.UserDefined(Utils::ReadInputFromFile(file));
            ClearError();
        } catch (std::exception& e) {
            SetCurrentError("No file is selected");
        }
    });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void QueueState::AddDeleteOperation() {
    GUI::Button::Ptr buttonDelete(
        new GUI::Button("Dequeue", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Dequeue */

    AddNoFieldOperationOption(container, "Dequeue the front", [this]() {
        queue.Dequeue();
        SetCurrentAction("Remove i = 0 (Head)");
        Success();
    });
    operationList.AddOperation(buttonDelete, container);
}

void QueueState::AddSearchOperation() {
    GUI::Button::Ptr buttonSearch(new GUI::Button("Peek", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Peek */

    AddNoFieldOperationOption(container, "Front", [this]() {
        queue.PeekFront();
        SetCurrentAction("Peek front (head)");
        Success();
    });

    AddNoFieldOperationOption(container, "Back", [this]() {
        queue.PeekBack();
        SetCurrentAction("Peek back (tail)");
        Success();
    });

    operationList.AddOperation(buttonSearch, container);
}