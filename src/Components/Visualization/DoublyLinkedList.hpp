#ifndef COMPONENTS_VISUALIZATION_DOUBLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_DOUBLYLINKEDLIST_HPP

#include "LinkedList.hpp"

namespace GUIVisualizer {
    class DoublyLinkedList : public GUIVisualizer::LinkedList {
    public:
    private:
        std::vector< ArrowType > arrowStateNext;
        std::vector< ArrowType > arrowStatePrev;

    public:
    public:
        DoublyLinkedList();
        DoublyLinkedList(FontHolder* fonts);
        ~DoublyLinkedList();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        void Import(std::vector< int > nodes);
        void InsertNode(std::size_t index, Node node, bool rePosition = true);
        void DeleteNode(std::size_t index, bool rePosition = true);

    public:
        void SetArrowTypeNext(std::size_t index, ArrowType type);
        void SetArrowTypePrev(std::size_t index, ArrowType type);
        ArrowType GetArrowTypeNext(std::size_t index);
        ArrowType GetArrowTypePrev(std::size_t index);
        void ResetArrow();

    private:
        void DrawArrow(Vector2 base, float t);
    };
};      // namespace GUIVisualizer

#endif  // COMPONENTS_VISUALIZATION_DOUBLYLINKEDLIST_HPP