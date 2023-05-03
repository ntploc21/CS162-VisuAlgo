#include "Queue.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>

#include "Animation/AnimationFactory.hpp"
#include "Global.hpp"

using ArrowType = GUIVisualizer::SinglyLinkedList::ArrowType;

Algorithm::Queue::Queue() {}

Algorithm::Queue::Queue(GUIComponent::CodeHighlighter::Ptr codeHighlighter,
                        SLLAnimationController::Ptr animController,
                        FontHolder* fonts)
    : Algorithm::Algorithm(codeHighlighter, animController, fonts) {
    Random();
}

Algorithm::Queue::~Queue() {}

std::size_t Algorithm::Queue::size() const { return visualizer.size(); }

void Algorithm::Queue::EnqueueEmpty(int value) {
    if (visualizer.GetList().size() == maxN) return;
    InitAction({"Node *node = new Node(v);", "node->next = head;",
                "head = node, tail = head;"});

    /* Animation goes here */

    visualizer.InsertNode(0, visualizer.GenerateNode(value));
    visualizer.Relayout();
    auto& node = visualizer.GetList().front();

    node.AnimationOnNode(true);
    node.SetLabel("node");
    node.SetNodeState(GUIVisualizer::Node::Active);

    SLLAnimation anim1 = GenerateAnimation(
        1, 0, "Create new node to store value " + std::to_string(value) + ".");
    anim1.SetAnimation([this](GUIVisualizer::SinglyLinkedList srcDS,
                              float playingAt, Vector2 base) {
        GUIVisualizer::Node& node = srcDS.GetList().at(0);
        node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
        node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
        node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

        srcDS.Draw(base, playingAt);
        return srcDS;
    });
    animController->AddAnimation(anim1);
    node.AnimationOnNode(false);

    SLLAnimation anim2 = GenerateAnimation(
        0.5, 1,
        "node->next points to the current head.\nHead is currently null.");
    animController->AddAnimation(anim2);

    node.SetLabel("head");
    SLLAnimation anim3 = GenerateAnimation(0.5, 2, "head points to node.");
    node.SetNodeState(GUIVisualizer::Node::State::Default);
    animController->AddAnimation(anim3);
}

void Algorithm::Queue::Enqueue(int value) {
    int prvSize = visualizer.size();
    if (prvSize == 0) {
        EnqueueEmpty(value);
        return;
    }

    InitAction(
        {"Node *node = new Node(v);", "tail->next = node;", "tail = node;"});

    /* Animation goes here */

    GUIVisualizer::Node newNode = visualizer.GenerateNode(value);
    newNode.SetNodeState(GUIVisualizer::Node::Active);
    newNode.AnimationOnNode(true);
    newNode.SetLabel("node");

    Vector2 pos = visualizer.GetList().back().GetPosition();
    pos.x += 60;
    newNode.SetPosition(pos);

    visualizer.InsertNode(prvSize, newNode);
    visualizer.SetArrowType(prvSize - 1, ArrowType::Hidden);

    SLLAnimation anim1 = GenerateAnimation(
        1, 0,
        "Create new vertex to store value " + std::to_string(value) + ".");
    anim1.SetAnimation([this](GUIVisualizer::SinglyLinkedList srcDS,
                              float playingAt, Vector2 base) {
        GUIVisualizer::Node& node = srcDS.GetList().back();
        node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
        node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
        node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

        srcDS.Draw(base, playingAt);
        return srcDS;
    });
    animController->AddAnimation(anim1);

    visualizer.GetList().back().SetNodeState(
        GUIVisualizer::Node::State::Iterated);
    visualizer.GetList()[prvSize - 1].SetNodeState(
        GUIVisualizer::Node::State::Active);
    visualizer.GetList()[prvSize - 1].AnimationOnNode(true);
    SLLAnimation anim2 =
        GenerateAnimation(1, 1, "Current tail->next points to the node.");
    anim2.SetAnimation([this, prvSize](GUIVisualizer::SinglyLinkedList srcDS,
                                       float playingAt, Vector2 base) {
        srcDS.Draw(base, playingAt);
        base.x += srcDS.GetPosition().x;
        base.y += srcDS.GetPosition().y;

        Vector2 start = srcDS.GetList()[prvSize - 1].GetPosition();
        Vector2 end = srcDS.GetList()[prvSize].GetPosition();
        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        AnimationFactory::DrawActiveArrow(start, end, playingAt);

        return srcDS;
    });
    visualizer.SetArrowType(prvSize - 1, ArrowType::Default);

    visualizer.GetList()[prvSize - 1].SetNodeState(
        GUIVisualizer::Node::State::Default);
    visualizer.GetList()[prvSize - 1].ClearLabel();
    if (prvSize - 1 == 0) visualizer.GetList()[prvSize - 1].SetLabel("head");
    animController->AddAnimation(anim2);

    visualizer.GetList().back().SetLabel("tail");
    SLLAnimation anim3 =
        GenerateAnimation(0.5, 2,
                          "tail points to node.\nThe whole operation is O(1) "
                          "if we maintain the tail pointer.");
    animController->AddAnimation(anim3);

    visualizer.GetList().back().AnimationOnNode(false);

    float length = 40 * visualizer.GetList().size() +
                   20 * (visualizer.GetList().size() - 1);
    float actualPosX = (global::SCREEN_WIDTH - length) / 2;
    SLLAnimation anim4 = GenerateAnimation(
        0.5, -1,
        "Re-layout the Linked List for visualization (not in the actual Linked "
        "List).\nThe whole process is still O(1).");
    anim4.SetAnimation([this, actualPosX](GUIVisualizer::SinglyLinkedList srcDS,
                                          float playingAt, Vector2 base) {
        Vector2 newPos = srcDS.GetPosition();
        newPos.x += (actualPosX - newPos.x) * playingAt;
        srcDS.SetPosition(newPos);

        srcDS.Draw(base, playingAt);

        return srcDS;
    });
    animController->AddAnimation(anim4);

    visualizer.Relayout();
}

void Algorithm::Queue::Dequeue() {
    InitAction({"if(head == nullptr) return; // empty, do nothing",
                "Node *del = head;", "head = head->next;", "delete del;"});
    auto& nodes = visualizer.GetList();
    if (!nodes.size()) {
        SLLAnimation animNoElement = GenerateAnimation(
            0.75, 0,
            "head is currently NULL, so there is no element to delete.");
        animController->AddAnimation(animNoElement);
        return;
    }
    nodes[0].SetLabel("head/0");
    nodes[0].AnimationOnNode(true);
    nodes[0].SetNodeState(GUIVisualizer::Node::State::Active);
    SLLAnimation anim1 = GenerateAnimation(
        0.75, 0, "head is exist, so we proceed to the next step");
    animController->AddAnimation(anim1);

    nodes[0].AnimationOnNode(false);
    nodes[0].SetLabel("head/del/0");

    if (nodes.size() > 1)

        nodes.back().SetLabel("tail/" + std::to_string(nodes.size() - 1));

    SLLAnimation anim2 =
        GenerateAnimation(0.75, 1, "The head is the only vertex in this List.");
    if (nodes.size() > 1)
        anim2.SetActionDescription("The head has a next node");

    animController->AddAnimation(anim2);
    nodes[0].SetLabel("del");

    if (nodes.size() == 1) {
        SLLAnimation anim3 =
            GenerateAnimation(0.75, 1, "Head points to next (which is null).");
        animController->AddAnimation(anim3);

        SLLAnimation anim4 = GenerateAnimation(
            0.75, 3, "Remove head vertex.\nWe now have an empty List.");
        anim4.SetAnimation([this](GUIVisualizer::SinglyLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& node = srcDS.GetList().front();

            node.SetRadius(AnimationFactory::ElasticOut(1.0f - playingAt) * 20);
            node.SetValueFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
            node.SetLabelFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        visualizer.DeleteNode(0);
        animController->AddAnimation(anim4);

        return;
    }
    nodes[1].SetLabel("head/0");
    nodes[1].AnimationOnNode(true);
    nodes[1].SetNodeState(GUIVisualizer::Node::State::ActiveGreen);
    nodes.back().SetLabel("tail/" + std::to_string(nodes.size() - 2));
    SLLAnimation anim3 =
        GenerateAnimation(0.75, 2, "head points to the next node.");
    anim3.SetAnimation(HighlightArrowFromCur(0));
    animController->AddAnimation(anim3);

    visualizer.SetArrowType(0, ArrowType::Hidden);
    nodes[1].AnimationOnNode(false);
    SLLAnimation anim4 = GenerateAnimation(
        0.75, 3, "Delete del, which was the (previous) head.");
    anim4.SetAnimation([this](GUIVisualizer::SinglyLinkedList srcDS,
                              float playingAt, Vector2 base) {
        auto& nodes = srcDS.GetList();

        nodes[0].SetRadius(AnimationFactory::ElasticOut(1.0f - playingAt) * 20);
        nodes[0].SetValueFontSize(
            AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
        nodes[0].SetLabelFontSize(
            AnimationFactory::ElasticOut(1.0f - playingAt) * 20);

        srcDS.Draw(base, playingAt);

        base.x += srcDS.GetPosition().x;
        base.y += srcDS.GetPosition().y;

        Vector2 start = nodes[0].GetPosition();
        Vector2 end = nodes[1].GetPosition();

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;
        AnimationFactory::DrawDirectionalArrow(start, end, true,
                                               1.0f - playingAt);

        return srcDS;
    });
    animController->AddAnimation(anim4);

    visualizer.DeleteNode(0);
    visualizer.SetPosition(visualizer.GetPosition().x + 60,
                           visualizer.GetPosition().y);

    float length = 40 * visualizer.GetList().size() +
                   20 * (visualizer.GetList().size() - 1);
    float actualPosX = (global::SCREEN_WIDTH - length) / 2;
    SLLAnimation anim5 = GenerateAnimation(
        0.5, -1,
        "Re-layout the Linked List for visualization (not in the actual Linked "
        "List).\nThe whole process is still O(1).");
    anim5.SetAnimation([this, actualPosX](GUIVisualizer::SinglyLinkedList srcDS,
                                          float playingAt, Vector2 base) {
        Vector2 newPos = srcDS.GetPosition();
        newPos.x += (actualPosX - newPos.x) * playingAt;
        srcDS.SetPosition(newPos);

        srcDS.Draw(base, playingAt);

        return srcDS;
    });
    animController->AddAnimation(anim5);

    visualizer.Relayout();
}

void Algorithm::Queue::PeekFront() {
    InitAction({"return head;"});

    auto& nodes = visualizer.GetList();
    SLLAnimation anim =
        GenerateAnimation(0.75, 0,
                          "The current Linked List is empty, the head we "
                          "return will be NULL.");
    if (!nodes.empty()) {
        nodes[0].AnimationOnNode(true);
        nodes[0].SetNodeState(GUIVisualizer::Node::State::Active);
        anim = GenerateAnimation(0.75, 0,
                                 "Return the value stored at the head: " +
                                     std::to_string(nodes[0].GetValue()) + ".");
        nodes[0].SetNodeState(GUIVisualizer::Node::State::Default);
        nodes[0].AnimationOnNode(false);
    }
    animController->AddAnimation(anim);
}

void Algorithm::Queue::PeekBack() {
    InitAction({"return tail;"});

    auto& nodes = visualizer.GetList();
    SLLAnimation anim =
        GenerateAnimation(0.75, 0,
                          "The current Linked List is empty, the tail we "
                          "return will be NULL.");
    if (!nodes.empty()) {
        nodes.back().AnimationOnNode(true);
        nodes.back().SetNodeState(GUIVisualizer::Node::State::Active);
        anim = GenerateAnimation(0.75, 0,
                                 "Return the value stored at the head: " +
                                     std::to_string(nodes[0].GetValue()) + ".");
        nodes.back().SetNodeState(GUIVisualizer::Node::State::Default);
        nodes.back().AnimationOnNode(false);
    }
    animController->AddAnimation(anim);
}

std::function< GUIVisualizer::SinglyLinkedList(GUIVisualizer::SinglyLinkedList,
                                               float, Vector2) >
Algorithm::Queue::HighlightArrowFromCur(int index, bool drawVisualizer,
                                        bool reverse) {
    return [this, index, drawVisualizer, reverse](
               GUIVisualizer::SinglyLinkedList srcDS, float playingAt,
               Vector2 base) {
        auto& nodes = srcDS.GetList();
        if (drawVisualizer) srcDS.Draw(base, playingAt);
        base.x += srcDS.GetPosition().x;
        base.y += srcDS.GetPosition().y;

        Vector2 start = nodes[index].GetPosition();
        Vector2 end = nodes[index + 1].GetPosition();
        if (srcDS.GetArrowType(index + 1) == ArrowType::Skip) {
            if (!(index + 2 < nodes.size())) return srcDS;
            end = nodes[index + 2].GetPosition();
        }

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        if (reverse) playingAt = 1.0f - playingAt;
        AnimationFactory::DrawActiveArrow(start, end, playingAt);
        return srcDS;
    };
}