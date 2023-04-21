#ifndef COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP

#include "DataStructure.hpp"
#include "Node.hpp"

namespace GUI {
    class SinglyLinkedList : public GUI::DataStructure {
    private:
        FontHolder* fonts;
        std::vector< GUI::Node > list;
        std::vector< bool > arrowState;

    public:
        SinglyLinkedList();
        SinglyLinkedList(FontHolder* fonts);
        ~SinglyLinkedList();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        std::vector< GUI::Node >& GetList();
        GUI::Node GenerateNode(int value);
        void Import(std::vector< int > nodes);

    public:
        void SetActiveArrow(std::size_t index);
        void ClearActiveArrow();

    private:
        void DrawArrow(Vector2 base, float t);
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP