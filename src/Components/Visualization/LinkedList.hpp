#ifndef COMPONENTS_VISUALIZATION_LINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_LINKEDLIST_HPP

#include "Container.hpp"
#include "Node.hpp"

namespace GUIVisualizer {
    /**
     * @brief The base class for the linked list visualization. This class
     * provides the basic functionality for the linked list visualization.
     */
    class LinkedList : public GUI::Container {
    public:
        /**
         * @brief The type of the arrow.
         * @details The type of the arrow is used to determine the color of the
         * arrow.
         */
        enum ArrowType {
            Default,
            Hidden,
            Active,
            Skip,
            ArrowTypeCount,
        };

        /**
         * @brief The orientation of the linked list.
         * @details The orientation of the linked list is used to determine the
         * orientation of the linked list.
         */
        enum Orientation {
            Horizontal,
            Vertical,

            OrientationCount,
        };

    public:
        /**
         * @brief The distance between the GUI nodes.
         */
        static constexpr float mNodeDistance = 20;

    protected:
        FontHolder* fonts;
        std::vector< Node > list;
        bool mDisplayHeadAndTail;

        /**
         * @brief The orientation of the linked list, by default it is
         * horizontal.
         */
        Orientation mOrientation = Orientation::Horizontal;

        /**
         * @brief The shape of the node, by default it is a circle.
         */
        Node::Shape mShape = Node::Shape::Circle;

    public:
        /**
         * @brief Set the shape of the node.
         */
        void SetShape(Node::Shape shape);

        /**
         * @brief Get the shape of the node.
         */
        Node::Shape GetShape() const;

    public:
        /**
         * @brief Construct a new linked list visualization.
         */
        LinkedList();

        /**
         * @brief Construct a new linked list visualization.
         * @param fonts The fonts to be used in the linked list visualization.
         */
        LinkedList(FontHolder* fonts);

        /**
         * @brief Destroy the linked list visualization.
         */
        ~LinkedList();

        bool isSelectable() const;

        /**
         * @brief Draw the linked list visualization.
         * @param base The base position of the linked list visualization.
         * @param t The interpolation value.
         * @param init Whether the linked list visualization is initialized.
         * @details This function draws the linked list visualization.
         */
        virtual void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                          bool init = false) = 0;

        /**
         * @brief Get the size of the linked list visualization.
         * @return The size of the linked list visualization.
         */
        virtual std::size_t size() const;

        virtual void SetShowHeadAndTail(bool show);

        /**
         * @brief Set the orientation of the linked list visualization.
         * @param orientation The orientation of the linked list visualization.
         */
        virtual void SetOrientation(Orientation orientation);

    public:
        virtual std::vector< Node >& GetList();
        virtual Node GenerateNode(int value);

        /**
         * @brief Initialize the linked list visualization with the given nodes.
         * @param nodes The nodes to initialize the linked list visualization.
         */
        virtual void Import(std::vector< int > nodes);

        /**
         * @brief Insert a node into the linked list visualization.
         * @param index The index to insert the node.
         * @param node The node to insert.
         * @param rePosition Whether to reposition the whole linked list
         * after insertion.
         * @see Relayout
         */
        virtual void InsertNode(std::size_t index, Node node,
                                bool rePosition = true);

        /**
         * @brief Delete a node from the singly linked list visualization.
         * @param index The index to delete the node.
         * @param rePosition Whether to reposition the whole singly linked list
         * after deletion.
         * @see Relayout
         */
        virtual void DeleteNode(std::size_t index, bool rePosition = true);

        /**
         * @brief relayout the linked list visualization.
         */
        virtual void Relayout();

    protected:
        Vector2 GetNodeDefaultPosition(std::size_t index);
    };
};      // namespace GUIVisualizer

#endif  // COMPONENTS_VISUALIZATION_LINKEDLIST_HPP