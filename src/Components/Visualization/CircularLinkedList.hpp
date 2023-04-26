#ifndef COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP

#include "LinkedList.hpp"

namespace GUI {
    class CircularLinkedList : public GUI::LinkedList {
    private:
        std::vector< ArrowType > arrowState;

        ArrowType defaultArrowType = ArrowType::Default;

    public:
    public:
        CircularLinkedList();
        CircularLinkedList(FontHolder* fonts);
        ~CircularLinkedList();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

        void SetDefaultArrowType(ArrowType arrowType);

    public:
        void Import(std::vector< int > nodes);
        void InsertNode(std::size_t index, GUI::Node node,
                        bool rePosition = true);
        void DeleteNode(std::size_t index, bool rePosition = true);

    public:
        void SetArrowType(std::size_t index, ArrowType type);
        ArrowType GetArrowType(std::size_t index);
        void ResetArrow();

    private:
        void DrawArrow(Vector2 base, float t);
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP