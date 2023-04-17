#include "LLState.hpp"

#include <iostream>

#include "Components/Common/IntegerInputField.hpp"
#include "Components/Common/StringInputField.hpp"
#include "Global.hpp"

LLState::LLState(StateStack& stack, Context context,
                 DataStructures::ID activeDS)
    : State(stack, context), activeDS(activeDS),
      codeHighlighter(GUI::CodeHighlighter(context.fonts)) {
    InitNavigationBar();
    operationList = GUI::OperationList(context.fonts);
    codeHighlighter.SetPosition(global::SCREEN_WIDTH - 40,
                                global::SCREEN_HEIGHT - 334);
    codeHighlighter.InitButtons();
}

LLState::~LLState() {}

void LLState::InitNavigationBar() {
    navigation.SetVisableTitle(true);
    auto info = GetContext().categories->Get(Category::LinkedList);
    navigation.SetCategory(info.categoryName);
    navigation.SetActiveTitle(activeDS);
    for (auto dsID : info.mDS) {
        auto dsInfo = GetContext().dsInfo->Get(dsID);
        navigation.InsertTitle(dsID, dsInfo.stateID, dsInfo.abbr, dsInfo.name);
    };
}

void LLState::AddOperations() {
    AddInitializeOperation();
    AddInsertOperation();
    AddDeleteOperation();
    AddUpdateOperation();
    AddSearchOperation();

    operationList.SetPosition(
        0, global::SCREEN_HEIGHT - 60 - operationList.GetSize().y);
    operationList.InitActionBar();
}

void LLState::AddInitializeOperation() {}

void LLState::AddInsertOperation() {}

void LLState::AddDeleteOperation() {}

void LLState::AddUpdateOperation() {}

void LLState::AddSearchOperation() {}

void LLState::AddNoFieldOperationOption(GUI::OperationContainer::Ptr container,
                                        std::string title,
                                        std::function< void() > action) {
    GUI::OptionInputField::Ptr button(
        new GUI::OptionInputField(GetContext().fonts));

    button.get()->SetNoFieldOption(title, action);

    container.get()->pack(button);
}

void LLState::AddIntFieldOperationOption(
    GUI::OperationContainer::Ptr container, std::string title,
    std::vector< IntegerInput > fields,
    std::function< void(std::map< std::string, std::string >) > action) {
    GUI::OptionInputField::Ptr button(
        new GUI::OptionInputField(GetContext().fonts));
    std::vector< GUI::InputField::Ptr > intFields;
    for (auto field : fields) {
        GUI::IntegerInputField::Ptr intField(
            new GUI::IntegerInputField(GetContext().fonts));
        intField.get()->SetLabel(field.label);
        intField.get()->SetInputFieldSize((Vector2){(float)field.width, 30});
        intField.get()->SetConstraint(field.minValue, field.maxValue);
        intFields.push_back(intField);
    }

    button.get()->SetOption(title, intFields, action);

    container.get()->pack(button);
}

void LLState::AddStringFieldOption(
    GUI::OperationContainer::Ptr container, std::string title,
    std::string label,
    std::function< void(std::map< std::string, std::string >) > action) {
    GUI::OptionInputField::Ptr button(
        new GUI::OptionInputField(GetContext().fonts));
    GUI::StringInputField::Ptr strField(
        new GUI::StringInputField(GetContext().fonts));
    strField.get()->SetLabel(label);
    strField.get()->SetInputFieldSize((Vector2){100, 30});
    button.get()->SetOption(title, {strField}, action);
    container.get()->pack(button);
}
