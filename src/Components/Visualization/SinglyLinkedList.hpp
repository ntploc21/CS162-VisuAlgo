#ifndef COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP

#include "Container.hpp"

namespace GUI {
    class SinglyLinkedList : public GUI::Container {
    private:
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();
        bool isSelectable() const;
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP