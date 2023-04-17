#ifndef STATES_LINKEDLIST_LLSTATE_HPP
#define STATES_LINKEDLIST_LLSTATE_HPP

#include "Components/Common/CodeHighlighter.hpp"
#include "Components/Common/OperationContainer.hpp"
#include "Components/Common/OperationList.hpp"
#include "Components/Common/OptionInputField.hpp"
#include "State.hpp"

class LLState : public State {
public:
    struct IntegerInput {
        std::string label;
        int width;
        int minValue;
        int maxValue;
    };

public:
    LLState(StateStack& stack, Context context, DataStructures::ID activeDS);
    ~LLState();
    virtual void Draw() = 0;
    virtual bool Update(float dt) = 0;

protected:
    void InitNavigationBar();
    Context mContext;

protected:
    GUI::CodeHighlighter codeHighlighter;

protected:
    GUI::OperationList operationList;
    virtual void AddOperations();  // DO NOT OVERRIDE THIS FUNCTION
    virtual void AddInitializeOperation();
    virtual void AddInsertOperation();
    virtual void AddDeleteOperation();
    virtual void AddUpdateOperation();
    virtual void AddSearchOperation();

protected:
    virtual void AddNoFieldOperationOption(
        GUI::OperationContainer::Ptr container, std::string title,
        std::function< void() > action);
    virtual void AddIntFieldOperationOption(
        GUI::OperationContainer::Ptr container, std::string title,
        std::vector< IntegerInput > fields,
        std::function< void(std::map< std::string, std::string >) > action);
    virtual void AddStringFieldOption(
        GUI::OperationContainer::Ptr container, std::string title,
        std::string label,
        std::function< void(std::map< std::string, std::string >) > action);

private:
    DataStructures::ID activeDS;
};

#endif  // STATES_LINKEDLIST_LLSTATE_HPP