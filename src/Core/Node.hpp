#ifndef CORE_NODE_HPP
#define CORE_NODE_HPP

namespace Core {
    /**
     * @brief The node class that is used to store the value of the node, and
     * the pointers to the previous and the next node (similar to Doubly Linked
     * List node).
     * @tparam T The type of the value of the node.
     */
    template< typename T >
    class Node {
    public:
        /**
         * @brief The value of the node.
         */
        T mValue;

        /**
         * @brief The pointer to the previous node.
         */
        Node< T >* mPrev;

        /**
         * @brief The pointer to the next node.
         */
        Node< T >* mNext;

    public:
        /**
         * @brief The default constructor of the node.
         */
        Node() : mValue{T()}, mPrev{nullptr}, mNext{nullptr} {}

        /**
         * @brief The constructor of the node.
         * @param value The value of the node.
         */
        Node(const T& value) : mValue{value}, mPrev{nullptr}, mNext{nullptr} {}

        /**
         * @brief The copy constructor of the node.
         * @param node The node that will be copied.
         */
        Node(const Node< T >& node)
            : mValue{node.mValue}, mPrev{node.mPrev}, mNext{node.mNext} {}

        /**
         * @brief The constructor of the node.
         * @param value The value of the node.
         * @param prev The pointer to the previous node.
         * @param next The pointer to the next node.
         */
        Node(const T& value, Node< T >* const& prev, Node< T >* const& next)
            : mValue{value}, mPrev{prev}, mNext{next} {}
    };
}  // namespace Core

#endif  // CORE_NODE_HPP