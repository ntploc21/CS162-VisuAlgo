#ifndef COMPONENTS_OPERATIONCONTAINER_HPP
#define COMPONENTS_OPERATIONCONTAINER_HPP

#include "../Container.hpp"
#include "Button.hpp"

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
};

#endif  // COMPONENTS_OPERATIONCONTAINER_HPP