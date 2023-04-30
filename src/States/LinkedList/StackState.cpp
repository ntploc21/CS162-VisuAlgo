#include "StackState.hpp"

#include <iostream>

#include "Global.hpp"

StackState::StackState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::Stack) {
    AddOperations();
    mStackAlgorithm =
        Algorithm::Stack(codeHighlighter, animController, context.fonts);
}

StackState::~StackState() {}

void StackState::Draw() {
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

void StackState::AddInsertOperation() {
    GUI::Button::Ptr buttonInsert(new GUI::Button("Push", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

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

void StackState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

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

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void StackState::AddDeleteOperation() {
    GUI::Button::Ptr buttonDelete(new GUI::Button("Pop", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Pop */

    AddNoFieldOperationOption(container, "Pop", [this]() {
        mStackAlgorithm.Pop();
        SetCurrentAction("Remove i = 0 (Head)");
        Success();
    });
    operationList.AddOperation(buttonDelete, container);
}

void StackState::AddSearchOperation() {
    GUI::Button::Ptr buttonSearch(new GUI::Button("Peek", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Peek (return top of the stack) */

    AddNoFieldOperationOption(container, "Peek", [this]() {
        mStackAlgorithm.Peek();
        SetCurrentAction("Peek top (head)");
        Success();
    });

    operationList.AddOperation(buttonSearch, container);
}