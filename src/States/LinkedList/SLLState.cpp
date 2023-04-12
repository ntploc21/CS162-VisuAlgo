#include "SLLState.hpp"

#include <iostream>

#include "../../Global.hpp"

SLLState::SLLState(StateStack& stack, Context context)
    : LLState(stack, context, DataStructures::SinglyLinkedList) {
    AddOperations();
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
}

bool SLLState::Update(float dt) { return true; }

void SLLState::AddInsertOperation() {
    Button::Ptr buttonInsert(new Button("Insert", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR INSERT ==== */

    auto genButton = [&, this](std::string content,
                               std::function< void() > action) -> Button::Ptr {
        Button::Ptr button(new Button(content, GetContext().fonts));

        button.get()->SetFontSize(20);
        button.get()->EnableFitContent();
        button.get()->SetAction(action);
        button.get()->SetButtonColor((Color){82, 188, 105, 255});

        return button;
    };

    /* Insert head */
    Button::Ptr buttonInsertHead(
        genButton("i = 0 (Head), specify v =", [this]() {

        }));

    container.get()->AddOperation(buttonInsertHead);

    /* Insert tail */
    Button::Ptr buttonInsertAfterTail(
        genButton("i = N (After Tail), specify v =", [this]() {

        }));

    container.get()->AddOperation(buttonInsertAfterTail);

    /* Default insert */
    Button::Ptr buttonDefaultInsert(
        genButton("Specify both i in [1..N-1] and value", [this]() {

        }));

    container.get()->AddOperation(buttonDefaultInsert);

    /* ====================================== */
    operationList.AddOperation(buttonInsert, container);
}

void SLLState::AddInitializeOperation() {
    Button::Ptr buttonInitialize(new Button("Create", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR CREATE ==== */

    auto genButton = [&, this](std::string content,
                               std::function< void() > action) -> Button::Ptr {
        Button::Ptr button(new Button(content, GetContext().fonts));

        button.get()->SetFontSize(20);
        button.get()->EnableFitContent();
        button.get()->SetAction(action);
        button.get()->SetButtonColor((Color){82, 188, 105, 255});

        return button;
    };

    /* Empty */
    Button::Ptr buttonEmpty(genButton("Empty", [this]() {

    }));

    container.get()->AddOperation(buttonEmpty);

    /* Random */
    Button::Ptr buttonRandom(genButton("Random", [this]() {

    }));

    container.get()->AddOperation(buttonRandom);

    /* Random Sorted */
    Button::Ptr buttonRandomSorted(genButton("Random Sorted", [this]() {

    }));

    container.get()->AddOperation(buttonRandomSorted);

    /* Random Fixed Size */
    Button::Ptr buttonRandomFixedSize(genButton("Random Fixed Size", [this]() {

    }));

    container.get()->AddOperation(buttonRandomFixedSize);

    /* User defined */
    Button::Ptr buttonUserDefined(
        genButton("--- User defined list ---", [this]() {

        }));

    container.get()->AddOperation(buttonUserDefined);

    /* ====================================== */
    operationList.AddOperation(buttonInitialize, container);
}

void SLLState::AddUpdateOperation() {
    Button::Ptr buttonUpdate(new Button("Update", GetContext().fonts));
    /*  */

    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR UPDATE ==== */

    auto genButton = [&, this](std::string content,
                               std::function< void() > action) -> Button::Ptr {
        Button::Ptr button(new Button(content, GetContext().fonts));

        button.get()->SetFontSize(20);
        button.get()->EnableFitContent();
        button.get()->SetAction(action);
        button.get()->SetButtonColor((Color){82, 188, 105, 255});

        return button;
    };

    /* Delete head */
    Button::Ptr buttonUpdateOption(
        genButton("Specify i in [0..N-1] and v", [this]() {

        }));

    container.get()->AddOperation(buttonUpdateOption);

    operationList.AddOperation(buttonUpdate, container);
}

void SLLState::AddDeleteOperation() {
    Button::Ptr buttonDelete(new Button("Delete", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR DELETE ==== */

    auto genButton = [&, this](std::string content,
                               std::function< void() > action) -> Button::Ptr {
        Button::Ptr button(new Button(content, GetContext().fonts));

        button.get()->SetFontSize(20);
        button.get()->EnableFitContent();
        button.get()->SetAction(action);
        button.get()->SetButtonColor((Color){82, 188, 105, 255});

        return button;
    };

    /* Delete head */
    Button::Ptr buttonDeleteHead(genButton("i = 0 (Head)", [this]() {

    }));

    container.get()->AddOperation(buttonDeleteHead);

    /* Delete tail */
    Button::Ptr buttonDeleteTail(genButton("i = N-1 (Tail)", [this]() {

    }));

    container.get()->AddOperation(buttonDeleteTail);

    /* Delete specific element */
    Button::Ptr buttonDefaultDelete(
        genButton("Specify i in [1..N-1]", [this]() {

        }));

    /* Delete elements with specific value */
    Button::Ptr buttonDeleteMultiple(genButton("Specify v", [this]() {

    }));

    container.get()->AddOperation(buttonDeleteMultiple);
    operationList.AddOperation(buttonDelete, container);
}

void SLLState::AddSearchOperation() {
    Button::Ptr buttonSearch(new Button("Search", GetContext().fonts));
    OperationContainer::Ptr container(new OperationContainer());

    /* ==== DEFINE OPERATIONS FOR SEARCH ==== */

    auto genButton = [&, this](std::string content,
                               std::function< void() > action) -> Button::Ptr {
        Button::Ptr button(new Button(content, GetContext().fonts));

        button.get()->SetFontSize(20);
        button.get()->EnableFitContent();
        button.get()->SetAction(action);
        button.get()->SetButtonColor((Color){82, 188, 105, 255});

        return button;
    };

    /* Search for the first element that has value of v */
    Button::Ptr buttonSearchFirstElement(genButton("Specify v =", [this]() {

    }));

    container.get()->AddOperation(buttonSearchFirstElement);

    operationList.AddOperation(buttonSearch, container);
}