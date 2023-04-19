#ifndef CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP

// #include "../../Operations/Create/Create.hpp"
// #include "BaseNode.hpp"

// template< typename T >
// class SinglyLinkedList {
// private:
//     Create create = Create();
//     using Node_ptr = BaseNode< T >*;
//     Node_ptr head{nullptr};
//     std::size_t size;

// public:
//     SinglyLinkedList();
//     ~SinglyLinkedList();
//     void Random();
//     void RandomFixedSize(int nSize);
//     void UserDefined(std::string userInput);
//     void ReadFromFile(std::string inputFile);
//     // private:
//     void Clear();
//     std::size_t Size();

// private:
//     void ApplyInput(std::vector< int > input);
// };

// template< typename T >
// inline SinglyLinkedList< T >::SinglyLinkedList() {
//     create = Create();
// }

// template< typename T >
// inline SinglyLinkedList< T >::~SinglyLinkedList() {
//     Clear();
// }

// template< typename T >
// inline void SinglyLinkedList< T >::Random() {
//     std::vector< int > input = create.Random();
//     ApplyInput(input);
// }

// template< typename T >
// inline void SinglyLinkedList< T >::RandomFixedSize(int nSize) {
//     std::vector< int > input = create.RandomFixedSize(nSize);
//     ApplyInput(input);
//     // std::map<std::string, std::string> params;
// }

// template< typename T >
// inline void SinglyLinkedList< T >::UserDefined(std::string userInput) {
//     std::vector< int > input = create.UserDefined(userInput);
//     ApplyInput(input);
// }

// template< typename T >
// inline void SinglyLinkedList< T >::ReadFromFile(std::string inputFile) {
//     std::vector< int > input = create.ReadFromFile(inputFile);
//     ApplyInput(input);
// }

// template< typename T >
// inline void SinglyLinkedList< T >::Clear() {
//     while (head != nullptr) {
//         Node_ptr next = head->next;
//         delete head;
//         head = next;
//     }
//     size = 0;
// }

// template< typename T >
// inline std::size_t SinglyLinkedList< T >::Size() {
//     return size;
// }

// template< typename T >
// inline void SinglyLinkedList< T >::ApplyInput(std::vector< int > input) {
//     Clear();
//     head = new BaseNode< T >();
//     Node_ptr cur = head;
//     for (int value : input) {
//         cur->data = value;
//         cur->next = new BaseNode< T >();
//         cur = cur->next;
//     }
//     size = input.size();
// }

#include <string>

// #include "BaseNode.hpp"
#include "Components/Common/CodeHighlighter.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"
#include "Core/Animation/AnimationController.hpp"
#include "Core/Operations/Create/Create.hpp"

namespace Algorithm {
    class SinglyLinkedList {
    public:
        static constexpr int maxN = 10;

    private:
        GUI::SinglyLinkedList visualizer;
        GUI::CodeHighlighter::Ptr codeHighlighter;
        SLLAnimationController::Ptr animController;

    private:
        Algorithm::Create create;

    public:
        SinglyLinkedList();
        SinglyLinkedList(GUI::CodeHighlighter::Ptr codeHighlighter,
                         SLLAnimationController::Ptr animController,
                         FontHolder* fonts);
        ~SinglyLinkedList();

    public:
        void Empty();
        void Random();
        void RandomFixedSize(int N);
        void UserDefined(std::string input);
        void ReadFromExternalFile(std::string path);
        void Sorted();

    private:
        void ApplyInput(std::vector< int > input);

    public:
        void Insert(int index, int value);
        void InsertHead(int value);
        void InsertAfterTail(int value);
        void InsertMiddle(int index, int value);

    public:
        void Delete(int index);
        void DeleteHead();
        void DeleteTail();
        void DeleteMiddle(int index);

    public:
        void Update(int index, int value);

    public:
        void Search(int value);
    };
};  // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP