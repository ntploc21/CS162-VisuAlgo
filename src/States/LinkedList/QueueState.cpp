#include "QueueState.hpp"

#include "Global.hpp"

State::QueueState::QueueState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Queue) {
    AddOperations();
    queue = Algorithm::Queue(codeHighlighter, animController, context.fonts);
}

State::QueueState::~QueueState() {}

void State::QueueState::AddInsertOperation() {
    GUIComponent::Button::Ptr buttonInsert(
        new GUIComponent::Button("Enqueue", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

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

void State::QueueState::AddInitializeOperation() {
    GUIComponent::Button::Ptr buttonInitialize(
        new GUIComponent::Button("Create", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

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

void State::QueueState::AddDeleteOperation() {
    GUIComponent::Button::Ptr buttonDelete(
        new GUIComponent::Button("Dequeue", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Dequeue */

    AddNoFieldOperationOption(container, "Dequeue the front", [this]() {
        queue.Dequeue();
        SetCurrentAction("Remove i = 0 (Head)");
        Success();
    });
    operationList.AddOperation(buttonDelete, container);
}

void State::QueueState::AddSearchOperation() {
    GUIComponent::Button::Ptr buttonSearch(
        new GUIComponent::Button("Peek", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

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