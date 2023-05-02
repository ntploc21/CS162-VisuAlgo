#include "StackState.hpp"

#include <iostream>

State::StackState::StackState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Stack) {
    AddOperations();
    mStackAlgorithm =
        Algorithm::Stack(codeHighlighter, animController, context.fonts);
}

State::StackState::~StackState() {}

void State::StackState::AddInsertOperation() {
    GUIComponent::Button::Ptr buttonInsert(
        new GUIComponent::Button("Push", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Push */
    AddIntFieldOperationOption(
        container, "Push v = … to the top of the stack", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (mStackAlgorithm.size() == mStackAlgorithm.maxN) {
                SetCurrentError("Stack is full");
                return;
            }

            int v = std::stoi(input["v = "]);
            mStackAlgorithm.Push(v);
            SetCurrentAction("Push v = " + input["v = "] + " at top (head)");
            Success();
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void State::StackState::AddInitializeOperation() {
    GUIComponent::Button::Ptr buttonInitialize(
        new GUIComponent::Button("Create", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty", [this]() {
        mStackAlgorithm.Empty();
        ClearError();
    });

    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() {
        mStackAlgorithm.Random();
        ClearError();
    });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            int N = std::stoi(input["N = "]);
            mStackAlgorithm.RandomFixedSize(N);
            ClearError();
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             try {
                                 mStackAlgorithm.UserDefined(input["arr = "]);
                                 ClearError();
                             } catch (const std::exception& e) {
                                 SetCurrentError(e.what());
                             }
                         });

    /* Input from file */
    AddNoFieldOperationOption(container, "File", [this]() {
        try {
            std::string file = Utils::OpenFileDiaglog(
                "Select file with input", "Select your input file",
                {"*.txt", "*.inp"}, "", false);
            mStackAlgorithm.UserDefined(Utils::ReadInputFromFile(file));
            ClearError();
        } catch (std::exception& e) {
            SetCurrentError("No file is selected");
        }
    });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void State::StackState::AddDeleteOperation() {
    GUIComponent::Button::Ptr buttonDelete(
        new GUIComponent::Button("Pop", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Pop */

    AddNoFieldOperationOption(container, "Pop", [this]() {
        mStackAlgorithm.Pop();
        SetCurrentAction("Remove i = 0 (Head)");
        Success();
    });
    operationList.AddOperation(buttonDelete, container);
}

void State::StackState::AddSearchOperation() {
    GUIComponent::Button::Ptr buttonSearch(
        new GUIComponent::Button("Peek", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Peek (return top of the stack) */

    AddNoFieldOperationOption(container, "Peek", [this]() {
        mStackAlgorithm.Peek();
        SetCurrentAction("Peek top (head)");
        Success();
    });

    operationList.AddOperation(buttonSearch, container);
}