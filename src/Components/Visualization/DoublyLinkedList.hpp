#ifndef COMPONENTS_VISUALIZATION_DOUBLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_DOUBLYLINKEDLIST_HPP

#include "LinkedList.hpp"

namespace GUIVisualizer {
    /**
     * @brief The doubly linked list visualization.
     * @details The doubly linked list visualization is used to visualize the
     * doubly linked list.
     */
    class DoublyLinkedList : public GUIVisualizer::LinkedList {
    private:
        std::vector< ArrowType > arrowStateNext;
        std::vector< ArrowType > arrowStatePrev;

    public:
        /**
         * @brief Construct a new Doubly Linked List object.
         */
        DoublyLinkedList();

        /**
         * @brief Construct a new Doubly Linked List object.
         */
        DoublyLinkedList(FontHolder* fonts);

        /**
         * @brief Destroy the Doubly Linked List object.
         */
        ~DoublyLinkedList();

        bool isSelectable() const;

        /**
         * @brief Draw the doubly linked list visualization.
         * @details This function draws the doubly linked list visualization.
         * @param base The base position of the doubly linked list
         * visualization.
         * @param t The time delta.
         * @param init True if the doubly linked list visualization is
         * initializing.
         */
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        /**
         * @brief Initialize the doubly linked list visualization with the given
         * nodes.
         * @param nodes The nodes to initialize the doubly linked list
         * visualization with.
         * @see LinkedList::Import
         */
        void Import(std::vector< int > nodes);

        /**
         * @brief Insert a node into the doubly linked list visualization.
         * @param index The index to insert the node.
         * @param node The node to insert.
         * @param rePosition Whether to reposition the whole doubly linked list
         * after insertion.
         * @see LinkedList::InsertNode
         */
        void InsertNode(std::size_t index, Node node, bool rePosition = true);

        /**
         * @brief Delete a node from the doubly linked list visualization.
         * @param index The index to delete the node.
         * @param rePosition Whether to reposition the whole doubly linked list
         * after deletion.
         * @see LinkedList::DeleteNode
         */
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