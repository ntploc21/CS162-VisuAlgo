#include "SinglyLinkedList.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <mutex>

Algorithm::SinglyLinkedList::SinglyLinkedList() {}

Algorithm::SinglyLinkedList::SinglyLinkedList(
    GUI::CodeHighlighter::Ptr codeHighlighter,
    SLLAnimationController::Ptr animController, FontHolder* fonts)
    : codeHighlighter(codeHighlighter), animController(animController),
      visualizer(GUI::SinglyLinkedList(fonts)), create(Algorithm::Create()) {}

Algorithm::SinglyLinkedList::~SinglyLinkedList() {}

void Algorithm::SinglyLinkedList::Empty() { ApplyInput({}); }

void Algorithm::SinglyLinkedList::Random() {
    std::vector< int > input = create.Random();
    ApplyInput(input);
}

void Algorithm::SinglyLinkedList::RandomFixedSize(int N) {
    std::vector< int > input = create.RandomFixedSize(N);
    ApplyInput(input);
}

void Algorithm::SinglyLinkedList::UserDefined(std::string input) {
    std::mutex m;
    bool canParse =
        (!input.empty() &&
         std::all_of(
             input.begin(), input.end(),
             [](char c) { return ('0' <= c && c <= '9') || (c == ','); }) &&
         input.back() != ',');
    if (!canParse) {
        Empty();
        return;
    }
    std::vector< int > inputArr;

    for (int i = 0, j = 0; j < input.size(); i = j) {
        while (j < input.size() && input[j] != ',') j++;
        int num = std::stoi(input.substr(i, j - i));
        inputArr.emplace_back(num);
        j++;
    }
    ApplyInput(inputArr);
}

void Algorithm::SinglyLinkedList::ReadFromExternalFile(std::string path) {}

void Algorithm::SinglyLinkedList::Sorted() {}

void Algorithm::SinglyLinkedList::ApplyInput(std::vector< int > input) {
    if (input.size() > maxN) input.resize(maxN);
    for (int v : input) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    visualizer.GetList().clear();

    GUI::Node guiNode = visualizer.GenerateNode(10);
    guiNode.SetLabel("head");
    guiNode.SetPosition(300, 300);
    visualizer.GetList().emplace_back(guiNode);

    SLLAnimation state;
    state.SetDuration(0);
    state.SetHighlightLine(-1);
    state.SetSourceDataStructure(visualizer);
    state.SetAnimation(
        [this](GUI::SinglyLinkedList srcDS, float playingAt, Vector2 base) {
            srcDS.Draw(base);
            return srcDS;
        });

    animController->AddAnimation(state);
    // state.SetAnimation();

    // Clear();
    // head = new BaseNode< T >();
    // Node_ptr cur = head;
    // for (int value : input) {
    //     cur->data = value;
    //     cur->next = new BaseNode< T >();
    //     cur = cur->next;
    // }
    // size = input.size();
}

void Algorithm::SinglyLinkedList::Insert(int index, int value) {}

void Algorithm::SinglyLinkedList::InsertHead(int value) {}

void Algorithm::SinglyLinkedList::InsertAfterTail(int value) {}

void Algorithm::SinglyLinkedList::InsertMiddle(int index, int value) {}

void Algorithm::SinglyLinkedList::Delete(int index) {}

void Algorithm::SinglyLinkedList::DeleteHead() {}

void Algorithm::SinglyLinkedList::DeleteTail() {}

void Algorithm::SinglyLinkedList::DeleteMiddle(int index) {}

void Algorithm::SinglyLinkedList::Update(int index, int value) {}

void Algorithm::SinglyLinkedList::Search(int value) {}
