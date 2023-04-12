#ifndef STATES_LINKEDLIST_LLSTATE_HPP
#define STATES_LINKEDLIST_LLSTATE_HPP

#include "../../Components/OperationContainer.hpp"
#include "../../Components/OperationList.hpp"
#include "../../State.hpp"

class LLState : public State {
private:
public:
    LLState(StateStack& stack, Context context, DataStructures::ID activeDS);
    ~LLState();
    virtual void Draw() = 0;
    virtual bool Update(float dt) = 0;

protected:
    void InitNavigationBar();
    Context mContext;

protected:
    OperationList operationList;
    virtual void AddOperations();  // DO NOT OVERRIDE THIS FUNCTION
    virtual void AddInitializeOperation();
    virtual void AddInsertOperation();
    virtual void AddDeleteOperation();
    virtual void AddUpdateOperation();
    virtual void AddSearchOperation();

private:
    DataStructures::ID activeDS;
};

#endif  // STATES_LINKEDLIST_LLSTATE_HPP