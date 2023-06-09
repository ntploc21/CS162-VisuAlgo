#include "DoublyLinkedList.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>

#include "Global.hpp"

using ArrowType = GUIVisualizer::LinkedList::ArrowType;

Algorithm::DoublyLinkedList::DoublyLinkedList() {}

Algorithm::DoublyLinkedList::DoublyLinkedList(
    GUIComponent::CodeHighlighter::Ptr codeHighlighter,
    DLLAnimationController::Ptr animController, FontHolder* fonts)
    : Algorithm::Algorithm(codeHighlighter, animController, fonts) {
    Random();
}

Algorithm::DoublyLinkedList::~DoublyLinkedList() {}

std::size_t Algorithm::DoublyLinkedList::size() const {
    return visualizer.size();
}

void Algorithm::DoublyLinkedList::InsertHead(int value) {
    InitAction({"Node *node = new Node(v);", "node->next = head",
                "if(head != nullptr) head->prev = node;", "head = node;"});

    /* Animation goes here */

    visualizer.SetPosition(visualizer.GetPosition().x - 60,
                           visualizer.GetPosition().y);

    GUIVisualizer::Node newNode = visualizer.GenerateNode(value);
    newNode.SetNodeState(GUIVisualizer::Node::Active);
    newNode.AnimationOnNode(true);
    newNode.SetLabel("node");
    {  // Line 1

        visualizer.InsertNode(0, newNode);
        visualizer.SetArrowTypeNext(0, ArrowType::Hidden);
        visualizer.SetArrowTypePrev(0, ArrowType::Hidden);

        DLLAnimation anim1 = GenerateAnimation(
            1, 0,
            "Create new vertex to store value " + std::to_string(value) + ".");
        anim1.SetAnimation([this](GUIVisualizer::DoublyLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            GUIVisualizer::Node& node = srcDS.GetList().at(0);
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        animController->AddAnimation(anim1);
        visualizer.GetList()[0].AnimationOnNode(false);
    }

    {  // Line 2, 3
        if (visualizer.GetList().size() > 1) {
            Vector2 start = visualizer.GetList()[0].GetPosition();
            Vector2 end = visualizer.GetList()[1].GetPosition();

            DLLAnimation anim2 = GenerateAnimation(
                0.5f, 1, "node->next points to the current head.");

            anim2.SetAnimation(
                [this, start, end](GUIVisualizer::DoublyLinkedList srcDS,
                                   float playingAt, Vector2 base) mutable {
                    srcDS.Draw(base, playingAt);
                    base.x += srcDS.GetPosition().x;
                    base.y += srcDS.GetPosition().y;
                    start.x += base.x, end.x += base.x;
                    start.y += base.y, end.y += base.y;

                    AnimationFactory::DrawDoubleActiveArrow(start, end,
                                                            playingAt, 0.0f);

                    return srcDS;
                });
            animController->AddAnimation(anim2);

            DLLAnimation anim3 = GenerateAnimation(
                0.5f, 2, "Current head->prev points to node.");
            anim3.SetAnimation(
                [this, start, end](GUIVisualizer::DoublyLinkedList srcDS,
                                   float playingAt, Vector2 base) mutable {
                    srcDS.Draw(base, playingAt);
                    base.x += srcDS.GetPosition().x;
                    base.y += srcDS.GetPosition().y;

                    start.x += base.x, start.y += base.y;
                    end.x += base.x, end.y += base.y;

                    AnimationFactory::DrawDoubleActiveArrow(start, end, 1.0f,
                                                            playingAt);

                    return srcDS;
                });
            animController->AddAnimation(anim3);

            visualizer.SetArrowTypeNext(0, ArrowType::Active);
            visualizer.SetArrowTypePrev(0, ArrowType::Active);

            visualizer.GetList()[1].ClearLabel();
        } else {
            DLLAnimation anim2 = GenerateAnimation(
                0.5, 1,
                "node->next points to the current head.\nHead is currently "
                "null.");
            animController->AddAnimation(anim2);

            DLLAnimation anim3 = GenerateAnimation(
                0.5, 2,
                "Current head->prev points to node.\nHead is currently "
                "null.");
            animController->AddAnimation(anim3);
        }
    }

    visualizer.GetList()[0].SetLabel("head");
    DLLAnimation anim4 = GenerateAnimation(0.5, 3, "head points to node.");
    animController->AddAnimation(anim4);

    float length = 40 * visualizer.GetList().size() +
                   20 * (visualizer.GetList().size() - 1);
    float actualPosX = (global::SCREEN_WIDTH - length) / 2;
    if (visualizer.GetList().size() == 2) {
        visualizer.GetList().at(1).SetLabel("tail");
    }

    GenerateRelayoutAnimation(
        (Vector2){actualPosX, visualizer.GetPosition().y});

    visualizer.Relayout();
}

void Algorithm::DoublyLinkedList::InsertAfterTail(int value) {
    int prvSize = visualizer.GetList().size();
    if (prvSize == 0) {
        InsertHead(value);
        return;
    }

    InitAction({"Node *node = new Node(v);",
                "tail->next = node, node->prev = tail;", "tail = node;"});

    /* Animation goes here */

    GUIVisualizer::Node newNode = visualizer.GenerateNode(value);
    newNode.SetNodeState(GUIVisualizer::Node::Active);
    newNode.AnimationOnNode(true);
    newNode.SetLabel("node");

    {  // Line 1
        Vector2 pos = visualizer.GetList().back().GetPosition();
        pos.x += 60;
        newNode.SetPosition(pos);

        visualizer.InsertNode(prvSize, newNode);
        visualizer.SetArrowTypeNext(prvSize - 1, ArrowType::Hidden);
        visualizer.SetArrowTypePrev(prvSize - 1, ArrowType::Hidden);

        DLLAnimation anim1 = GenerateAnimation(
            1, 0,
            "Create new vertex to store value " + std::to_string(value) + ".");
        anim1.SetAnimation([this](GUIVisualizer::DoublyLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            GUIVisualizer::Node& node = srcDS.GetList().back();
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        animController->AddAnimation(anim1);
    }

    {  // Line 2
        Vector2 start = visualizer.GetList()[prvSize - 1].GetPosition();
        Vector2 end = visualizer.GetList()[prvSize].GetPosition();

        visualizer.GetList().back().SetNodeState(
            GUIVisualizer::Node::State::Iterated);
        visualizer.GetList()[prvSize - 1].SetNodeState(
            GUIVisualizer::Node::State::Active);
        visualizer.GetList()[prvSize - 1].AnimationOnNode(true);
        DLLAnimation anim2Next =
            GenerateAnimation(0.5, 1,
                              "Current tail->next points to the node.\nAnd "
                              "node->prev points to the tail.");
        anim2Next.SetAnimation(
            [this, start, end](GUIVisualizer::DoublyLinkedList srcDS,
                               float playingAt, Vector2 base) mutable {
                srcDS.Draw(base, playingAt);
                base.x += srcDS.GetPosition().x;
                base.y += srcDS.GetPosition().y;
                start.x += base.x, end.x += base.x;
                start.y += base.y, end.y += base.y;

                AnimationFactory::DrawDoubleActiveArrow(start, end, playingAt,
                                                        0.0f);

                return srcDS;
            });
        animController->AddAnimation(anim2Next);
        visualizer.GetList()[prvSize - 1].AnimationOnNode(false);
        visualizer.GetList()[prvSize].AnimationOnNode(false);

        DLLAnimation anim2Prev =
            GenerateAnimation(0.5, 1,
                              "Current tail->next points to the node.\nAnd "
                              "node->prev points to the tail.");
        anim2Prev.SetAnimation(
            [this, start, end](GUIVisualizer::DoublyLinkedList srcDS,
                               float playingAt, Vector2 base) mutable {
                srcDS.Draw(base, playingAt);
                base.x += srcDS.GetPosition().x;
                base.y += srcDS.GetPosition().y;

                start.x += base.x, start.y += base.y;
                end.x += base.x, end.y += base.y;

                AnimationFactory::DrawDoubleActiveArrow(start, end, 1.0f,
                                                        playingAt);

                return srcDS;
            });
        animController->AddAnimation(anim2Prev);
        visualizer.GetList()[prvSize - 1].AnimationOnNode(true);
        visualizer.GetList()[prvSize].AnimationOnNode(true);

        visualizer.GetList()[prvSize - 1].SetNodeState(
            GUIVisualizer::Node::State::Default);

        visualizer.SetArrowTypeNext(prvSize - 1, ArrowType::Default);
        visualizer.SetArrowTypePrev(prvSize - 1, ArrowType::Default);

        visualizer.GetList()[prvSize - 1].ClearLabel();
        if (prvSize - 1 == 0)
            visualizer.GetList()[prvSize - 1].SetLabel("head");
    }

    visualizer.GetList().back().SetLabel("tail");
    DLLAnimation anim3 =
        GenerateAnimation(0.5, 2,
                          "tail points to node.\nThe whole operation is O(1) "
                          "if we maintain the tail pointer.");
    animController->AddAnimation(anim3);

    visualizer.GetList().back().AnimationOnNode(false);

    float length = 40 * visualizer.GetList().size() +
                   20 * (visualizer.GetList().size() - 1);
    float actualPosX = (global::SCREEN_WIDTH - length) / 2;
    DLLAnimation anim4 = GenerateAnimation(
        0.5, -1,
        "Re-layout the Linked List for visualization (not in the actual Linked "
        "List).\nThe whole process is still O(1).");
    anim4.SetAnimation([this, actualPosX](GUIVisualizer::DoublyLinkedList srcDS,
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

void Algorithm::DoublyLinkedList::InsertMiddle(int index, int value) {
    InitAction({"Node *pre = head;", "for(int k=0;k<i-1;k++)",
                "	pre = pre->next;", "Node *aft = pre->next;",
                "Node *node = new Node(v);",
                "node->next = aft, aft->prev = node;",
                "pre->next = node, node->prev = pre;"});
    /* Animation goes here */
    auto& nodes = visualizer.GetList();
    for (GUIVisualizer::Node& node : nodes) node.AnimationOnNode(true);

    {  // Line 1
        nodes[0].SetNodeState(GUIVisualizer::Node::Active);
        nodes[0].SetLabel("head/pre/0");
        nodes[0].AnimationOnNode(true);
        DLLAnimation anim1 = GenerateAnimation(0.75, 0, "Set pre to head.");
        animController->AddAnimation(anim1);
    }

    nodes[0].AnimationOnNode(false);
    for (int k = 0; k <= index - 1; k++) {
        {  // Line 2
            DLLAnimation animLoop1 = GenerateAnimation(
                0.75, 1, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index - 1)
                animLoop1.SetActionDescription(
                    "We have found the insertion point.\nWe continue the nex "
                    "insertion step.");
            else
                animLoop1.SetAnimation(HighlightArrowNext(k));
            animController->AddAnimation(animLoop1);
        }

        if (k == index - 1) break;

        {  // Line 3
            nodes[k].SetNodeState(GUIVisualizer::Node::Iterated);
            nodes[k].ClearLabel();
            if (k == 0) nodes[k].SetLabel("head");

            nodes[k + 1].SetLabel("pre/" + std::to_string(k + 1));
            nodes[k + 1].SetNodeState(GUIVisualizer::Node::Active);
            nodes[k + 1].AnimationOnNode(true);
            visualizer.SetArrowTypeNext(k, ArrowType::Active);

            DLLAnimation animLoop2 =
                GenerateAnimation(0.75, 2, "We set pre to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    {  // line 4
        nodes[index].SetLabel("aft/" + std::to_string(index));
        nodes[index].SetNodeState(GUIVisualizer::Node::ActiveBlue);
        nodes[index].AnimationOnNode(true);
        DLLAnimation anim4 = GenerateAnimation(
            0.75, 3,
            "The index before insertion point is found.\npre is before the "
            "insertion point and aft is the insertion point.");
        anim4.SetAnimation(HighlightArrowNext(index - 1));
        animController->AddAnimation(anim4);
        visualizer.SetArrowTypeNext(index - 1, ArrowType::Active);
        nodes[index].AnimationOnNode(false);
    }

    GUIVisualizer::Node newNode = visualizer.GenerateNode(value);
    {  // line 5
        newNode.SetNodeState(GUIVisualizer::Node::ActiveGreen);
        newNode.AnimationOnNode(true);
        newNode.SetLabel("node");
        Vector2 newNodePos = nodes[index].GetPosition();
        newNodePos.y += 60;

        visualizer.InsertNode(index, newNode, false);
        visualizer.SetArrowTypeNext(index, ArrowType::Skip);
        visualizer.SetArrowTypePrev(index, ArrowType::Skip);

        nodes[index].SetPosition(newNodePos);

        DLLAnimation anim5 = GenerateAnimation(
            0.75, 4,
            "Create new vertex to store value " + std::to_string(value) + ".");
        animController->AddAnimation(anim5);

        nodes[index].AnimationOnNode(false);
    }

    {  // line 6
        Vector2 start = nodes[index].GetPosition();
        Vector2 end = nodes[index + 1].GetPosition();

        nodes[index].SetLabel("node/" + std::to_string(index));
        nodes[index + 1].SetLabel("aft/" + std::to_string(index + 1));
        DLLAnimation anim6 =
            GenerateAnimation(0.75, 5, "node->next points to aft.");
        anim6.SetAnimation(
            [this, start, end](GUIVisualizer::DoublyLinkedList srcDS,
                               float playingAt, Vector2 base) mutable {
                auto& nodes = srcDS.GetList();
                srcDS.Draw(base, playingAt);

                base.x += srcDS.GetPosition().x;
                base.y += srcDS.GetPosition().y;
                start.x += base.x, start.y += base.y;
                end.x += base.x, end.y += base.y;

                AnimationFactory::DrawDoubleActiveArrow(start, end, playingAt,
                                                        playingAt);
                if (playingAt == 1.0f) {
                    AnimationFactory::DrawDoubleDirectionalArrow(
                        start, end, true, true, 1.0f, 1.0f);
                }
                return srcDS;
            });
        animController->AddAnimation(anim6);
        visualizer.SetArrowTypeNext(index, ArrowType::Active);
        visualizer.SetArrowTypePrev(index, ArrowType::Active);
    }

    {  // line 7
        visualizer.SetArrowTypeNext(index - 1, ArrowType::Hidden);
        visualizer.SetArrowTypePrev(index - 1, ArrowType::Hidden);
        DLLAnimation anim6Next =
            GenerateAnimation(0.75, 6, "pre->next points to node.");
        anim6Next.SetAnimation([this, index](
                                   GUIVisualizer::DoublyLinkedList srcDS,
                                   float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();
            srcDS.Draw(base, playingAt);

            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;
            Vector2 src = nodes[index - 1].GetPosition();
            Vector2 start = nodes[index + 1].GetPosition();
            Vector2 initEnd = nodes[index].GetPosition();
            Vector2 end = nodes[index].GetPosition();
            src.x += base.x, src.y += base.y;
            start.x += base.x, start.y += base.y;
            initEnd.x += base.x, initEnd.y += base.y;
            end.x += base.x, end.y += base.y;

            Vector2 side = (Vector2){end.x - start.x, end.y - start.y};
            end = (Vector2){start.x + side.x * std::min(1.0f, playingAt * 2),
                            start.y + side.y * std::min(1.0f, playingAt * 2)};

            AnimationFactory::DrawDoubleDirectionalArrow(src, end, true, false,
                                                         1.0f, 0.0f);
            if (playingAt >= 0.5f) {
                AnimationFactory::DrawDoubleActiveArrow(src, initEnd, 0.0f,
                                                        (playingAt - 0.5f) * 2);
            }
            return srcDS;
        });
        animController->AddAnimation(anim6Next);
        visualizer.SetArrowTypeNext(index - 1, ArrowType::Active);
        visualizer.SetArrowTypePrev(index - 1, ArrowType::Active);
    }

    {  // Re-layout
        DLLAnimation anim8 =
            GenerateAnimation(0.75, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked "
                              "List).\nThe whole process is still O(1).");
        anim8.SetAnimation([this, index](GUIVisualizer::DoublyLinkedList srcDS,
                                         float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            Vector2 posInserted = nodes[index].GetPosition();
            Vector2 posAfter = nodes[index + 1].GetPosition();

            Vector2 newPosInserted =
                AnimationFactory::MoveNode(posInserted, posAfter, playingAt);
            nodes[index].SetPosition(newPosInserted);

            for (int i = index + 1; i < int(nodes.size()); i++) {
                Vector2 cur = nodes[i].GetPosition();
                Vector2 nxt = cur;
                nxt.x += 60;
                nodes[i].SetPosition(
                    AnimationFactory::MoveNode(cur, nxt, playingAt));
            }
            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        animController->AddAnimation(anim8);

        for (int i = index; i < int(nodes.size()) - 1; i++) {
            nodes[i].SetPosition(nodes[i + 1].GetPosition());
        }
        nodes.back().SetPosition(nodes.back().GetPosition().x + 60,
                                 nodes.back().GetPosition().y);
    }

    {  // Re-layout (center the LL)
        float length = 40 * visualizer.GetList().size() +
                       20 * (visualizer.GetList().size() - 1);
        float actualPosX = (global::SCREEN_WIDTH - length) / 2;
        GenerateRelayoutAnimation(
            (Vector2){actualPosX, visualizer.GetPosition().y});
    }

    visualizer.Relayout();

    for (GUIVisualizer::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUIVisualizer::Node::Default);
    }
    visualizer.ResetArrow();
}

void Algorithm::DoublyLinkedList::DeleteHead() {
    InitAction({"if(head == nullptr) return; // empty, do nothing",
                "Node *del = head;", "head = head->next;", "delete del;",
                "if(head != nullptr) head->prev = nullptr;"});
    auto& nodes = visualizer.GetList();
    if (!nodes.size()) {
        DLLAnimation animNoElement = GenerateAnimation(
            0.75, 0,
            "head is currently NULL, so there is no element to delete.");
        animController->AddAnimation(animNoElement);
        return;
    }
    nodes[0].SetLabel("head/0");
    nodes[0].AnimationOnNode(true);
    nodes[0].SetNodeState(GUIVisualizer::Node::State::Active);
    DLLAnimation anim1 = GenerateAnimation(
        0.75, 0, "head is exist, so we proceed to the next step");
    animController->AddAnimation(anim1);

    nodes[0].AnimationOnNode(false);
    nodes[0].SetLabel("head/del/0");

    if (nodes.size() > 1)

        nodes.back().SetLabel("tail/" + std::to_string(nodes.size() - 1));

    DLLAnimation anim2 =
        GenerateAnimation(0.75, 1, "The head is the only vertex in this List.");
    if (nodes.size() > 1)
        anim2.SetActionDescription("The head has a next node");

    animController->AddAnimation(anim2);
    nodes[0].SetLabel("del");

    if (nodes.size() == 1) {
        DLLAnimation anim3 =
            GenerateAnimation(0.75, 1, "Head points to next (which is null).");
        animController->AddAnimation(anim3);

        DLLAnimation anim4 = GenerateAnimation(
            0.75, 3, "Remove head vertex.\nWe now have an empty List.");
        anim4.SetAnimation([this](GUIVisualizer::DoublyLinkedList srcDS,
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
    DLLAnimation anim3 =
        GenerateAnimation(0.75, 2, "head points to the next node.");
    anim3.SetAnimation(HighlightArrowNext(0));
    animController->AddAnimation(anim3);

    visualizer.SetArrowTypeNext(0, ArrowType::Hidden);
    visualizer.SetArrowTypePrev(0, ArrowType::Hidden);
    nodes[1].AnimationOnNode(false);
    DLLAnimation anim4 = GenerateAnimation(
        0.75, 3, "Delete del, which was the (previous) head.");
    anim4.SetAnimation([this](GUIVisualizer::DoublyLinkedList srcDS,
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
        AnimationFactory::DrawDoubleDirectionalArrow(
            start, end, true, false, 1.0f - playingAt, 1.0f - playingAt);

        return srcDS;
    });
    animController->AddAnimation(anim4);

    visualizer.DeleteNode(0);
    visualizer.SetPosition(visualizer.GetPosition().x + 60,
                           visualizer.GetPosition().y);

    float length = 40 * visualizer.GetList().size() +
                   20 * (visualizer.GetList().size() - 1);
    float actualPosX = (global::SCREEN_WIDTH - length) / 2;
    GenerateRelayoutAnimation(
        (Vector2){actualPosX, visualizer.GetPosition().y});

    visualizer.Relayout();
}

void Algorithm::DoublyLinkedList::DeleteTail() {
    InitAction({"if(head == nullptr) return; // empty, do nothing",
                "Node *del = tail;", "tail = tail->prev;",
                "tail->next = nullptr;", "delete del;"});
    auto& nodes = visualizer.GetList();
    if (nodes.size() <= 1) {
        DeleteHead();
        return;
    }

    {  // Line 1
        nodes[0].SetLabel("head/0");
        // nodes[0].AnimationOnNode(true);
        // nodes[0].SetNodeState(GUIVisualizer::Node::State::Active);
        DLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is exist, so we proceed to the next step");
        animController->AddAnimation(anim1);

        // nodes[0].SetNodeState(GUIVisualizer::Node::State::Default);
    }

    int prvSize = nodes.size();
    {  // Line 2
        nodes[prvSize - 2].SetLabel("tail/" + std::to_string(prvSize - 2));
        if (prvSize - 2 == 0) {
            nodes[prvSize - 2].SetLabel("head/tail/0");
        }

        nodes.back().SetLabel("del");
        nodes.back().AnimationOnNode(true);
        nodes.back().SetNodeState(GUIVisualizer::Node::State::ActiveRed);

        DLLAnimation anim2 =
            GenerateAnimation(0.75, 1, "Set del to (old) tail.");
        animController->AddAnimation(anim2);

        nodes.back().AnimationOnNode(false);
        // nodes[0].AnimationOnNode(false);
    }

    {  // Line 3
        nodes[prvSize - 2].AnimationOnNode(true);
        nodes[prvSize - 2].SetNodeState(
            GUIVisualizer::Node::State::ActiveGreen);
        visualizer.SetArrowTypePrev(prvSize - 2, ArrowType::Hidden);
        DLLAnimation anim3 =
            GenerateAnimation(0.75, 2, "Set tail to tail->prev.");
        anim3.SetAnimation(HighlightArrowPrev(prvSize - 2));
        nodes[prvSize - 2].AnimationOnNode(false);
    }

    {  // Line 4, 5
        visualizer.SetArrowTypeNext(prvSize - 2, ArrowType::Hidden);
        DLLAnimation anim4 = GenerateAnimation(
            0.75, 3,
            "Set the next of (new) tail to null.; Delete tmp.\nThe whole "
            "operations is just O(1) as we can access (old) tail.prev.");
        anim4.SetAnimation([this](GUIVisualizer::DoublyLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            nodes.back().SetRadius(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);
            nodes.back().SetValueFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
            nodes.back().SetLabelFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);

            srcDS.Draw(base, playingAt);

            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            Vector2 start = nodes[nodes.size() - 2].GetPosition();
            Vector2 end = nodes.back().GetPosition();

            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;
            AnimationFactory::DrawDoubleDirectionalArrow(
                start, end, false, true, 1.0f - playingAt, 1.0f - playingAt);

            return srcDS;
        });
        animController->AddAnimation(anim4);
        visualizer.DeleteNode(prvSize);
    }

    float length = 40 * visualizer.GetList().size() +
                   20 * (visualizer.GetList().size() - 1);
    float actualPosX = (global::SCREEN_WIDTH - length) / 2;
    GenerateRelayoutAnimation(
        (Vector2){actualPosX, visualizer.GetPosition().y});

    visualizer.Relayout();
}

void Algorithm::DoublyLinkedList::DeleteMiddle(int index) {
    InitAction(
        {"if(head == nullptr) return; // empty, do nothing",
         "Node *pre = head;", "for(int k=0;k<i-1;k++)",
         "	pre = pre->next;", "Node *del = pre->next, *aft = del->next;",
         " pre->next = aft, aft->prev = pre;  // bypass del", "delete del;"});

    /* Animation goes here */
    auto& nodes = visualizer.GetList();

    if (!nodes.size()) {
        DLLAnimation animNoElement = GenerateAnimation(
            0.75, 0,
            "head is currently NULL, so there is no element to delete.");
        animController->AddAnimation(animNoElement);
        return;
    }

    for (GUIVisualizer::Node& node : nodes) node.AnimationOnNode(true);

    {  // Line 1
        nodes[0].SetLabel("head/0");
        nodes[0].SetNodeState(GUIVisualizer::Node::State::Active);
        DLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is exist, so we proceed to the next step");
        animController->AddAnimation(anim1);
        nodes[0].AnimationOnNode(false);
    }

    {  // Line 2
        nodes[0].SetLabel("head/pre/0");
        DLLAnimation anim1 =
            GenerateAnimation(0.75, 1,
                              "Set prev to head.\nPointer prev will stop at "
                              "one vertex before the deleted vertex.");
        animController->AddAnimation(anim1);
    }

    nodes[0].AnimationOnNode(false);
    for (int k = 0; k <= index - 1; k++) {
        {  // Line 3
            DLLAnimation animLoop1 = GenerateAnimation(
                0.75, 2,
                "Increment k, index specified has not been reached.\nk: " +
                    std::to_string(k) + ".");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index - 1)
                animLoop1.SetActionDescription(
                    "k is " + std::to_string(k) +
                    ", prev now points to one vertex behind the vertex "
                    "to-be-deleted.\nWe stop searching and continue with the "
                    "removal.");
            else
                animLoop1.SetAnimation(HighlightArrowNext(k));
            animController->AddAnimation(animLoop1);
        }

        if (k == index - 1) break;

        {  // Line 4
            nodes[k].SetNodeState(GUIVisualizer::Node::Iterated);
            nodes[k].ClearLabel();
            if (k == 0) nodes[k].SetLabel("head");

            nodes[k + 1].SetLabel("pre/" + std::to_string(k + 1));
            nodes[k + 1].SetNodeState(GUIVisualizer::Node::Active);
            nodes[k + 1].AnimationOnNode(true);
            visualizer.SetArrowTypeNext(k, ArrowType::Active);

            DLLAnimation animLoop2 = GenerateAnimation(
                0.75, 3, "Pointer pre advances to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    {  // Line 5
        nodes[index].SetLabel("del/" + std::to_string(index));
        nodes[index].SetNodeState(GUIVisualizer::Node::State::ActiveRed);
        DLLAnimation anim5 = GenerateAnimation(
            0.75, 4,
            "We store reference to the vertex to-be-deleted.\nWe also store "
            "reference to the vertex after the to-be-deleted vertex.");
        anim5.SetAnimation(HighlightArrowNext(index - 1));
        visualizer.SetArrowTypeNext(index - 1, ArrowType::Active);
        nodes[index].AnimationOnNode(false);

        nodes[index + 1].SetLabel("aft/" + std::to_string(index + 1));
        nodes[index + 1].SetNodeState(GUIVisualizer::Node::State::ActiveGreen);
        if (index + 1 == nodes.size() - 1)
            nodes[index + 1].SetLabel("tail/aft/" + std::to_string(index + 1));

        DLLAnimation anim5_2 = GenerateAnimation(
            0.75, 4,
            "We store reference to the vertex to-be-deleted.\nWe also store "
            "reference to the vertex after the to-be-deleted vertex.");
        anim5_2.SetAnimation(HighlightArrowNext(index));

        animController->AddAnimation(anim5);
        animController->AddAnimation(anim5_2);
    }

    {  // Line 6
        nodes[index + 1].AnimationOnNode(false);
        visualizer.SetArrowTypeNext(index - 1, ArrowType::Hidden);
        visualizer.SetArrowTypePrev(index - 1, ArrowType::Hidden);
        visualizer.SetArrowTypeNext(index, ArrowType::Skip);
        visualizer.SetArrowTypePrev(index, ArrowType::Skip);

        DLLAnimation anim6 =
            GenerateAnimation(1.50, 5,
                              "We connect the vertex behind the vertex "
                              "to-be-deleted (pointer prev) "
                              "with the next vertex after the vertex "
                              "to-be-deleted (pointer after).");
        anim6.SetAnimation([this, index](GUIVisualizer::DoublyLinkedList srcDS,
                                         float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            Vector2 beforeStart = nodes[index - 1].GetPosition();
            Vector2 start = nodes[index].GetPosition();
            Vector2 end = nodes[index + 1].GetPosition();
            Vector2 end2 = AnimationFactory::MoveNode(
                start, end, std::max(0.0f, (playingAt - 0.5f) * 2));
            start = AnimationFactory::MoveNode(start,
                                               (Vector2){start.x, start.y - 60},
                                               std::min(playingAt * 2, 1.0f));
            nodes[index].SetPosition(start.x, start.y);

            srcDS.Draw(base, playingAt);
            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            beforeStart.x += base.x, beforeStart.y += base.y;
            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;
            end2.x += base.x, end2.y += base.y;

            AnimationFactory::DrawDoubleActiveArrow(beforeStart, end2, 1.0f,
                                                    0.0f);
            AnimationFactory::DrawDoubleDirectionalArrow(
                beforeStart, end2, false, false, 0.0f, 1.0f);
            AnimationFactory::DrawDoubleDirectionalArrow(start, end, true, true,
                                                         1.0f, 1.0f);

            return srcDS;
        });
        animController->AddAnimation(anim6);

        visualizer.SetArrowTypePrev(index - 1, ArrowType::Default);
        visualizer.SetArrowTypeNext(index - 1, ArrowType::Active);
        nodes[index].SetPosition(nodes[index].GetPosition().x,
                                 nodes[index].GetPosition().y - 60);
    }

    {  // Line 7
        nodes[index + 1].SetLabel("aft/" + std::to_string(index));
        if (index + 1 == nodes.size() - 1)
            nodes[index + 1].SetLabel("tail/aft/" + std::to_string(index));
        DLLAnimation anim7 =
            GenerateAnimation(0.75, 6, "Now we delete this vertex.");
        anim7.SetAnimation([this, index](GUIVisualizer::DoublyLinkedList srcDS,
                                         float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            nodes[index].SetRadius(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);
            nodes[index].SetValueFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
            nodes[index].SetLabelFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);

            srcDS.Draw(base, playingAt);

            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            Vector2 start = nodes[index].GetPosition();
            Vector2 end = nodes[index + 1].GetPosition();

            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;
            AnimationFactory::DrawDoubleDirectionalArrow(
                start, end, true, true, 1.0f - playingAt, 1.0f - playingAt);

            return srcDS;
        });
        animController->AddAnimation(anim7);
        visualizer.DeleteNode(index, false);
    }

    {  // Re-layout
        DLLAnimation anim8 =
            GenerateAnimation(0.75, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked List).\nThe whole "
                              "process is still O(1).");
        anim8.SetAnimation([this, index](GUIVisualizer::DoublyLinkedList srcDS,
                                         float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            for (int i = index; i < int(nodes.size()); i++) {
                Vector2 cur = nodes[i].GetPosition();
                Vector2 nxt = cur;
                nxt.x -= 60;
                nodes[i].SetPosition(
                    AnimationFactory::MoveNode(cur, nxt, playingAt));
            }
            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        animController->AddAnimation(anim8);

        for (int i = index; i < int(nodes.size()); i++) {
            nodes[i].SetPosition(nodes[i].GetPosition().x - 60,
                                 nodes[i].GetPosition().y);
        }
    }

    {  // Re-layout (center the LL)
        float length = 40 * visualizer.GetList().size() +
                       20 * (visualizer.GetList().size() - 1);
        float actualPosX = (global::SCREEN_WIDTH - length) / 2;
        GenerateRelayoutAnimation(
            (Vector2){actualPosX, visualizer.GetPosition().y});
    }

    visualizer.Relayout();
    ResetVisualizer();
}

void Algorithm::DoublyLinkedList::Update(int index, int value) {
    InitAction({"if(head == nullptr) return; // NO_ELEMENT",
                "Node *cur = head;", "for(int k=0;k<i;k++)",
                "	cur = cur->next;", "cur->value = v;"});
    /* Animation goes here */
    auto& nodes = visualizer.GetList();

    if (!nodes.size()) {
        DLLAnimation animNoElement = GenerateAnimation(
            0.75, 0,
            "head is currently NULL, so there is no element to update.");
        animController->AddAnimation(animNoElement);
        return;
    }
    {  // Line 1
        nodes[0].SetNodeState(GUIVisualizer::Node::Active);
        nodes[0].SetLabel("head/0");
        nodes[0].AnimationOnNode(true);
        DLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is currently NOT NULL, proceed to the next line.");
        animController->AddAnimation(anim1);
        nodes[0].AnimationOnNode(false);
    }

    {  // Line 2
        // nodes[0].SetNodeState(GUIVisualizer::Node::Active);
        nodes[0].SetLabel("head/cur/0");
        DLLAnimation anim2 = GenerateAnimation(0.75, 1, "Set cur to head.");
        animController->AddAnimation(anim2);
    }

    if (index == 0) {
        DLLAnimation animNoLoop =
            GenerateAnimation(0.75, 1,
                              "We are already at the point we want to update "
                              "(head).\nProceed to update the head.");
    }

    for (int k = 0; k <= index; k++) {
        {  // Line 2
            DLLAnimation animLoop1 = GenerateAnimation(
                0.75, 2, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index)
                animLoop1.SetActionDescription(
                    "We have found the point we want to update.\nWe will exit "
                    "the for-loop.");
            else
                animLoop1.SetAnimation(HighlightArrowNext(k));
            animController->AddAnimation(animLoop1);
        }

        if (k == index) break;

        {  // Line 3
            nodes[k].SetNodeState(GUIVisualizer::Node::Iterated);
            nodes[k].ClearLabel();
            if (k == 0) nodes[k].SetLabel("head");

            nodes[k + 1].SetLabel("cur/" + std::to_string(k + 1));
            nodes[k + 1].SetNodeState(GUIVisualizer::Node::Active);
            nodes[k + 1].AnimationOnNode(true);
            visualizer.SetArrowTypeNext(k, ArrowType::Active);

            DLLAnimation animLoop2 =
                GenerateAnimation(0.75, 3, "We set cur to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    // nodes[index].AnimationOnNode(true);
    nodes[index].SetNodeState(GUIVisualizer::Node::ActiveGreen);
    DLLAnimation animFocusNode =
        GenerateAnimation(0.75, 4,
                          "Updating node " + std::to_string(index) +
                              "'s value to " + std::to_string(value));
    animController->AddAnimation(animFocusNode);

    nodes[index].AnimationOnNode(false);
    nodes[index].SetValue(value);
    DLLAnimation animFinal =
        GenerateAnimation(0.75, 4,
                          "Updated node " + std::to_string(index) +
                              "'s value to " + std::to_string(value) + "!");
    animController->AddAnimation(animFinal);
}

void Algorithm::DoublyLinkedList::Search(int value) {
    InitAction({"Node *cur = head;", "while(cur != nullptr) {",
                "	if(cur->value == v) return cur;",
                "	cur = cur->next;", "}",
                "return nullptr; // NOT_FOUND"});

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
    for (GUIVisualizer::Node& node : nodes) node.AnimationOnNode(true);

    nodes[0].SetNodeState(GUIVisualizer::Node::Active);
    nodes[0].SetLabel("head/cur/0");
    DLLAnimation anim1 = GenerateAnimation(0.5, 0, "Set cur to head.");
    animController->AddAnimation(anim1);

    int i = 0;
    bool found = false;
    do {
        nodes[i].AnimationOnNode(false);
        DLLAnimation animLoop1 =
            GenerateAnimation(0.5, 1, "Check whether the current node is NULL");
        animController->AddAnimation(animLoop1);
        if (i == nodes.size()) break;
        DLLAnimation animLoop2 = GenerateAnimation(
            1, 2, "Check if the current node's value is equal to v");
        DLLAnimation animLoop3;
        if (nodes[i].GetValue() == value) {
            animLoop3 = GenerateAnimation(
                0.5, 2,
                "Found value v = " + std::to_string(value) +
                    " at this highlighted vertex so we return node at index " +
                    std::to_string(i) + ".\nThe whole operation is O(N)");
            found = true;
            nodes[i].ClearLabel();
            if (i == 0)
                nodes[i].SetLabel("head");
            else if (i + 1 == nodes.size())
                nodes[i].SetLabel("tail");
        } else {
            nodes[i].AnimationOnNode(true);
            nodes[i].SetNodeState(GUIVisualizer::Node::Iterated);
            if (i == 0)
                nodes[i].SetLabel("head");
            else if (i + 1 == nodes.size())
                nodes[i].SetLabel("tail");
            else
                nodes[i].ClearLabel();

            if (i + 1 < nodes.size()) {
                nodes[i + 1].SetNodeState(GUIVisualizer::Node::Active);
                if (i + 1 == nodes.size() - 1)
                    nodes[i + 1].SetLabel("tail/cur/" + std::to_string(i + 1));
                else
                    nodes[i + 1].SetLabel("cur/" + std::to_string(i + 1));
            }
            animLoop3 = GenerateAnimation(0.5, 3, "Advance to the next node");

            if (i + 1 < nodes.size()) {
                animLoop3.SetAnimation(HighlightArrowNext(i));
                visualizer.SetArrowTypeNext(i, ArrowType::Active);
            }
        }
        animController->AddAnimation(animLoop2);
        animController->AddAnimation(animLoop3);
        nodes[i].AnimationOnNode(false);
    } while (!found && ++i);

    if (!found) {
        DLLAnimation animNotFound = GenerateAnimation(
            0.5, 5,
            "cur is null (we have gone past the tail after O(N) step(s)).\n"
            "We can conclude that value v = " +
                std::to_string(value) + " is NOT FOUND in the Linked List");
        animController->AddAnimation(animNotFound);
    }

    for (GUIVisualizer::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUIVisualizer::Node::Default);
    }
    visualizer.ResetArrow();
}

std::function< GUIVisualizer::DoublyLinkedList(GUIVisualizer::DoublyLinkedList,
                                               float, Vector2) >
Algorithm::DoublyLinkedList::HighlightArrowNext(int index, bool drawVisualizer,
                                                bool reverse) {
    return [this, index, drawVisualizer, reverse](
               GUIVisualizer::DoublyLinkedList srcDS, float playingAt,
               Vector2 base) {
        auto& nodes = srcDS.GetList();
        if (drawVisualizer) srcDS.Draw(base, playingAt);
        base.x += srcDS.GetPosition().x;
        base.y += srcDS.GetPosition().y;

        Vector2 start = nodes[index].GetPosition();
        int nextIndex;
        for (nextIndex = index + 1; nextIndex < nodes.size(); nextIndex++)
            if (nodes[nextIndex].GetNodeState() ==
                    GUIVisualizer::Node::State::Hide ||
                (srcDS.GetArrowTypeNext(nextIndex) != ArrowType::Skip ||
                 srcDS.GetArrowTypePrev(nextIndex) != ArrowType::Skip))
                break;

        if (nextIndex == nodes.size())
            return srcDS;  // all of the nodes behind the current node is
                           // hidden, so we don't need to draw any arrow
        Vector2 end = nodes[nextIndex].GetPosition();

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        if (reverse) playingAt = 1.0f - playingAt;
        // ArrowType arrowNext = srcDS.GetArrowTypeNext(index);
        ArrowType arrowPrev = srcDS.GetArrowTypePrev(index);

        // float lengthNext = (arrowNext == ArrowType::Hidden ? 0.0f :
        // playingAt);
        float lengthPrev = (arrowPrev == ArrowType::Hidden ? 0.0f : 1.0f);

        AnimationFactory::DrawDoubleDirectionalArrow(
            start, end, false, arrowPrev == ArrowType::Active, 0.0f,
            lengthPrev);

        AnimationFactory::DrawDoubleActiveArrow(start, end, playingAt, 0.0f);
        return srcDS;
    };
}

std::function< GUIVisualizer::DoublyLinkedList(GUIVisualizer::DoublyLinkedList,
                                               float, Vector2) >
Algorithm::DoublyLinkedList::HighlightArrowPrev(int index, bool drawVisualizer,
                                                bool reverse) {
    return [this, index, drawVisualizer, reverse](
               GUIVisualizer::DoublyLinkedList srcDS, float playingAt,
               Vector2 base) {
        auto& nodes = srcDS.GetList();
        if (drawVisualizer) srcDS.Draw(base, playingAt);
        base.x += srcDS.GetPosition().x;
        base.y += srcDS.GetPosition().y;

        Vector2 start = nodes[index].GetPosition();
        int nextIndex;
        for (nextIndex = index + 1; nextIndex < nodes.size(); nextIndex++)
            if (nodes[nextIndex].GetNodeState() ==
                    GUIVisualizer::Node::State::Hide ||
                (srcDS.GetArrowTypeNext(nextIndex) != ArrowType::Skip ||
                 srcDS.GetArrowTypePrev(nextIndex) != ArrowType::Skip))
                break;

        if (nextIndex == nodes.size())
            return srcDS;  // all of the nodes behind the current node is
                           // hidden, so we don't need to draw any arrow
        Vector2 end = nodes[nextIndex].GetPosition();

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        if (reverse) playingAt = 1.0f - playingAt;
        ArrowType arrowNext = srcDS.GetArrowTypeNext(index);
        // ArrowType arrowPrev = srcDS.GetArrowTypePrev(index);

        float lengthNext = (arrowNext == ArrowType::Hidden ? 0.0f : 1.0f);
        // float lengthPrev = (arrowPrev == ArrowType::Hidden ? 0.0f :
        // playingAt);

        AnimationFactory::DrawDoubleDirectionalArrow(
            start, end, arrowNext == ArrowType::Active, false, lengthNext,
            0.0f);

        AnimationFactory::DrawDoubleActiveArrow(start, end, 0.0f, playingAt);
        return srcDS;
    };
}

std::function< GUIVisualizer::DoublyLinkedList(GUIVisualizer::DoublyLinkedList,
                                               float, Vector2) >
Algorithm::DoublyLinkedList::HighlightArrowBoth(int index, bool drawVisualizer,
                                                bool reverse) {
    return [this, index, drawVisualizer, reverse](
               GUIVisualizer::DoublyLinkedList srcDS, float playingAt,
               Vector2 base) {
        auto& nodes = srcDS.GetList();
        if (drawVisualizer) srcDS.Draw(base, playingAt);
        base.x += srcDS.GetPosition().x;
        base.y += srcDS.GetPosition().y;

        Vector2 start = nodes[index].GetPosition();
        int nextIndex;
        for (nextIndex = index + 1; nextIndex < nodes.size(); nextIndex++)
            if (nodes[nextIndex].GetNodeState() ==
                    GUIVisualizer::Node::State::Hide ||
                (srcDS.GetArrowTypeNext(nextIndex) != ArrowType::Skip ||
                 srcDS.GetArrowTypePrev(nextIndex) != ArrowType::Skip))
                break;

        if (nextIndex == nodes.size())
            return srcDS;  // all of the nodes behind the current node is
                           // hidden, so we don't need to draw any arrow
        Vector2 end = nodes[nextIndex].GetPosition();

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        if (reverse) playingAt = 1.0f - playingAt;

        AnimationFactory::DrawDoubleActiveArrow(start, end, playingAt,
                                                playingAt);
        return srcDS;
    };
}

void Algorithm::DoublyLinkedList::ResetVisualizer() {
    auto& nodes = visualizer.GetList();
    for (GUIVisualizer::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUIVisualizer::Node::Default);
    }
    visualizer.ResetArrow();
}
