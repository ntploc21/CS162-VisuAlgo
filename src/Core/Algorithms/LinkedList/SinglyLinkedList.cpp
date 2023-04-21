#include "SinglyLinkedList.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <mutex>

#include "Core/Animation/AnimationFactory.hpp"
#include "Global.hpp"

using ArrowType = GUI::SinglyLinkedList::ArrowType;

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
    codeHighlighter->SetShowCode(false);
    codeHighlighter->SetShowAction(false);

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
    animController->Reset();
    animController->Continue();
    animController->InteractionLock();
}

void Algorithm::SinglyLinkedList::Insert(int index, int value) {}

void Algorithm::SinglyLinkedList::InsertHead(int value) {
    if (visualizer.GetList().size() == maxN) return;
    animController->InteractionAllow();
    animController->Clear();

    codeHighlighter->AddCode(
        {"Node *node = new Node(v);", "node->next = head;", "head = node;"});
    codeHighlighter->SetShowCode(true);
    codeHighlighter->SetShowAction(true);

    /* Animation goes here */

    visualizer.SetPosition(visualizer.GetPosition().x - 60,
                           visualizer.GetPosition().y);

    GUI::Node newNode = visualizer.GenerateNode(value);
    newNode.SetNodeState(GUI::Node::Active);
    newNode.AnimationOnNode(true);
    newNode.SetLabel("node");

    visualizer.InsertNode(0, newNode);
    visualizer.SetArrowType(0, ArrowType::Hidden);

    SLLAnimation anim1 = GenerateAnimation(
        1, 0,
        "Create new vertex to store value " + std::to_string(value) + ".");
    anim1.SetAnimation(
        [this](GUI::SinglyLinkedList srcDS, float playingAt, Vector2 base) {
            GUI::Node& node = srcDS.GetList().at(0);
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
    animController->AddAnimation(anim1);
    visualizer.GetList()[0].AnimationOnNode(false);

    SLLAnimation anim2 =
        GenerateAnimation(0.5, 1, "node->next points to the current head.");
    if (visualizer.GetList().size() > 1) {
        anim2.SetAnimation(
            [this](GUI::SinglyLinkedList srcDS, float playingAt, Vector2 base) {
                srcDS.Draw(base, playingAt);
                base.x += srcDS.GetPosition().x;
                base.y += srcDS.GetPosition().y;

                Vector2 start = srcDS.GetList()[0].GetPosition();
                Vector2 end = srcDS.GetList()[1].GetPosition();
                start.x += base.x, start.y += base.y;
                end.x += base.x, end.y += base.y;

                AnimationFactory::DrawActiveArrow(start, end, playingAt);

                return srcDS;
            });
        visualizer.SetArrowType(0, ArrowType::Active);

        visualizer.GetList()[1].ClearLabel();
    } else
        anim2.SetActionDescription(
            "node->next points to the current head.\nHead is currently null.");
    animController->AddAnimation(anim2);

    visualizer.GetList()[0].SetLabel("head");
    SLLAnimation anim3 = GenerateAnimation(0.5, 2, "head points to node.");
    animController->AddAnimation(anim3);

    float length = 40 * visualizer.GetList().size() +
                   20 * (visualizer.GetList().size() - 1);
    float actualPosX = (global::SCREEN_WIDTH - length) / 2;
    SLLAnimation anim4 = GenerateAnimation(
        0.5, -1,
        "Re-layout the Linked List for visualization (not in the actual Linked "
        "List).\nThe whole process is still O(1).");
    anim4.SetAnimation([this, actualPosX](GUI::SinglyLinkedList srcDS,
                                          float playingAt, Vector2 base) {
        Vector2 newPos = srcDS.GetPosition();
        newPos.x += (actualPosX - newPos.x) * playingAt;
        srcDS.SetPosition(newPos);

        if (playingAt == 1.0f && srcDS.GetList().size() == 2) {
            srcDS.GetList().back().SetLabel("tail");
        }

        srcDS.Draw(base, playingAt);

        return srcDS;
    });
    animController->AddAnimation(anim4);

    visualizer.Relayout();

    animController->Reset();
    animController->Continue();
}

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
    nodes[0].SetLabel("head/0");
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
            nodes[i].ClearLabel();
            if (i == 0)
                nodes[i].SetLabel("head");
            else if (i + 1 == nodes.size())
                nodes[i].SetLabel("tail");
        } else {
            nodes[i].AnimationOnNode(true);
            nodes[i].SetNodeState(GUI::Node::Iterated);
            if (i == 0)
                nodes[i].SetLabel("head");
            else if (i + 1 == nodes.size())
                nodes[i].SetLabel("tail");
            else
                nodes[i].ClearLabel();

            if (i + 1 < nodes.size()) {
                nodes[i + 1].SetNodeState(GUI::Node::Active);
                if (i + 1 == nodes.size() - 1)
                    nodes[i + 1].SetLabel("tail/cur/" + std::to_string(i + 1));
                else
                    nodes[i + 1].SetLabel("cur/" + std::to_string(i + 1));
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
                    start.x += base.x, start.y += base.y;
                    end.x += base.x, end.y += base.y;

                    AnimationFactory::DrawActiveArrow(start, end, playingAt);
                    return srcDS;
                });
                visualizer.SetArrowType(i, ArrowType::Active);
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
    visualizer.ResetArrow();
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
