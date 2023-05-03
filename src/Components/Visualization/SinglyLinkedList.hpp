#ifndef COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP

#include "LinkedList.hpp"

namespace GUIVisualizer {
    /**
     * @brief The singly linked list visualization.
     * @details The singly linked list visualization is used to visualize the
     * singly linked list.
     */
    class SinglyLinkedList : public GUIVisualizer::LinkedList {
    private:
        std::vector< ArrowType > arrowState;

    public:
        /**
         * @brief Construct a new Singly Linked List object.
         */
        SinglyLinkedList();

        /**
         * @brief Construct a new Singly Linked List object.
         */
        SinglyLinkedList(FontHolder* fonts);

        /**
         * @brief Destroy the Singly Linked List object.
         */
        ~SinglyLinkedList();

        bool isSelectable() const;

        /**
         * @brief Draw the singly linked list visualization.
         * @details This function draws the singly linked list visualization.
         * @param base The base position of the singly linked list
         * visualization.
         * @param t The time delta.
         * @param init True if the singly linked list visualization is
         * initializing.
         */
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        /**
         * @brief Initialize the singly linked list visualization with the given
         * nodes.
         * @param nodes The nodes to initialize the singly linked list
         * visualization with.
         * @see LinkedList::Import
         */
        void Import(std::vector< int > nodes);

        /**
         * @brief Insert a node into the singly linked list visualization.
         * @param index The index to insert the node.
         * @param node The node to insert.
         * @param rePosition Whether to reposition the whole singly linked list
         * after insertion.
         * @see LinkedList::InsertNode
         */
        void InsertNode(std::size_t index, Node node, bool rePosition = true);

        /**
         * @brief Delete a node from the singly linked list visualization.
         * @param index The index to delete the node.
         * @param rePosition Whether to reposition the whole singly linked list
         * after deletion.
         * @see LinkedList::DeleteNode
         */
        void DeleteNode(std::size_t index, bool rePosition = true);

    public:
        void SetArrowType(std::size_t index, ArrowType type);
        ArrowType GetArrowType(std::size_t index);
        void ResetArrow();

    private:
        void DrawArrow(Vector2 base, float t);
    };
};      // namespace GUIVisualizer

#endif  // COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP