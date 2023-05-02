#ifndef COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP

#include "LinkedList.hpp"

namespace GUIVisualizer {
    class CircularLinkedList : public GUIVisualizer::LinkedList {
    private:
        std::vector< ArrowType > arrowState;

    private:
        ArrowType circularArrowState;
        std::pair< std::size_t, std::size_t > mCircularEnds;

    public:
        CircularLinkedList();
        CircularLinkedList(FontHolder* fonts);
        ~CircularLinkedList();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        void Import(std::vector< int > nodes);
        void InsertNode(std::size_t index, Node node, bool rePosition = true);
        void DeleteNode(std::size_t index, bool rePosition = true);

    public:
        void SetCircularArrowType(ArrowType type);
        ArrowType GetCircularArrowType(std::size_t index);
        void SetCircularEnds(std::size_t from, std::size_t to);
        std::pair< std::size_t, std::size_t > GetCircularEnds();

        void SetArrowType(std::size_t index, ArrowType type);
        ArrowType GetArrowType(std::size_t index);
        void ResetArrow();

    private:
        void DrawArrow(Vector2 base, float t);
    };
};      // namespace GUIVisualizer

#endif  // COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP