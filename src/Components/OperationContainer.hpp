#ifndef COMPONENTS_OPERATIONCONTAINER_HPP
#define COMPONENTS_OPERATIONCONTAINER_HPP

#include "../Container.hpp"
#include "Button.hpp"

class OperationContainer : public GUI::Container {
private:
public:
    typedef std::shared_ptr< OperationContainer > Ptr;
    OperationContainer();
    ~OperationContainer();
    void AddOperation(GUI::Component::Ptr option);
};

#endif  // COMPONENTS_OPERATIONCONTAINER_HPP