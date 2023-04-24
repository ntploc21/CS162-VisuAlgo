#include "StaticArrayState.hpp"

#include <iostream>

#include "../../Global.hpp"

StaticArrayState::StaticArrayState(StateStack& stack, Context context)
    : ArrayState(stack, context, DataStructures::StaticArray) {
    AddOperations();

    mStaticArray =
        Algorithm::StaticArray(codeHighlighter, animController, context.fonts);
}

StaticArrayState::~StaticArrayState() {}

void StaticArrayState::Draw() {
    DrawRectangle(0, 0, 40, global::SCREEN_HEIGHT, BLACK);

    DrawRectangle(global::SCREEN_WIDTH - 40, 0, 40, global::SCREEN_HEIGHT,
                  BLACK);

    animController->GetAnimation().Draw();
    operationList.Draw();
    navigation.Draw();
    codeHighlighter->Draw();
    footer.Draw(animController.get());
    DrawCurrentActionText();
}

void StaticArrayState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */
    /* Random */

    AddNoFieldOperationOption(container, "Random",
                              [this]() { mStaticArray.Random(); });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            int N = std::stoi(input["N = "]);
            mStaticArray.RandomFixedSize(N);
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             mStaticArray.UserDefined(input["arr = "]);
                         });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void StaticArrayState::AddUpdateOperation() {
    GUI::Button::Ptr buttonUpdate(
        new GUI::Button("Update", GetContext().fonts));
    /*  */

    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR UPDATE ==== */

    AddIntFieldOperationOption(
        container, "Specify i in [0..N-1] and v",
        {{"i = ", 50, 0, 9}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);
            if (!(i >= 0 && i < mStaticArray.maxN)) return;
            mStaticArray.Update(i, v);
            SetCurrentAction("Update arr[" + input["i = "] +
                             "] = " + input["v = "]);
        });

    operationList.AddOperation(buttonUpdate, container);
}

void StaticArrayState::AddSearchOperation() {
    GUI::Button::Ptr buttonSearch(
        new GUI::Button("Search", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Search for the first element that has value of v */

    AddIntFieldOperationOption(
        container, "Specify v", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int v = std::stoi(input["v = "]);
            mStaticArray.Search(v);
            SetCurrentAction("Search for element has value equal to " +
                             input["v = "]);
        });

    operationList.AddOperation(buttonSearch, container);
}