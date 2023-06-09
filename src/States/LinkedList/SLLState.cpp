#include "SLLState.hpp"

#include "Components/Visualization/Node.hpp"

State::SLLState::SLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::SinglyLinkedList) {
    AddOperations();
    SLL = Algorithm::SinglyLinkedList(codeHighlighter, animController,
                                      context.fonts);
}

State::SLLState::~SLLState() {}

void State::SLLState::AddInsertOperation() {
    GUIComponent::Button::Ptr buttonInsert(
        new GUIComponent::Button("Insert", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Insert head */
    AddIntFieldOperationOption(
        container, "i = 0 (Head), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (SLL.size() == SLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            SLL.InsertHead(std::stoi(input["v = "]));
            Success();
            SetCurrentAction("Insert " + input["v = "] + " at head");
        });

    /* Insert tail */
    AddIntFieldOperationOption(
        container, "i = N (After Tail), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (SLL.size() == SLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            SLL.InsertAfterTail(std::stoi(input["v = "]));
            Success();
            SetCurrentAction("Insert " + input["v = "] + " at tail");
        });

    /* Default insert */

    AddIntFieldOperationOption(
        container, "Specify both i in [1..N-1] and v",
        {{"i = ", 50, 0, SLL.maxN - 1}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            if (SLL.size() == SLL.maxN) {
                SetCurrentError("List is full");
                return;
            }

            int i = std::stoi(input["i = "]);
            int v = std::stoi(input["v = "]);
            if (i <= 0 || i >= SLL.size()) {
                SetCurrentError("Invalid index");
                return;
            }

            SLL.InsertMiddle(i, v);
            Success();
            SetCurrentAction("Insert " + input["v = "] + " at index " +
                             input["i = "]);
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void State::SLLState::AddInitializeOperation() {
    GUIComponent::Button::Ptr buttonInitialize(
        new GUIComponent::Button("Create", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty", [this]() {
        SLL.Empty();
        ClearError();
    });

    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() {
        SLL.Random();
        ClearError();
    });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, SLL.maxN}},
        [this](std::map< std::string, std::string > input) {
            int N = std::stoi(input.begin()->second);
            SLL.RandomFixedSize(N);
            ClearError();
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             try {
                                 SLL.UserDefined(input.begin()->second);
                                 ClearError();
                             } catch (std::invalid_argument& e) {
                                 SetCurrentError("Invalid input");
                             }
                         });

    /* Input from file */
    AddNoFieldOperationOption(container, "File", [this]() {
        try {
            std::string file = Utils::OpenFileDiaglog(
                "Select file with input", "Select your input file",
                {"*.txt", "*.inp"}, "", false);
            SLL.UserDefined(Utils::ReadInputFromFile(file));
            ClearError();
        } catch (std::exception& e) {
            SetCurrentError("No file is selected");
        }
    });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void State::SLLState::AddUpdateOperation() {
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

            if (i >= SLL.size()) {
                SetCurrentError("Index out of bound");
                return;
            }
            SLL.Update(i, v);
            SetCurrentAction("Update node " + input["i = "] + "'s value to " +
                             input["v = "]);
            Success();
        });

    operationList.AddOperation(buttonUpdate, container);
}

void State::SLLState::AddDeleteOperation() {
    GUIComponent::Button::Ptr buttonDelete(
        new GUIComponent::Button("Delete", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Delete head */

    AddNoFieldOperationOption(container, "i = 0 (Head)", [this]() {
        SLL.DeleteHead();
        SetCurrentAction("Remove i = 0 (Head)");
        Success();
    });

    /* Delete tail */
    AddNoFieldOperationOption(container, "i = N-1 (Tail)", [this]() {
        SLL.DeleteTail();
        SetCurrentAction("Remove i = N-1 (Tail)");
        Success();
    });

    /* Delete specific element */

    AddIntFieldOperationOption(
        container, "Specify i in [1..N-2]", {{"i = ", 50, 0, SLL.maxN}},
        [this](std::map< std::string, std::string > input) {
            if (SLL.size() == 0) {
                SetCurrentError("List is empty");
                return;
            }

            int i = std::stoi(input["i = "]);
            if (i < 1 || i >= SLL.size() - 1) {
                SetCurrentError("Invalid index");
                return;
            }
            SLL.DeleteMiddle(i);
            SetCurrentAction("Remove i = " + input["i = "]);
            Success();
        });

    operationList.AddOperation(buttonDelete, container);
}

void State::SLLState::AddSearchOperation() {
    GUIComponent::Button::Ptr buttonSearch(
        new GUIComponent::Button("Search", GetContext().fonts));
    GUIComponent::OperationContainer::Ptr container(
        new GUIComponent::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Search for the first element that has value of v */

    AddIntFieldOperationOption(
        container, "Specify v", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            SLL.Search(std::stoi(input["v = "]));
            operationList.ToggleOperations();
            SetCurrentAction("Search " + input["v = "]);
            Success();
        });
    operationList.AddOperation(buttonSearch, container);
}