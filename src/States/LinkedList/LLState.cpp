// #include "LLState.hpp"

// #include <iostream>

// #include "Components/Common/IntegerInputField.hpp"
// #include "Components/Common/StringInputField.hpp"
// #include "Global.hpp"

// template< typename T >
// LLState< T >::LLState(StateStack& stack, Context context,
//                       DataStructures::ID activeDS)
//     : State(stack, context), activeDS(activeDS),
//       codeHighlighter(new GUI::CodeHighlighter(context.fonts)),
//       footer(GUI::Footer< T >()), animController(new T()) {
//     InitNavigationBar();
//     operationList = GUI::OperationList(context.fonts);
//     codeHighlighter->SetPosition(global::SCREEN_WIDTH - 40,
//                                  global::SCREEN_HEIGHT - 334);
//     codeHighlighter->InitButtons();

//     footer.SetPosition(0, global::SCREEN_HEIGHT - 40);
// }

// template< typename T >
// LLState< T >::~LLState() {}

// template< typename T >
// bool LLState< T >::Update(float dt) {
//     animController->Update(dt);
//     return true;
// }

// template< typename T >
// void LLState< T >::InitNavigationBar() {
//     navigation.SetVisableTitle(true);
//     auto info = GetContext().categories->Get(Category::LinkedList);
//     navigation.SetCategory(info.categoryName);
//     navigation.SetActiveTitle(activeDS);
//     for (auto dsID : info.mDS) {
//         auto dsInfo = GetContext().dsInfo->Get(dsID);
//         navigation.InsertTitle(dsID, dsInfo.stateID, dsInfo.abbr,
//         dsInfo.name);
//     };
// }

// template< typename T >
// void LLState< T >::AddOperations() {
//     AddInitializeOperation();
//     AddInsertOperation();
//     AddDeleteOperation();
//     AddUpdateOperation();
//     AddSearchOperation();

//     operationList.SetPosition(
//         0, global::SCREEN_HEIGHT - 60 - operationList.GetSize().y);
//     operationList.InitActionBar();
// }

// template< typename T >
// void LLState< T >::AddInitializeOperation() {}

// template< typename T >
// void LLState< T >::AddInsertOperation() {}

// template< typename T >
// void LLState< T >::AddDeleteOperation() {}

// template< typename T >
// void LLState< T >::AddUpdateOperation() {}

// template< typename T >
// void LLState< T >::AddSearchOperation() {}

// template< typename T >
// void LLState< T >::AddNoFieldOperationOption(
//     GUI::OperationContainer::Ptr container, std::string title,
//     std::function< void() > action) {
//     GUI::OptionInputField::Ptr button(
//         new GUI::OptionInputField(GetContext().fonts));

//     button.get()->SetNoFieldOption(title, action);

//     container.get()->pack(button);
// }

// template< typename T >
// void LLState< T >::AddIntFieldOperationOption(
//     GUI::OperationContainer::Ptr container, std::string title,
//     std::vector< IntegerInput > fields,
//     std::function< void(std::map< std::string, std::string >) > action) {
//     GUI::OptionInputField::Ptr button(
//         new GUI::OptionInputField(GetContext().fonts));
//     std::vector< GUI::InputField::Ptr > intFields;
//     for (auto field : fields) {
//         GUI::IntegerInputField::Ptr intField(
//             new GUI::IntegerInputField(GetContext().fonts));
//         intField.get()->SetLabel(field.label);
//         intField.get()->SetInputFieldSize((Vector2){(float)field.width, 30});
//         intField.get()->SetConstraint(field.minValue, field.maxValue);
//         intFields.push_back(intField);
//     }

//     button.get()->SetOption(title, intFields, action);

//     container.get()->pack(button);
// }

// template< typename T >
// void LLState< T >::AddStringFieldOption(
//     GUI::OperationContainer::Ptr container, std::string title,
//     std::string label,
//     std::function< void(std::map< std::string, std::string >) > action) {
//     GUI::OptionInputField::Ptr button(
//         new GUI::OptionInputField(GetContext().fonts));
//     GUI::StringInputField::Ptr strField(
//         new GUI::StringInputField(GetContext().fonts));
//     strField.get()->SetLabel(label);
//     strField.get()->SetInputFieldSize((Vector2){100, 30});
//     button.get()->SetOption(title, {strField}, action);
//     container.get()->pack(button);
// }
