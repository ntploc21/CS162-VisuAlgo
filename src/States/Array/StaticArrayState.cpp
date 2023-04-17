#include "StaticArrayState.hpp"

#include <iostream>

#include "../../Global.hpp"

StaticArrayState::StaticArrayState(StateStack& stack, Context context)
    : ArrayState(stack, context, DataStructures::StaticArray) {
    AddOperations();
}

StaticArrayState::~StaticArrayState() {}

void StaticArrayState::Draw() {
    DrawRectangle(0, global::SCREEN_HEIGHT - 40, global::SCREEN_WIDTH, 40,
                  BLACK);
    DrawRectangle(0, 0, 40, global::SCREEN_HEIGHT, BLACK);

    DrawRectangle(global::SCREEN_WIDTH - 40, 0, 40, global::SCREEN_HEIGHT,
                  BLACK);

    operationList.Draw();
    navigation.Draw();
    codeHighlighter.Draw();
}

bool StaticArrayState::Update(float dt) { return true; }

void StaticArrayState::AddInitializeOperation() {
    GUI::Button::Ptr buttonInitialize(
        new GUI::Button("Create", GetContext().fonts));
    GUI::OperationContainer::Ptr container(new GUI::OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */
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
            std::cout << "Specify i in [0..N-1] and v parameters: "
                      << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
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
            std::cout << "Specify v" << std::endl;
            for (auto it : input) {
                std::cout << it.first << it.second << std::endl;
            }
        });

    operationList.AddOperation(buttonSearch, container);
}