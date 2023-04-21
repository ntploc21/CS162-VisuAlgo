#include "SinglyLinkedList.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <mutex>

#include "Core/Animation/AnimationFactory.hpp"

Algorithm::SinglyLinkedList::SinglyLinkedList() {}

Algorithm::SinglyLinkedList::SinglyLinkedList(
    GUI::CodeHighlighter::Ptr codeHighlighter,
    SLLAnimationController::Ptr animController, FontHolder* fonts)
    : codeHighlighter(codeHighlighter), animController(animController),
      visualizer(GUI::SinglyLinkedList(fonts)), create(Algorithm::Create()) {
    visualizer.SetPosition(0, 150);
    InitSLL();
}

Algorithm::SinglyLinkedList::~SinglyLinkedList() {}

void Algorithm::SinglyLinkedList::InitSLL() { Random(); }

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
    animController->Clear();

    visualizer.GetList().clear();
    visualizer.Import(input);

    SLLAnimation state;
    state.SetDuration(0.5);
    state.SetHighlightLine(-1);
    state.SetSourceDataStructure(visualizer);
    state.SetAnimation([this](GUI::SinglyLinkedList srcDS, float playingAt,
                              Vector2 base) {
        auto& nodes = srcDS.GetList();
        for (GUI::Node& node : nodes) {
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);
        }
        srcDS.Draw(base, playingAt, true);
        return srcDS;
    });

    animController->AddAnimation(state);
    animController->Continue();
    animController->InteractionLock();
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

void Algorithm::SinglyLinkedList::Search(int value) {
    animController->InteractionAllow();
    animController->Clear();

    codeHighlighter->AddCode({"Node *cur = head;", "while(cur != nullptr) {",
                              "	if(cur->value == v) return cur;",
                              "	cur = cur->next;", "}",
                              "return nullptr; // NOT_FOUND"});
    codeHighlighter->SetShowCode(true);
    codeHighlighter->SetShowAction(true);

    if (!visualizer.GetList().size()) {
        animController->AddAnimation(
            GenerateAnimation(0.5, 0, "Set cur to head."));
        animController->AddAnimation(GenerateAnimation(
            1, 1, "cur is currently NULL, so we will halt the while loop."));
        animController->AddAnimation(
            GenerateAnimation(0.5, 5, "Element not found, return NULL"));
        animController->Continue();
        return;
    }
    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) node.AnimationOnNode(true);

    nodes[0].SetNodeState(GUI::Node::Active);
    SLLAnimation anim1 = GenerateAnimation(0.5, 0, "Set cur to head.");
    animController->AddAnimation(anim1);

    int i = 0;
    bool found = false;
    do {
        nodes[i].AnimationOnNode(false);
        SLLAnimation animLoop1 =
            GenerateAnimation(0.5, 1, "Check whether the current node is NULL");
        animController->AddAnimation(animLoop1);
        if (i == nodes.size()) break;
        SLLAnimation animLoop2 = GenerateAnimation(
            1, 2, "Check if the current node's value is equal to v");
        SLLAnimation animLoop3;
        if (nodes[i].GetValue() == value) {
            animLoop3 = GenerateAnimation(
                0.5, 2,
                "Found value v = " + std::to_string(value) +
                    " at this highlighted vertex so we return index " +
                    std::to_string(i) + ".\nThe whole operation is O(N)");
            found = true;
        } else {
            nodes[i].AnimationOnNode(true);
            nodes[i].SetNodeState(GUI::Node::Iterated);
            if (i + 1 < nodes.size()) {
                nodes[i + 1].SetNodeState(GUI::Node::Active);
            }
            animLoop3 = GenerateAnimation(0.5, 3, "Advance to the next node");

            if (i + 1 < nodes.size()) {
                animLoop3.SetAnimation([this, i](GUI::SinglyLinkedList srcDS,
                                                 float playingAt,
                                                 Vector2 base) {
                    auto& nodes = visualizer.GetList();
                    srcDS.Draw(base, playingAt);
                    base.x += srcDS.GetPosition().x;
                    base.y += srcDS.GetPosition().y;

                    Vector2 start = nodes[i].GetPosition();
                    Vector2 end = nodes[i + 1].GetPosition();
                    start.x += base.x + 20, start.y += base.y;
                    end.x += base.x - 20, end.y += base.y;

                    AnimationFactory::DrawActiveArrow(start, end, playingAt);
                    return srcDS;
                });
                visualizer.SetActiveArrow(i);
            }
        }
        animController->AddAnimation(animLoop2);
        animController->AddAnimation(animLoop3);
        nodes[i].AnimationOnNode(false);
    } while (!found && ++i);

    if (!found) {
        SLLAnimation animNotFound = GenerateAnimation(
            0.5, 5,
            "cur is null (we have gone past the tail after O(N) step(s)).\n"
            "We can conclude that value v = 90 is NOT FOUND in the Linked "
            "List");
        animController->AddAnimation(animNotFound);
    }

    for (GUI::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUI::Node::Default);
    }
    visualizer.ClearActiveArrow();
    animController->Reset();
    animController->Continue();
}

SLLAnimation Algorithm::SinglyLinkedList::GenerateAnimation(
    float duration, int highlightLine, std::string actionDescription) {
    SLLAnimation animation;
    animation.SetDuration(duration);
    animation.SetHighlightLine(highlightLine);
    animation.SetSourceDataStructure(visualizer);
    animation.SetActionDescription(actionDescription);
    return animation;
}
