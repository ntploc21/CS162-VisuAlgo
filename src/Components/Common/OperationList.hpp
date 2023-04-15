#ifndef COMPONENTS_OPERATIONLIST_HPP
#define COMPONENTS_OPERATIONLIST_HPP
#include "Button.hpp"
#include "Container.hpp"

class OperationList : public GUI::Container {
private:
    GUI::Container buttons;
    GUI::Container optionContainers;
    bool isHide;
    Button toggleButton;

public:
    void ShowOptions(std::size_t index);
    void HideAllOptions();
    void ToggleOperations();

public:
    void Draw(Vector2 base = (Vector2){0, 0});
    OperationList();
    OperationList(FontHolder *fonts);
    ~OperationList();
    void AddOperation(Button::Ptr action, GUI::Container::Ptr optionContainer);
    void InitActionBar();

    Vector2 GetSize();
};

#endif  // COMPONENTS_OPERATIONLIST_HPP