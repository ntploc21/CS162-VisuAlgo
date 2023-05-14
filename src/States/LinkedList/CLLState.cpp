#include "CLLState.hpp"

#include "Global.hpp"

State::CLLState::CLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::CircularLinkedList) {
    CLL = Algorithm::CircularLinkedList(codeHighlighter, animController,
                                        context.fonts);
    AddOperations();
}

State::CLLState::~CLLState() {}

void State::CLLState::AddInsertOperation() {
    GUIComponent::Button::Ptr buttonInsert(
        new GUIComponent::Button("Insert", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Insert head */
    AddIntFieldOperationOption(
        container, "i = 0 (Head), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (CLL.size() == CLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            CLL.InsertHead(std::stoi(input["v = "]));
            SetCurrentAction("Insert " + input["v = "] + " at head");
            Success();
        });

    /* Insert tail */
    AddIntFieldOperationOption(
        container, "i = N (After Tail), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (CLL.size() == CLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            CLL.InsertAfterTail(std::stoi(input["v = "]));
            SetCurrentAction("Insert " + input["v = "] + " at tail");
            Success();
        });

    /* Default insert */

    AddIntFieldOperationOption(
        container, "Specify both i in [1..N-1] and v",
        {{"i = ", 50, 0, 9}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (CLL.size() == CLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            int i = std::stoi(input["i = "]);
            if (i <= 0 || i >= CLL.size()) {
                SetCurrentError("Invalid index");
                return;
            }

            CLL.InsertMiddle(i, std::stoi(input["v = "]));
            SetCurrentAction("Insert " + input["v = "] + " at index " +
                             input["i = "]);
            Success();
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void State::CLLState::AddInitializeOperation() {
    GUIComponent::Button::Ptr buttonInitialize(
        new GUIComponent::Button("Create", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty", [this]() {
        CLL.Empty();
        ClearError();
    });

    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() {
        CLL.Random();
        ClearError();
    });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, CLL.maxN}},
        [this](std::map< std::string, std::string > input) {
            try {
                CLL.RandomFixedSize(std::stoi(input.begin()->second));
                ClearError();
            } catch (std::invalid_argument) {
                SetCurrentError("Invalid input");
            }
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             try {
                                 CLL.UserDefined(input.begin()->second);
                                 ClearError();
                             } catch (std::invalid_argument) {
                                 SetCurrentError("Invalid input");
                             }
                         });

    /* Input from file */
    AddNoFieldOperationOption(container, "File", [this]() {
        try {
            std::string file = Utils::OpenFileDiaglog(
                "Select file with input", "Select your input file",
                {"*.txt", "*.inp"}, "", false);
            CLL.UserDefined(Utils::ReadInputFromFile(file));
            ClearError();
        } catch (std::exception& e) {
            SetCurrentError("No file is selected");
        }
    });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void State::CLLState::AddUpdateOperation() {
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

            if (i >= CLL.size()) {
                SetCurrentError("Invalid index");
                return;
            }

            CLL.Update(i, v);
            SetCurrentAction("Update node " + input["i = "] + "'s value to " +
                             input["v = "]);
            Success();
        });

    operationList.AddOperation(buttonUpdate, container);
}

void State::CLLState::AddDeleteOperation() {
    GUIComponent::Button::Ptr buttonDelete(
        new GUIComponent::Button("Delete", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Delete head */

    AddNoFieldOperationOption(container, "i = 0 (Head)", [this]() {
        CLL.DeleteHead();
        SetCurrentAction("Remove i = 0 (Head)");
        Success();
    });

    /* Delete tail */
    AddNoFieldOperationOption(container, "i = N-1 (Tail)", [this]() {
        CLL.DeleteTail();
        SetCurrentAction("Remove i = N-1 (Tail)");
        Success();
    });

    /* Delete specific element */

    AddIntFieldOperationOption(
        container, "Specify i in [1..N-1]", {{"i = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            if (CLL.size() == 0) {
                SetCurrentError("List is empty");
                return;
            }

            int i = std::stoi(input["i = "]);
            if (i < 1 || i >= CLL.size()) {
                SetCurrentError("Invalid index");
                return;
            }
            CLL.DeleteMiddle(i);
            SetCurrentAction("Remove i = " + input["i = "]);
        });

    operationList.AddOperation(buttonDelete, container);
}

void State::CLLState::AddSearchOperation() {
    GUIComponent::Button::Ptr buttonSearch(
        new GUIComponent::Button("Search", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Search for the first element that has value of v */

    AddIntFieldOperationOption(
        container, "Specify v", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            CLL.Search(std::stoi(input["v = "]));
            operationList.ToggleOperations();
            SetCurrentAction("Search " + input["v = "]);
            Success();
        });

    operationList.AddOperation(buttonSearch, container);
}