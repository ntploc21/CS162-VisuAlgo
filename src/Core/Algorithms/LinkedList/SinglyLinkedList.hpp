#ifndef CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP
#define CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP

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
        void InitSLL();

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

    private:
        SLLAnimation GenerateAnimation(float duration, int highlightLine,
                                       std::string actionDescription);
        void InitAction(std::vector< std::string > code);

        std::function< GUI::SinglyLinkedList(GUI::SinglyLinkedList, float,
                                             Vector2) >
        HighlightArrowFromCur(int index);
    };
};  // namespace Algorithm

#endif  // CORE_DATASTRUCTURES_LINKEDLIST_SINGLYLINKEDLIST_HPP