#ifndef COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP

#include "LinkedList.hpp"

namespace GUI {
    class SinglyLinkedList : public GUI::LinkedList {
    public:
        enum ArrowType {
            Default,
            Hidden,
            Active,
            Skip,
            ArrowTypeCount,
        };

    private:
        std::vector< ArrowType > arrowState;

        ArrowType defaultArrowType = ArrowType::Default;

    public:
    public:
        SinglyLinkedList();
        SinglyLinkedList(FontHolder* fonts);
        ~SinglyLinkedList();
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

#endif  // COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP