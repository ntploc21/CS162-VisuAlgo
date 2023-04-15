#ifndef COMPONENTS_OPERATIONCONTAINER_HPP
#define COMPONENTS_OPERATIONCONTAINER_HPP

#include "Button.hpp"
#include "Container.hpp"

class OperationContainer : public GUI::Container {
public:
    typedef std::shared_ptr< OperationContainer > Ptr;
    OperationContainer();
    ~OperationContainer();

    void DrawCurrent(Vector2 base = (Vector2){0, 0});

    void SetVisible(bool visible);

private:
    void UpdatePosition();
};

#endif  // COMPONENTS_OPERATIONCONTAINER_HPP