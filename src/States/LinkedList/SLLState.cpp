#include "SLLState.hpp"

#include <iostream>

#include "Components/Visualization/Node.hpp"
#include "Global.hpp"

SLLState::SLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::SinglyLinkedList) {
    AddOperations();
    SLL = Algorithm::SinglyLinkedList(codeHighlighter, animController,
                                      context.fonts);
}

SLLState::~SLLState() {}

void SLLState::Draw() {
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

void SLLState::AddInsertOperation() {
    GUI::Button::Ptr buttonInsert(
        new GUI::Button("Insert", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    /* Insert head */
    AddIntFieldOperationOption(
        container, "i = 0 (Head), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            SLL.InsertHead(std::stoi(input["v = "]));
            operationList.ToggleOperations();
            SetCurrentAction("Insert " + input["v = "] + " at head");
        });

    /* Insert tail */
    AddIntFieldOperationOption(
        container, "i = N (After Tail), specify v =", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "i = N (After Tail), specify v =" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    /* Default insert */

    AddIntFieldOperationOption(
        container, "Specify both i in [0..N] and v",
        {{"i = ", 50, 0, 9}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Specify both i in [0..N] and v parameters: "
                      << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void SLLState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    /* Empty */
    AddNoFieldOperationOption(container, "Empty", [this]() { SLL.Empty(); });

    /* Random */

    AddNoFieldOperationOption(container, "Random", [this]() { SLL.Random(); });

    /* Random Sorted */
    // AddNoFieldOperationOption(container, "Random Sorted", [this]() {
    //     std::cout << "Random Sorted" << std::endl;
    // });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"N = ", 50, 0, SLL.maxN}},
        [this](std::map< std::string, std::string > input) {
            assert(input.size() == 1);
            assert(input.begin()->first == "N = ");

            SLL.RandomFixedSize(std::stoi(input.begin()->second));
        });

    /* User defined */
    AddStringFieldOption(container, "--- User defined list ---", "arr = ",
                         [this](std::map< std::string, std::string > input) {
                             assert(input.size() == 1);
                             assert(input.begin()->first == "arr = ");
                             SLL.UserDefined(input.begin()->second);
                         });

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void SLLState::AddUpdateOperation() {
    GUI::Button::Ptr buttonUpdate(
        new GUI::Button("Update", GetContext().fonts));
    /*  */

    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR UPDATE ==== */

    AddIntFieldOperationOption(
        container, "Specify i in [0..N-1] and v",
        {{"i = ", 50, 0, 9}, {"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Specify i in [0..N-1] and v parameters: "
                      << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    operationList.AddOperation(buttonUpdate, container);
}

void SLLState::AddDeleteOperation() {
    GUI::Button::Ptr buttonDelete(
        new GUI::Button("Delete", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    /* Delete head */

    AddNoFieldOperationOption(container, "i = 0 (Head)", [this]() {
        std::cout << "i = 0 (Head)" << std::endl;
    });

    /* Delete tail */
    AddNoFieldOperationOption(container, "i = N-1 (Tail)", [this]() {
        std::cout << "i = N-1 (Tail)" << std::endl;
    });

    /* Delete specific element */

    AddIntFieldOperationOption(
        container, "Specify i in [1..N-1]", {{"i = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Specify i in [1..N-1]" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });
    /* Delete elements with specific value */

    AddIntFieldOperationOption(
        container, "Specify v", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Specify v" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });
    operationList.AddOperation(buttonDelete, container);
}

void SLLState::AddSearchOperation() {
    GUI::Button::Ptr buttonSearch(
        new GUI::Button("Search", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    /* Search for the first element that has value of v */

    AddIntFieldOperationOption(
        container, "Specify v", {{"v = ", 50, 0, 99}},
        [this](std::map< std::string, std::string > input) {
            SLL.Search(std::stoi(input["v = "]));
            operationList.ToggleOperations();
            SetCurrentAction("Search " + input["v = "]);
        });
    operationList.AddOperation(buttonSearch, container);
}