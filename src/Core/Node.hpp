#ifndef CORE_NODE_HPP
#define CORE_NODE_HPP

namespace Core {
    template< typename T >
    class Node {
    public:
        T mValue;
        Node< T >*mPrev, *mNext;

    public:
        Node() : mValue(T()), mPrev(nullptr), mNext(nullptr) {}
        Node(const T& value) : mValue(value), mPrev(nullptr), mNext(nullptr) {}
        Node(const Node< T >& node)
            : mValue(node.mValu), mPrev(node.mPrev), mNext(node.mNext) {}
        Node(const T& value, Node< T >* const& prev, Node< T >* const& next)
            : mValue(value), mPrev(prev), mNext(next) {}
    };
}  // namespace Core

#endif  // CORE_NODE_HPP