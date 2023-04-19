#ifndef CORE_DATASTRUCTURES_LINKEDLIST_BASENODE_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_BASENODE_HPP

#include <initializer_list>

template< typename T >
class BaseNode {
public:
    BaseNode();
    ~BaseNode();
    T data{};
    BaseNode< T >* prev{};
    BaseNode< T >* next{};
};

template< typename T >
inline BaseNode< T >::BaseNode() {}
template< typename T >
inline BaseNode< T >::~BaseNode() {}

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_BASENODE_HPP