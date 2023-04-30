#include "QueueState.hpp"

#include <iostream>

#include "Global.hpp"

QueueState::QueueState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Queue) {
    AddOperations();
    queue = Algorithm::Queue(codeHighlighter, animController, context.fonts);
}

QueueState::~QueueState() {}

void QueueState::Draw() {
    DrawRectangle(0, 0, 40, global::SCREEN_HEIGHT, BLACK);

    DrawRectangle(global::SCREEN_WIDTH - 40, 0, 40, global::SCREEN_HEIGHT,
                  BLACK);

    operationList.Draw();
    navigation.Draw();

    animController->GetAnimation().Draw();
    codeHighlighter->Draw();
    footer.Draw(animController.get());
    DrawCurrentActionText();
}

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
            int value = std::stoi(input["v = "]);
            queue.Enqueue(value);
            SetCurrentAction("Enqueue " + input["v = "] + " at back (tail)");
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
    AddNoFieldOperationOption(container, "Empty", [this]() { queue.Empty(); });

    /* Random */

    AddNoFieldOperationOption(container, "Random",
                              [this]() { queue.Random(); });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, queue.maxN}},
        [this](std::map< std::string, std::string > input) {
            assert(input.size() == 1);
            assert(input.begin()->first == "N = ");

            queue.RandomFixedSize(std::stoi(input.begin()->second));
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             assert(input.size() == 1);
                             assert(input.begin()->first == "arr = ");
                             queue.UserDefined(input.begin()->second);
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
    });

    AddNoFieldOperationOption(container, "Back", [this]() {
        queue.PeekBack();
        SetCurrentAction("Peek back (tail)");
    });

    operationList.AddOperation(buttonSearch, container);
}