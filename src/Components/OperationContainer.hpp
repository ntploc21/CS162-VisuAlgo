#ifndef COMPONENTS_OPERATIONCONTAINER_HPP
#define COMPONENTS_OPERATIONCONTAINER_HPP

#include "../Container.hpp"
#include "Button.hpp"

class OperationContainer : public GUI::Container {
private:
    GUI::Container buttons;
    GUI::Container optionContainers;
    bool isHide;
    Button toggleButton;

public:
    void HideAllOptions();
    void ToggleOperations();

public:
    void Draw(Vector2 base = (Vector2){0, 0});
    OperationContainer();
    OperationContainer(FontHolder *fonts);
    ~OperationContainer();
    void AddOperation(Button::Ptr action, GUI::Container::Ptr optionContainer);
    void InitActionBar();
};

#endif  // COMPONENTS_OPERATIONCONTAINER_HPP