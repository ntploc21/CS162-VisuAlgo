#include "SinglyLinkedList.hpp"

GUI::SinglyLinkedList::SinglyLinkedList(FontHolder* fonts) : fonts(fonts) {}
GUI::SinglyLinkedList::SinglyLinkedList() {}
GUI::SinglyLinkedList::~SinglyLinkedList() {}

bool GUI::SinglyLinkedList::isSelectable() const { return false; }

void GUI::SinglyLinkedList::Draw(Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    for (auto node : list) {
        node.Draw(base);
    }
}

std::vector< GUI::Node >& GUI::SinglyLinkedList::GetList() { return list; }

GUI::Node GUI::SinglyLinkedList::GenerateNode(int value) {
    return GUI::Node(value, fonts);
}
