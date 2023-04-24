#include "DynamicArrayState.hpp"

#include <iostream>

#include "../../Global.hpp"

DynamicArrayState::DynamicArrayState(StateStack& stack, Context context)
    : ArrayState(stack, context, DataStructures::DynamicArray) {
    mDynamicArray =
        Algorithm::DynamicArray(codeHighlighter, animController, context.fonts);

    AddOperations();
}

DynamicArrayState::~DynamicArrayState() {}

void DynamicArrayState::Draw() {
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

void DynamicArrayState::AddInsertOperation() {
    GUI::Button::Ptr buttonInsert(new GUI::Button("Push", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Insert head */
    // AddIntFieldOperationOption(
    //     container, "i = 0 (Head), specify v =", {{"v = ", 50, 0, 99}},
    //     [this](std::map< std::string, std::string > input) {
    //         std::cout << "i = 0 (Head), specify v =" << std::endl;
    //         for (auto it : input) {
    //             std::cout << it.first << it.second << std::endl;
    //         }
    //     });

    /* Insert tail */
    AddIntFieldOperationOption(
        container, "Back", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int v = std::stoi(input["v = "]);
            mDynamicArray.PushBack(v);
            SetCurrentAction("Push v = " + input["v = "] +
                             " at back (i = length - 1)");
        });

    /* Default insert */

    // AddIntFieldOperationOption(
    //     container, "Specify both i in [0..N] and v",
    //     {{"i = ", 50, 0, 9}, {"v = ", 50, 0, 99}},
    //     [this](std::map< std::string, std::string > input) {
    //         std::cout << "Specify both i in [0..N] and v parameters: "
    //                   << std::endl;
    //         for (auto it : input) {
    //             std::cout << it.first << it.second << std::endl;
    //         }
    //     });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void DynamicArrayState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty",
                              [this]() { mDynamicArray.Empty(); });

    /* Random */

    AddNoFieldOperationOption(container, "Random",
                              [this]() { mDynamicArray.Random(); });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"length = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            int length = std::stoi(input["length = "]);
            mDynamicArray.RandomFixedSize(length);
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             mDynamicArray.UserDefined(input["arr = "]);
                         });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void DynamicArrayState::AddUpdateOperation() {
    GUI::Button::Ptr buttonUpdate(
        new GUI::Button("Update", GetContext().fonts));
    /*  */

    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR UPDATE ==== */

    AddIntFieldOperationOption(
        container, "Specify i in [0..N-1] and v",
        {{"i = ", 50, 0, mDynamicArray.maxN}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);
            mDynamicArray.Update(i, v);
            SetCurrentAction("Update arr[" + input["i = "] +
                             "] = " + input["v = "]);
        });

    operationList.AddOperation(buttonUpdate, container);
}

void DynamicArrayState::AddDeleteOperation() {
    GUI::Button::Ptr buttonDelete(new GUI::Button("Pop", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Delete head */

    /* Delete tail */
    AddNoFieldOperationOption(container, "Back (i = length - 1)", [this]() {
        mDynamicArray.PopBack();
        SetCurrentAction("Remove i = length - 1 (Back)");
    });

    /* Delete specific element */

    // AddIntFieldOperationOption(
    //     container, "Specify i in [1..N-1]", {{"i = ", 50, 0, 9}},
    //     [this](std::map< std::string, std::string > input) {
    //         std::cout << "Specify i in [1..N-1]" << std::endl;
    //         for (auto it : input) {
    //             std::cout << it.first << it.second << std::endl;
    //         }
    //     });
    /* Delete elements with specific value */

    // AddIntFieldOperationOption(
    //     container, "Specify v", {{"v = ", 50, 0, 99}},
    //     [this](std::map< std::string, std::string > input) {
    //         std::cout << "Specify v" << std::endl;
    //         for (auto it : input) {
    //             std::cout << it.first << it.second << std::endl;
    //         }
    //     });
    operationList.AddOperation(buttonDelete, container);
}

void DynamicArrayState::AddSearchOperation() {
    GUI::Button::Ptr buttonSearch(
        new GUI::Button("Search", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Search for the first element that has value of v */

    AddIntFieldOperationOption(
        container, "Specify v", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int v = std::stoi(input["v = "]);
            mDynamicArray.Search(v);
            SetCurrentAction("Search for element has value equal to " +
                             input["v = "]);
        });

    operationList.AddOperation(buttonSearch, container);
}