#ifndef STATES_LINKEDLIST_SLLSTATE_HPP
#define STATES_LINKEDLIST_SLLSTATE_HPP
#include "Components/Common/CodeHighlighter.hpp"
#include "LLState.hpp"

class SLLState : public LLState {
private:
    void AddInsertOperation();
    void AddInitializeOperation();
    void AddUpdateOperation();
    void AddDeleteOperation();
    void AddSearchOperation();

private:
    GUI::CodeHighlighter codeHighlighter;

protected:
public:
    SLLState(StateStack& stack, Context context);
    ~SLLState();
    void Draw();
    bool Update(float dt);
};

#endif  // STATES_LINKEDLIST_SLLSTATE_HPP