#ifndef CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP

#include "../../Operations/Create/Create.hpp"
#include "BaseNode.hpp"

template< typename T >
class SinglyLinkedList {
private:
    Create create = Create();
    using Node_ptr = BaseNode< T >*;
    Node_ptr head{nullptr};
    std::size_t size;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    void Random();
    void RandomFixedSize(int nSize);
    void UserDefined(std::string userInput);
    void ReadFromFile(std::string inputFile);
    // private:
    void Clear();
    std::size_t Size();

private:
    void ApplyInput(std::vector< int > input);
};

template< typename T >
inline SinglyLinkedList< T >::SinglyLinkedList() {
    create = Create();
}

template< typename T >
inline SinglyLinkedList< T >::~SinglyLinkedList() {
    Clear();
}

template< typename T >
inline void SinglyLinkedList< T >::Random() {
    std::vector< int > input = create.Random();
    ApplyInput(input);
}

template< typename T >
inline void SinglyLinkedList< T >::RandomFixedSize(int nSize) {
    std::vector< int > input = create.RandomFixedSize(nSize);
    ApplyInput(input);
    // std::map<std::string, std::string> params;
}

template< typename T >
inline void SinglyLinkedList< T >::UserDefined(std::string userInput) {
    std::vector< int > input = create.UserDefined(userInput);
    ApplyInput(input);
}

template< typename T >
inline void SinglyLinkedList< T >::ReadFromFile(std::string inputFile) {
    std::vector< int > input = create.ReadFromFile(inputFile);
    ApplyInput(input);
}

template< typename T >
inline void SinglyLinkedList< T >::Clear() {
    while (head != nullptr) {
        Node_ptr next = head->next;
        delete head;
        head = next;
    }
    size = 0;
}

template< typename T >
inline std::size_t SinglyLinkedList< T >::Size() {
    return size;
}

template< typename T >
inline void SinglyLinkedList< T >::ApplyInput(std::vector< int > input) {
    Clear();
    head = new BaseNode< T >();
    Node_ptr cur = head;
    for (int value : input) {
        cur->data = value;
        cur->next = new BaseNode< T >();
        cur = cur->next;
    }
    size = input.size();
}

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP