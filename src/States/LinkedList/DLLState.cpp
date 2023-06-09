#include "DLLState.hpp"

#include "Global.hpp"

State::DLLState::DLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::DoublyLinkedList) {
    mDLL = Algorithm::DoublyLinkedList(codeHighlighter, animController,
                                       context.fonts);
    AddOperations();
}

State::DLLState::~DLLState() {}

void State::DLLState::AddInsertOperation() {
    GUIComponent::Button::Ptr buttonInsert(
        new GUIComponent::Button("Insert", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Insert head */
    AddIntFieldOperationOption(
        container, "i = 0 (Head), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (mDLL.size() == mDLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            int v = std::stoi(input["v = "]);
            mDLL.InsertHead(v);
            SetCurrentAction("Insert " + input["v = "] + " at head");
            Success();
        });

    /* Insert tail */
    AddIntFieldOperationOption(
        container, "i = N (After Tail), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (mDLL.size() == mDLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            int v = std::stoi(input["v = "]);
            mDLL.InsertAfterTail(v);
            SetCurrentAction("Insert " + input["v = "] + " at tail");
            Success();
        });

    /* Default insert */

    AddIntFieldOperationOption(
        container, "Specify both i in [1..N-1] and v",
        {{"i = ", 50, 0, 9}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (mDLL.size() == mDLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);
            if (i <= 0 || i >= mDLL.size()) {
                SetCurrentError("Invalid index");
                return;
            }

            mDLL.InsertMiddle(i, v);
            SetCurrentAction("Insert " + input["v = "] + " at index " +
                             input["i = "]);
            Success();
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void State::DLLState::AddInitializeOperation() {
    GUIComponent::Button::Ptr buttonInitialize(
        new GUIComponent::Button("Create", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty", [this]() {
        mDLL.Empty();
        ClearError();
    });

    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() {
        mDLL.Random();
        ClearError();
    });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            int N = std::stoi(input["N = "]);
            mDLL.RandomFixedSize(N);
            ClearError();
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             try {
                                 mDLL.UserDefined(input["arr = "]);
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
            mDLL.UserDefined(Utils::ReadInputFromFile(file));
            ClearError();
        } catch (std::exception& e) {
            SetCurrentError("No file is selected");
        }
    });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void State::DLLState::AddUpdateOperation() {
    GUIComponent::Button::Ptr buttonUpdate(
        new GUIComponent::Button("Update", GetContext().fonts));
    /*  */

    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR UPDATE ==== */

    AddIntFieldOperationOption(
        container, "Specify i in [0..N-1] and v",
        {{"i = ", 50, 0, 9}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);

            if (i >= mDLL.size()) {
                SetCurrentError("Index out of bound");
                return;
            }

            mDLL.Update(i, v);
            SetCurrentAction("Update node " + input["i = "] + "'s value to " +
                             input["v = "]);
            Success();
        });

    operationList.AddOperation(buttonUpdate, container);
}

void State::DLLState::AddDeleteOperation() {
    GUIComponent::Button::Ptr buttonDelete(
        new GUIComponent::Button("Delete", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Delete head */

    AddNoFieldOperationOption(container, "i = 0 (Head)", [this]() {
        mDLL.DeleteHead();
        SetCurrentAction("Remove i = 0 (Head)");
        Success();
    });

    /* Delete tail */
    AddNoFieldOperationOption(container, "i = N-1 (Tail)", [this]() {
        mDLL.DeleteTail();
        SetCurrentAction("Remove i = N - 1 (Tail)");
        Success();
    });

    /* Delete specific element */

    AddIntFieldOperationOption(
        container, "Specify i in [1..N-1]", {{"i = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            int i = std::stoi(input["i = "]);
            if (i < 1 || i >= mDLL.size()) {
                SetCurrentError("Index out of bound");
                return;
            }

            mDLL.DeleteMiddle(i);
            SetCurrentAction("Remove index " + input["i = "]);
            Success();
        });
    operationList.AddOperation(buttonDelete, container);
}

void State::DLLState::AddSearchOperation() {
    GUIComponent::Button::Ptr buttonSearch(
        new GUIComponent::Button("Search", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Search for the first element that has value of v */

    AddIntFieldOperationOption(
        container, "Specify v", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            int v = std::stoi(input["v = "]);
            mDLL.Search(v);
            SetCurrentAction("Search " + input["v = "]);
            Success();
        });

    operationList.AddOperation(buttonSearch, container);
}