#ifndef COMPONENTS_VISUALIZATION_DYNAMICARRAY_HPP
#define COMPONENTS_VISUALIZATION_DYNAMICARRAY_HPP

#include "Container.hpp"
#include "Node.hpp"

namespace GUIVisualizer {
    /**
     * @brief The base class for the dynamic array visualization. This class
     * provides the basic functionality for the dynamic array visualization.
     */
    class DynamicArray : public GUI::Container {
    public:
        /**
         * @brief The default constructor of the dynamic array visualization.
         */
        DynamicArray();

        /**
         * @brief The constructor of the dynamic array visualization.
         * @param fonts The fonts that are used to draw the text.
         */
        DynamicArray(FontHolder* fonts);

        bool isSelectable() const;

        /**
         * @brief The destructor of the dynamic array visualization.
         */
        ~DynamicArray();

        /**
         * @brief Draw the dynamic array visualization.
         * @param target The target to draw the dynamic array visualization on.
         * @param states The states used to draw the dynamic array
         * visualization.
         */
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        /**
         * @brief Get the length of the dynamic array visualization.
         * @return The length of the dynamic array visualization.
         */
        std::size_t GetLength() const;

        /**
         * @brief Get the capacity of the dynamic array visualization.
         * @return The capacity of the dynamic array visualization.
         */
        std::size_t GetCapacity() const;

        /**
         * @brief Get the node at the given index.
         * @param index The index of the node to get.
         * @return The node at the given index.
         */
        Node& operator[](std::size_t index);

        /**
         * @brief Get the node at the given index.
         * @param index The index of the node to get.
         * @return The node at the given index.
         */
        const Node& operator[](std::size_t index) const;

    public:
        /**
         * @brief Set the shape of the dynamic array visualization.
         * @param shape The shape of the dynamic array visualization.
         */
        void SetShape(Node::Shape shape);

        /**
         * @brief Get the shape of the dynamic array visualization.
         * @return The shape of the dynamic array visualization.
         */
        Node::Shape GetShape() const;

    public:
        /**
         * @brief Reserve the given size of the dynamic array visualization
         * (more specific, adjust the capacity of the array).
         * @param size The size to reserve.
         */
        void Reserve(std::size_t size);

        /**
         * @brief Resize the dynamic array visualization.
         * @param size The size to resize to.
         */
        void Resize(std::size_t size);

        /**
         * @brief Clear the dynamic array visualization.
         */
        void Clear();

    public:
        /**
         * @brief Get the list of nodes.
         * @return The list of nodes.
         */
        std::vector< Node >& GetList();
        Node GenerateNode(int value);

        /**
         * @brief Initialize the dynamic array visualization with the given
         * nodes.
         * @param nodes The nodes to initialize the dynamic array
         * visualization with.
         */
        void Import(std::vector< int > nodes);

        /**
         * @brief Insert the given node at the given index.
         * @param index The index to insert the node at.
         * @param node The node to insert.
         * @param rePosition Whether to reposition the nodes after inserting.
         * @see Relayout
         */
        void InsertNode(std::size_t index, Node node, bool rePosition = true);

        /**
         * @brief Delete the node at the given index.
         * @param index The index to delete the node at.
         * @param rePosition Whether to reposition the nodes after deleting.
         * @see Relayout
         */
        void DeleteNode(std::size_t index, bool rePosition = true);

        /**
         * @brief Relayout the array visualization.
         */
        void Relayout();

    private:
        Vector2 GetNodeDefaultPosition(std::size_t index);

    public:
        std::size_t GetCapacityFromLength(std::size_t length);

    public:
        static constexpr float mNodeDistance = 20;

    private:
        FontHolder* fonts;
        std::vector< Node > list;
        Node::Shape mShape;

    private:
        std::size_t capacity;
        std::size_t length;
    };
};      // namespace GUIVisualizer

#endif  // COMPONENTS_VISUALIZATION_DYNAMICARRAY_HPP