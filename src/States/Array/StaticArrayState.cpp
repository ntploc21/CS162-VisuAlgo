#include "StaticArrayState.hpp"

#include <iostream>

#include "Global.hpp"
#include "Utils/Utils.hpp"

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
    DrawCurrentErrorText();
}

void StaticArrayState::AddInsertOperation() {
    GUI::Button::Ptr buttonInsert(new GUI::Button("Push", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Insert front */
    AddIntFieldOperationOption(
        container, "Front", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int v = std::stoi(input["v = "]);
            mStaticArray.Insert(0, v);
            SetCurrentAction("Insert v = " + input["v = "] +
                             " at front (i = 0)");
            Success();
        });

    /* Insert middle */
    AddIntFieldOperationOption(
        container, "Specify i in [1..N-1] and v =",
        {{"i = ", 50, 0, mStaticArray.maxN}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);
            if (i <= 0 || i >= mStaticArray.size()) {
                SetCurrentError("i must be in [1.." +
                                std::to_string(mStaticArray.size() - 1) + "]");
                return;
            }

            mStaticArray.Insert(i, v);
            SetCurrentAction("Push v = " + input["v = "] +
                             " at i = " + input["i = "]);
            Success();
        });

    /* Insert back */
    AddIntFieldOperationOption(
        container, "Back", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int v = std::stoi(input["v = "]);
            mStaticArray.Insert(mStaticArray.size() - 1, v);
            SetCurrentAction("Insert v = " + input["v = "] +
                             " at back (i = length - 1)");
            Success();
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void StaticArrayState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */
    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() {
        mStaticArray.Random();
        ClearError();
    });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, mStaticArray.maxN}},
        [this](std::map< std::string, std::string > input) {
            int N = std::stoi(input["N = "]);
            mStaticArray.RandomFixedSize(N);
            ClearError();
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             try {
                                 mStaticArray.UserDefined(input["arr = "]);
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
            mStaticArray.UserDefined(Utils::ReadInputFromFile(file));
            ClearError();
        } catch (std::exception& e) {
            SetCurrentError("No file is selected");
        }
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
        {{"i = ", 50, 0, mStaticArray.maxN - 1}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);
            if (i >= mStaticArray.size()) {
                SetCurrentError("You can't modify inaccessible element");
                return;
            }
            mStaticArray.Update(i, v);
            SetCurrentAction("Update arr[" + input["i = "] +
                             "] = " + input["v = "]);
            Success();
        });

    operationList.AddOperation(buttonUpdate, container);
}

void StaticArrayState::AddDeleteOperation() {
    GUI::Button::Ptr buttonDelete(new GUI::Button("Pop", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Delete front */
    AddNoFieldOperationOption(container, "Front (i = 0)", [this]() {
        mStaticArray.Delete(0);
        SetCurrentAction("Remove i = 0 (Front)");
        Success();
    });

    /* Delete middle */
    AddIntFieldOperationOption(
        container, "Specify i in [1..N-1]",
        {{"i = ", 50, 0, mStaticArray.maxN}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            if (i >= mStaticArray.size() - 1) {
                SetCurrentError("Invalid index");
                return;
            }
            mStaticArray.Delete(i);
            SetCurrentAction("Remove i = " + input["i = "]);
            Success();
        });

    /* Delete back */
    AddNoFieldOperationOption(container, "Back (i = length - 2)", [this]() {
        mStaticArray.Delete(mStaticArray.size() - 1);
        SetCurrentAction("Remove i = length - 1 (Back)");
        Success();
    });

    operationList.AddOperation(buttonDelete, container);
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
            Success();
        });

    operationList.AddOperation(buttonSearch, container);
}

void StaticArrayState::AddAccessOperation() {
    GUI::Button::Ptr buttonSearch(
        new GUI::Button("Access", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR ACCESS ==== */

    AddIntFieldOperationOption(
        container, "Specify i", {{"i = ", 50, 0, mStaticArray.maxN - 1}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            if (i >= mStaticArray.size()) {
                SetCurrentError("You can't access inaccessible element");
                return;
            }
            mStaticArray.Access(i);
            SetCurrentAction("Accessing arr[" + input["i = "] + "]");
            Success();
        });

    operationList.AddOperation(buttonSearch, container);
}
