#include "DynamicArrayState.hpp"

#include <iostream>

#include "Global.hpp"

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
    DrawCurrentErrorText();
}

void DynamicArrayState::AddInsertOperation() {
    GUI::Button::Ptr buttonInsert(new GUI::Button("Push", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Insert head */
    AddIntFieldOperationOption(
        container, "Front", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (mDynamicArray.size() == mDynamicArray.maxN) {
                SetCurrentError("Array is full");
                return;
            }

            int v = std::stoi(input["v = "]);
            mDynamicArray.Push(0, v);
            SetCurrentAction("Push v = " + input["v = "] + " at front (i = 0)");
            Success();
        });

    /* Insert middle */
    AddIntFieldOperationOption(
        container, "Specify i in [1..N-1] and v =",
        {{"i = ", 50, 0, mDynamicArray.maxN}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (mDynamicArray.size() == mDynamicArray.maxN) {
                SetCurrentError("Array is full");
                return;
            }

            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);
            if (i <= 0 || i >= mDynamicArray.size()) {
                SetCurrentError("i must be in [1.." +
                                std::to_string(mDynamicArray.size() - 1) + "]");
                return;
            }

            mDynamicArray.Push(i, v);
            SetCurrentAction("Push v = " + input["v = "] +
                             " at i = " + input["i = "]);
            Success();
        });

    /* Insert tail */
    AddIntFieldOperationOption(
        container, "Back", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (mDynamicArray.size() == mDynamicArray.maxN) {
                SetCurrentError("Array is full");
                return;
            }

            int v = std::stoi(input["v = "]);
            mDynamicArray.PushBack(v);
            SetCurrentAction("Push v = " + input["v = "] + " at back (i = length)");
            Success();
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void DynamicArrayState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty", [this]() {
        mDynamicArray.Empty();
        ClearError();
    });

    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() {
        mDynamicArray.Random();
        ClearError();
    });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size",
        {{"length = ", 50, 0, mDynamicArray.maxN}},
        [this](std::map< std::string, std::string > input) {
            int length = std::stoi(input["length = "]);
            mDynamicArray.RandomFixedSize(length);
            ClearError();
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             try {
                                 mDynamicArray.UserDefined(input["arr = "]);
                                 ClearError();
                             } catch (std::exception& e) {
                                 SetCurrentError(e.what());
                             }
                         });

    /* Input from file */
    AddNoFieldOperationOption(container, "File", [this]() {
        try {
            std::string file = Utils::OpenFileDiaglog(
                "Select file with input", "Select your input file",
                {"*.txt", "*.inp"}, "", false);
            mDynamicArray.UserDefined(Utils::ReadInputFromFile(file));
            ClearError();
        } catch (std::exception& e) {
            SetCurrentError("No file is selected");
        }
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
            if (i >= mDynamicArray.size()) {
                SetCurrentError("You can't modify inaccessible element");
                return;
            }
            mDynamicArray.Update(i, v);
            SetCurrentAction("Update arr[" + input["i = "] +
                             "] = " + input["v = "]);
            Success();
        });

    operationList.AddOperation(buttonUpdate, container);
}

void DynamicArrayState::AddDeleteOperation() {
    GUI::Button::Ptr buttonDelete(new GUI::Button("Pop", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Delete front */
    AddNoFieldOperationOption(container, "Front (i = 0)", [this]() {
        mDynamicArray.Remove(0);
        SetCurrentAction("Remove i = 0 (Front)");
        Success();
    });

    /* Delete middle */
    AddIntFieldOperationOption(
        container, "Specify i in [1..N-1]",
        {{"i = ", 50, 0, mDynamicArray.maxN}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            if (i >= mDynamicArray.size() - 1) {
                SetCurrentError("Invalid index");
                return;
            }
            mDynamicArray.Remove(i);
            SetCurrentAction("Remove i = " + input["i = "]);
            Success();
        });

    /* Delete back */
    AddNoFieldOperationOption(container, "Back (i = length - 2)", [this]() {
        mDynamicArray.PopBack();
        SetCurrentAction("Remove i = length - 1 (Back)");
        Success();
    });

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
            Success();
        });

    operationList.AddOperation(buttonSearch, container);
}

void DynamicArrayState::AddAccessOperation() {
    GUI::Button::Ptr buttonSearch(
        new GUI::Button("Access", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR ACCESS ==== */

    AddIntFieldOperationOption(
        container, "Specify i", {{"i = ", 50, 0, mDynamicArray.maxN - 1}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            if (i >= mDynamicArray.size()) {
                SetCurrentError("You can't modify element out of range [0.." +
                                std::to_string(mDynamicArray.size() - 1) + "]");
                return;
            }
            mDynamicArray.Access(i);
            SetCurrentAction("Accessing arr[" + input["i = "] + "]");
            Success();
        });

    operationList.AddOperation(buttonSearch, container);
}
