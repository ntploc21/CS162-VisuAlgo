#include "SLLState.hpp"

#include <iostream>

#include "Components/Visualization/Node.hpp"
#include "Global.hpp"

SLLState::SLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::SinglyLinkedList) {
    AddOperations();
    // codeHighlighter.AddCode({"if(head == nullptr) return; // empty, do
    // nothing",
    //                          "Node *pre = head;", "for(int k=0;k<i-1;k++)",
    //                          "	pre = pre->next;",
    //                          "Node *del = pre->next, *aft = del->next;",
    //                          "pre->next = aft; // bypass del", "delete
    //                          del;"});
    // codeHighlighter.AddCode(
    //     {"if(head == nullptr) return nullptr; // empty, NOT_FOUND",
    //      "if(head == tail && head->value == v) return head;",
    //      "Node *cur = head;", "for(;cur->next != head; cur =
    //      cur->next)", "	if(cur->value == v) return cur;",
    //      "return nullptr; // NOT_FOUND"});

    // codeHighlighter.Highlight(3);
    // codeHighlighter.AddActionDescription(
    //     "The index before insertion point is found.\npre is before the "
    //     "insertion point and aft is the insertion point.");
}

SLLState::~SLLState() {}

void SLLState::Draw() {
    DrawRectangle(0, global::SCREEN_HEIGHT - 40, global::SCREEN_WIDTH, 40,
                  BLACK);
    DrawRectangle(0, 0, 40, global::SCREEN_HEIGHT, BLACK);

    DrawRectangle(global::SCREEN_WIDTH - 40, 0, 40, global::SCREEN_HEIGHT,
                  BLACK);

    operationList.Draw();
    navigation.Draw();

    // GUI::Node guiNode = GUI::Node(10, GetContext().fonts);
    // guiNode.SetLabel("head");
    // guiNode.SetPosition(300, 300);

    // guiNode.Draw();
    codeHighlighter.Draw();
}

bool SLLState::Update(float dt) {
    // std::cout << "update: " << dt << std::endl;
    return true;
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
            std::cout << "i = 0 (Head), specify v =" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
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
    AddNoFieldOperationOption(container, "Empty",
                              [this]() { std::cout << "Empty" << std::endl; });

    /* Random */

    AddNoFieldOperationOption(container, "Random",
                              [this]() { std::cout << "Random" << std::endl; });

    /* Random Sorted */
    AddNoFieldOperationOption(container, "Random Sorted", [this]() {
        std::cout << "Random Sorted" << std::endl;
    });

    /* Random Fixed Size */
    AddIntFieldOperationOption(
        container, "Random Fixed Size", {{"i = ", 50, 0, 9}},
        [this](std::map< std::string, std::string > input) {
            std::cout << "Random Fixed Size parameters:" << std::endl;

            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    /* User defined */
    AddStringFieldOption(
        container, "--- User defined list ---",
        "arr = ", [this](std::map< std::string, std::string > input) {
            std::cout << "--- User defined list --- parameters:" << std::endl;

            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
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
            std::cout << "Specify v" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    operationList.AddOperation(buttonSearch, container);
}