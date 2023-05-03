#ifndef COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_CIRCULARLINKEDLIST_HPP

#include "LinkedList.hpp"

namespace GUIVisualizer {
    /**
     * @brief The circular linked list visualization.
     * @details The circular linked list visualization is used to visualize the
     * circular linked list.
     */
    class CircularLinkedList : public GUIVisualizer::LinkedList {
    private:
        std::vector< ArrowType > arrowState;

    private:
        ArrowType circularArrowState;
        std::pair< std::size_t, std::size_t > mCircularEnds;

    public:
        /**
         * @brief Construct a new Circular Linked List object.
         */
        CircularLinkedList();

        /**
         * @brief Construct a new Circular Linked List object.
         */
        CircularLinkedList(FontHolder* fonts);

        /**
         * @brief Destroy the Circular Linked List object.
         */
        ~CircularLinkedList();

        bool isSelectable() const;

        /**
         * @brief Draw the circular linked list visualization.
         * @details This function draws the circular linked list visualization.
         * @param base The base position of the circular linked list
         * visualization.
         * @param t The time delta.
         * @param init True if the circular linked list visualization is
         * initializing.
         */
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        /**
         * @brief Initialize the circular linked list visualization with the
         * given nodes.
         * @param nodes The nodes to initialize the circular linked list
         * visualization with.
         * @see LinkedList::Import
         */
        void Import(std::vector< int > nodes);

        /**
         * @brief Insert a node into the circular linked list visualization.
         * @param index The index to insert the node.
         * @param node The node to insert.
         * @param rePosition Whether to reposition the whole circular linked
         * list after insertion.
         * @see LinkedList::InsertNode
         */
        void InsertNode(std::size_t index, Node node, bool rePosition = true);

        /**
         * @brief Delete a node from the circular linked list visualization.
         * @param index The index to delete the node.
         * @param rePosition Whether to reposition the whole circular linked
         * list after deletion.
         * @see LinkedList::DeleteNode
         */
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