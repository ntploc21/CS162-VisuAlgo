#ifndef COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP

#include "DataStructure.hpp"
#include "Node.hpp"

namespace GUI {
    class SinglyLinkedList : public GUI::DataStructure {
    private:
        FontHolder* fonts;
        std::vector< GUI::Node > list;

    public:
        SinglyLinkedList();
        SinglyLinkedList(FontHolder* fonts);
        ~SinglyLinkedList();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0});

    public:
        std::vector< GUI::Node >& GetList();
        GUI::Node GenerateNode(int value);
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP