#include "CircularLinkedList.hpp"

#include <algorithm>
#include <cstring>
#include <iomanip>

#include "Global.hpp"

using ArrowType = GUI::LinkedList::ArrowType;

Algorithm::CircularLinkedList::CircularLinkedList() {}

Algorithm::CircularLinkedList::CircularLinkedList(
    GUI::CodeHighlighter::Ptr codeHighlighter,
    CLLAnimationController::Ptr animController, FontHolder* fonts)
    : Algorithm::Algorithm(codeHighlighter, animController, fonts) {
    Random();
}

Algorithm::CircularLinkedList::~CircularLinkedList() {}

void Algorithm::CircularLinkedList::InsertHead(int value) {
    auto& nodes = visualizer.GetList();
    if (nodes.size() == maxN) return;
    InitAction({"Node *node = new Node(v);", "node->next = head;",
                "head = node;", "if(tail == nullptr) head->next = head;",
                "else tail->next = head;"});

    /* Animation goes here */

    // visualizer.SetPosition(visualizer.GetPosition().x - 60,
    //                        visualizer.GetPosition().y);

    if (nodes.empty()) {
        visualizer.SetCircularArrowType(ArrowType::Hidden);
    }
    GUI::Node newNode = visualizer.GenerateNode(value);
    newNode.SetPosition((Vector2){0, -60});
    newNode.SetNodeState(GUI::Node::Active);
    newNode.AnimationOnNode(true);
    newNode.SetLabel("node");

    visualizer.InsertNode(0, newNode, false);

    if (nodes.size() > 1) {
        visualizer.SetCircularEnds(1, nodes.size() - 1);
    }

    visualizer.SetArrowType(0, ArrowType::Hidden);

    CLLAnimation anim1 = GenerateAnimation(
        1, 0,
        "Create new vertex to store value " + std::to_string(value) + ".");
    anim1.SetAnimation(
        [this](GUI::CircularLinkedList srcDS, float playingAt, Vector2 base) {
            GUI::Node& node = srcDS.GetList().at(0);
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
    animController->AddAnimation(anim1);
    nodes[0].AnimationOnNode(false);

    CLLAnimation anim2 =
        GenerateAnimation(0.5, 1, "node->next points to the current head.");
    if (nodes.size() > 1) {
        anim2.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
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

        nodes[1].ClearLabel();
    } else
        anim2.SetActionDescription(
            "node->next points to the current head.\nHead is currently null.");
    animController->AddAnimation(anim2);

    {  // Line 3
        nodes[0].SetLabel("head");
        CLLAnimation anim3 = GenerateAnimation(0.5, 2, "head points to node.");
        animController->AddAnimation(anim3);
    }

    {  // Line 4
        if (nodes.size() == 1) {
            CLLAnimation anim4 =
                GenerateAnimation(0.5, 3,
                                  "tail = NULL, so the current circular linked "
                                  "list only have one element.");
            anim4.SetAnimation(HighlightCircularArrow());
            animController->AddAnimation(anim4);
            visualizer.SetCircularArrowType(ArrowType::Default);
            visualizer.SetCircularEnds(0, 0);
        } else {
            visualizer.SetCircularArrowType(ArrowType::Hidden);
            CLLAnimation anim4 =
                GenerateAnimation(0.5, 3,
                                  "tail <> NULL, we will move our tail->next "
                                  "to point to the current head.");
            anim4.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                      float playingAt, Vector2 base) {
                srcDS.Draw(base, playingAt);
                base.x += srcDS.GetPosition().x;
                base.y += srcDS.GetPosition().y;

                auto& nodes = srcDS.GetList();
                Vector2 start = nodes.back().GetPosition();
                Vector2 from = nodes[1].GetPosition();
                Vector2 to = nodes.front().GetPosition();
                start.x += base.x, start.y += base.y;
                from.x += base.x, from.y += base.y;
                to.x += base.x, to.y += base.y;

                AnimationFactory::DrawCircularArrow(
                    AnimationFactory::MoveNode(from, to, playingAt), start,
                    false, 1.0f);

                return srcDS;
            });
            animController->AddAnimation(anim4);

            visualizer.SetCircularArrowType(ArrowType::Default);
            visualizer.SetCircularEnds(0, nodes.size() - 1);
        }
    }

    {  // Re-layout
        CLLAnimation anim8 =
            GenerateAnimation(0.75, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked "
                              "List).\nThe whole process is still O(1).");
        anim8.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            Vector2 posInserted = nodes[0].GetPosition();
            Vector2 posAfter = posInserted;
            posAfter.y += 60;

            Vector2 newPosInserted =
                AnimationFactory::MoveNode(posInserted, posAfter, playingAt);
            nodes[0].SetPosition(newPosInserted);

            for (int i = 1; i < int(nodes.size()); i++) {
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

        for (int i = 0; i < int(nodes.size()) - 1; i++) {
            nodes[i].SetPosition(nodes[i + 1].GetPosition());
        }
        if (nodes.size() > 1) {
            nodes.back().SetPosition(nodes.back().GetPosition().x + 60,
                                     nodes.back().GetPosition().y);
        } else
            nodes.back().SetPosition(nodes.back().GetPosition().x,
                                     nodes.back().GetPosition().y + 60);
    }

    {  // Relayout
        float length = 40 * visualizer.GetList().size() +
                       20 * (visualizer.GetList().size() - 1);
        float actualPosX = (global::SCREEN_WIDTH - length) / 2;
        GenerateRelayoutAnimation(
            (Vector2){actualPosX, visualizer.GetPosition().y});
        visualizer.Relayout();
    }
    ResetVisualizer();
}

void Algorithm::CircularLinkedList::InsertAfterTail(int value) {
    auto& nodes = visualizer.GetList();
    int prvSize = nodes.size();
    if (prvSize == 0) {
        InsertHead(value);
        return;
    }
    if (prvSize == maxN) return;
    if (nodes.size() == maxN) return;

    InitAction({"Node *node = new Node(v);", "tail->next = node;",
                "tail = node;", "tail->next = head;"});

    /* Animation goes here */

    GUI::Node newNode = visualizer.GenerateNode(value);
    newNode.SetNodeState(GUI::Node::Active);
    newNode.AnimationOnNode(true);
    newNode.SetLabel("node");

    Vector2 pos = nodes.back().GetPosition();
    pos.y -= 60;
    newNode.SetPosition(pos);

    {  // Line 1
        visualizer.InsertNode(prvSize, newNode, false);
        visualizer.SetCircularEnds(0, prvSize - 1);
        visualizer.SetArrowType(prvSize - 1, ArrowType::Hidden);

        CLLAnimation anim1 = GenerateAnimation(
            1, 0,
            "Create new vertex to store value " + std::to_string(value) + ".");
        anim1.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            GUI::Node& node = srcDS.GetList().back();
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        animController->AddAnimation(anim1);
    }

    {  // Line 2
        nodes.back().SetNodeState(GUI::Node::State::Iterated);
        nodes[prvSize - 1].SetNodeState(GUI::Node::State::Active);
        nodes[prvSize - 1].AnimationOnNode(true);
        visualizer.SetCircularArrowType(ArrowType::Hidden);

        CLLAnimation anim2 =
            GenerateAnimation(1, 1, "Current tail->next points to the node.");
        anim2.SetAnimation([this, prvSize](GUI::CircularLinkedList srcDS,
                                           float playingAt, Vector2 base) {
            srcDS.Draw(base, playingAt);
            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            Vector2 startCircular = srcDS.GetList().front().GetPosition();
            Vector2 start = srcDS.GetList()[prvSize - 1].GetPosition();
            Vector2 end = srcDS.GetList()[prvSize].GetPosition();
            startCircular.x += base.x, startCircular.y += base.y;
            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;

            AnimationFactory::DrawActiveArrow(start, end, playingAt);
            AnimationFactory::DrawCircularArrow(startCircular, start, false,
                                                1.0f - playingAt);

            return srcDS;
        });
        visualizer.SetArrowType(prvSize - 1, ArrowType::Default);

        nodes[prvSize - 1].SetNodeState(GUI::Node::State::Default);
        nodes[prvSize - 1].ClearLabel();
        if (prvSize - 1 == 0) nodes[prvSize - 1].SetLabel("head");
        animController->AddAnimation(anim2);
    }

    {  // Line 3
        nodes.back().SetLabel("tail");
        CLLAnimation anim3 = GenerateAnimation(
            0.5, 2,
            "tail points to node.\nThe whole operation is O(1) "
            "if we maintain the tail pointer.");
        animController->AddAnimation(anim3);

        nodes.back().AnimationOnNode(false);
    }

    {  // Line 4
        visualizer.SetCircularEnds(0, nodes.size() - 1);
        CLLAnimation anim4 = GenerateAnimation(
            0.5, 3,
            "As the tail points to node, we will move our tail->next "
            "to point to the current head.");
        anim4.SetAnimation(HighlightCircularArrow());
        animController->AddAnimation(anim4);
        visualizer.SetCircularArrowType(ArrowType::Default);

        visualizer.SetCircularArrowType(ArrowType::Default);
        visualizer.SetCircularEnds(0, nodes.size() - 1);
    }

    {  // Re-layout
        CLLAnimation anim8 =
            GenerateAnimation(0.75, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked "
                              "List).\nThe whole process is still O(1).");
        anim8.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            Vector2 posInserted = nodes.back().GetPosition();
            Vector2 posAfter = posInserted;
            posAfter.y += 60;
            posAfter.x += 60;

            Vector2 newPosInserted =
                AnimationFactory::MoveNode(posInserted, posAfter, playingAt);
            nodes.back().SetPosition(newPosInserted);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
        animController->AddAnimation(anim8);

        nodes.back().SetPosition(nodes.back().GetPosition().x + 60,
                                 nodes.back().GetPosition().y + 60);
    }

    {  // Relayout
        float length = 40 * visualizer.GetList().size() +
                       20 * (visualizer.GetList().size() - 1);
        float actualPosX = (global::SCREEN_WIDTH - length) / 2;
        GenerateRelayoutAnimation(
            (Vector2){actualPosX, visualizer.GetPosition().y});
        visualizer.Relayout();
    }
    ResetVisualizer();
}

void Algorithm::CircularLinkedList::InsertMiddle(int index, int value) {
    if (!(index >= 1 && index < visualizer.GetList().size())) return;
    if (visualizer.GetList().size() == maxN) return;
    InitAction({"Node *pre = head;", "for(int k=0;k<i-1;k++)",
                "	pre = pre->next;", "Node *aft = pre->next;",
                "Node *node = new Node(v);", "node->next = aft;",
                "pre->next = node;"});
    /* Animation goes here */
    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) node.AnimationOnNode(true);

    {  // Line 1
        nodes[0].SetNodeState(GUI::Node::Active);
        nodes[0].SetLabel("head/pre/0");
        nodes[0].AnimationOnNode(true);
        CLLAnimation anim1 = GenerateAnimation(0.75, 0, "Set pre to head.");
        animController->AddAnimation(anim1);
    }

    nodes[0].AnimationOnNode(false);
    for (int k = 0; k <= index - 1; k++) {
        {  // Line 2
            CLLAnimation animLoop1 = GenerateAnimation(
                0.75, 1, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index - 1)
                animLoop1.SetActionDescription(
                    "We have found the insertion point.\nWe continue the "
                    "next "
                    "insertion step.");
            else
                animLoop1.SetAnimation(HighlightArrowFromCur(k));
            animController->AddAnimation(animLoop1);
        }

        if (k == index - 1) break;

        {  // Line 3
            nodes[k].SetNodeState(GUI::Node::Iterated);
            nodes[k].ClearLabel();
            if (k == 0) nodes[k].SetLabel("head");

            nodes[k + 1].SetLabel("pre/" + std::to_string(k + 1));
            nodes[k + 1].SetNodeState(GUI::Node::Active);
            nodes[k + 1].AnimationOnNode(true);
            visualizer.SetArrowType(k, ArrowType::Active);

            CLLAnimation animLoop2 =
                GenerateAnimation(0.75, 2, "We set pre to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    {  // line 4
        nodes[index].SetLabel("aft/" + std::to_string(index));
        nodes[index].SetNodeState(GUI::Node::ActiveBlue);
        nodes[index].AnimationOnNode(true);
        CLLAnimation anim4 = GenerateAnimation(
            0.75, 3,
            "The index before insertion point is found.\npre is before the "
            "insertion point and aft is the insertion point.");
        anim4.SetAnimation(HighlightArrowFromCur(index - 1));
        animController->AddAnimation(anim4);
        visualizer.SetArrowType(index - 1, ArrowType::Active);
        nodes[index].AnimationOnNode(false);
    }

    GUI::Node newNode = visualizer.GenerateNode(value);
    {  // line 5
        newNode.SetNodeState(GUI::Node::ActiveGreen);
        newNode.AnimationOnNode(true);
        newNode.SetLabel("node");
        Vector2 newNodePos = nodes[index].GetPosition();
        newNodePos.y -= 60;

        visualizer.InsertNode(index, newNode, false);
        visualizer.SetArrowType(index, ArrowType::Skip);

        nodes[index].SetPosition(newNodePos);

        CLLAnimation anim5 = GenerateAnimation(
            0.75, 4,
            "Create new vertex to store value " + std::to_string(value) + ".");
        animController->AddAnimation(anim5);

        nodes[index].AnimationOnNode(false);
    }

    {  // line 6
        nodes[index].SetLabel("node/" + std::to_string(index));
        nodes[index + 1].SetLabel("aft/" + std::to_string(index + 1));
        CLLAnimation anim6 =
            GenerateAnimation(0.75, 5, "node->next points to aft.");
        anim6.SetAnimation([this, index](GUI::CircularLinkedList srcDS,
                                         float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();
            srcDS.Draw(base, playingAt);

            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            Vector2 start = nodes[index].GetPosition();
            Vector2 end = nodes[index + 1].GetPosition();
            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;

            AnimationFactory::DrawActiveArrow(start, end, playingAt);
            if (playingAt == 1.0f) {
                AnimationFactory::DrawDirectionalArrow(start, end, true, 1.0f);
            }
            return srcDS;
        });
        animController->AddAnimation(anim6);
        visualizer.SetArrowType(index, ArrowType::Active);
    }

    {  // line 7
        visualizer.SetArrowType(index - 1, ArrowType::Hidden);
        CLLAnimation anim7 =
            GenerateAnimation(0.75, 5, "pre->next points to node.");
        anim7.SetAnimation([this, index](GUI::CircularLinkedList srcDS,
                                         float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();
            srcDS.Draw(base, playingAt);

            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            Vector2 src = nodes[index - 1].GetPosition();
            Vector2 start = nodes[index + 1].GetPosition();
            Vector2 end = nodes[index].GetPosition();
            src.x += base.x, src.y += base.y;
            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;

            Vector2 side = (Vector2){end.x - start.x, end.y - start.y};
            end = (Vector2){start.x + side.x * playingAt,
                            start.y + side.y * playingAt};

            AnimationFactory::DrawDirectionalArrow(src, end, true, 1.0f);

            return srcDS;
        });
        animController->AddAnimation(anim7);
        visualizer.SetArrowType(index - 1, ArrowType::Active);
    }

    {  // Re-layout
        CLLAnimation anim8 =
            GenerateAnimation(0.75, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked "
                              "List).\nThe whole process is still O(1).");
        anim8.SetAnimation([this, index](GUI::CircularLinkedList srcDS,
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

    {  // Relayout
        float length = 40 * visualizer.GetList().size() +
                       20 * (visualizer.GetList().size() - 1);
        float actualPosX = (global::SCREEN_WIDTH - length) / 2;
        GenerateRelayoutAnimation(
            (Vector2){actualPosX, visualizer.GetPosition().y});
        visualizer.Relayout();
    }
    ResetVisualizer();
}

void Algorithm::CircularLinkedList::DeleteHead() {
    InitAction({"if(head == nullptr) return; // empty, do nothing",
                "Node *del = head;", "head = head->next;", "tail->next = head;",
                "delete del;"});
    auto& nodes = visualizer.GetList();
    if (!nodes.size()) {
        CLLAnimation animNoElement = GenerateAnimation(
            0.75, 0,
            "head is currently NULL, so there is no element to delete.");
        animController->AddAnimation(animNoElement);
        return;
    }

    {  // Line 1
        nodes[0].SetLabel("head/0");
        nodes[0].AnimationOnNode(true);
        nodes[0].SetNodeState(GUI::Node::State::Active);
        CLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is exist, so we proceed to the next step");
        animController->AddAnimation(anim1);

        nodes[0].AnimationOnNode(false);
        nodes[0].SetLabel("head/del/0");
    }

    {  // Line 2
        if (nodes.size() > 1)

            nodes.back().SetLabel("tail/" + std::to_string(nodes.size() - 1));

        CLLAnimation anim2 = GenerateAnimation(
            0.75, 1, "The head is the only vertex in this List.");
        if (nodes.size() > 1)
            anim2.SetActionDescription("The head has a next node");

        animController->AddAnimation(anim2);
        nodes[0].SetLabel("del");
    }

    if (nodes.size() == 1) {
        CLLAnimation anim3 =
            GenerateAnimation(0.75, 1, "Head points to next (which is null).");
        animController->AddAnimation(anim3);

        visualizer.SetCircularArrowType(ArrowType::Hidden);
        CLLAnimation anim4 = GenerateAnimation(
            0.75, 3, "Remove head vertex.\nWe now have an empty List.");
        anim4.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& node = srcDS.GetList().front();

            node.SetRadius(AnimationFactory::ElasticOut(1.0f - playingAt) * 20);
            node.SetValueFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
            node.SetLabelFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);

            srcDS.Draw(base, playingAt);

            Vector2 pos = node.GetPosition();
            pos.x += base.x + srcDS.GetPosition().x;
            pos.y += base.y + srcDS.GetPosition().y;

            AnimationFactory::DrawCircularArrow(pos, pos, false,
                                                1.0f - playingAt);

            return srcDS;
        });
        visualizer.DeleteNode(0);
        animController->AddAnimation(anim4);

        return;
    }

    {  // Line 3
        nodes[1].SetLabel("head/0");
        nodes[1].AnimationOnNode(true);
        nodes[1].SetNodeState(GUI::Node::State::ActiveGreen);
        nodes.back().SetLabel("tail/" + std::to_string(nodes.size() - 2));
        CLLAnimation anim3 =
            GenerateAnimation(0.75, 2, "head points to the next node.");
        anim3.SetAnimation(HighlightArrowFromCur(0));
        animController->AddAnimation(anim3);

        visualizer.SetArrowType(0, ArrowType::Active);
    }

    {  // Line 4
        visualizer.SetCircularArrowType(ArrowType::Hidden);

        CLLAnimation anim4 =
            GenerateAnimation(0.75, 3, "tail->next now point to the new head.");
        anim4.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            Vector2 start = nodes[0].GetPosition();

            Vector2 newPosForOldHead = start;
            newPosForOldHead.y -= 60;

            nodes[0].SetPosition(
                AnimationFactory::MoveNode(start, newPosForOldHead, playingAt));

            srcDS.Draw(base, playingAt);

            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;
            Vector2 end = nodes[1].GetPosition();
            Vector2 endCircular = nodes.back().GetPosition();

            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;
            endCircular.x += base.x, endCircular.y += base.y;

            AnimationFactory::DrawCircularArrow(
                AnimationFactory::MoveNode(start, end, playingAt), endCircular,
                false, 1.0f);

            return srcDS;
        });
        animController->AddAnimation(anim4);

        nodes[0].SetPosition(nodes[0].GetPosition().x,
                             nodes[0].GetPosition().y - 60);

        visualizer.SetCircularEnds(1, nodes.size() - 1);
        visualizer.SetCircularArrowType(ArrowType::Default);
    }

    {  // Line 5
        visualizer.SetArrowType(0, ArrowType::Hidden);
        nodes[1].AnimationOnNode(false);
        CLLAnimation anim5 = GenerateAnimation(
            0.75, 3, "Delete del, which was the (previous) head.");
        anim5.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            nodes[0].SetRadius(AnimationFactory::ElasticOut(1.0f - playingAt) *
                               20);
            nodes[0].SetValueFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
            nodes[0].SetLabelFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);

            srcDS.Draw(base, playingAt);

            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            Vector2 start = nodes[0].GetPosition();
            Vector2 end = nodes[1].GetPosition();
            Vector2 endCircular = nodes.back().GetPosition();

            start.x += base.x, start.y += base.y;
            end.x += base.x, end.y += base.y;
            endCircular.x += base.x, endCircular.y += base.y;

            AnimationFactory::DrawDirectionalArrow(start, end, true,
                                                   1.0f - playingAt);
            return srcDS;
        });
        animController->AddAnimation(anim5);

        visualizer.DeleteNode(0);
        visualizer.SetPosition(visualizer.GetPosition().x + 60,
                               visualizer.GetPosition().y);
    }

    {  // Relayout
        float length = 40 * visualizer.GetList().size() +
                       20 * (visualizer.GetList().size() - 1);
        float actualPosX = (global::SCREEN_WIDTH - length) / 2;
        GenerateRelayoutAnimation(
            (Vector2){actualPosX, visualizer.GetPosition().y});
        visualizer.Relayout();
    }
    ResetVisualizer();
}

void Algorithm::CircularLinkedList::DeleteTail() {
    InitAction({"if(head == nullptr) return; // empty, do nothing",
                "Node *pre = head, *temp = head->next;", "while(temp != tail)",
                "	pre = temp, temp = temp->next; // pre->next = tmp",
                "tail = pre, tail->next = nullptr;", "delete temp;"});
    auto& nodes = visualizer.GetList();
    if (nodes.size() <= 1) {
        DeleteHead();
        return;
    }

    for (GUI::Node& node : nodes) node.AnimationOnNode(true);

    {  // Line 1
        nodes[0].SetLabel("head/0");
        nodes[0].SetNodeState(GUI::Node::State::Active);
        CLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is exist, so we proceed to the next step.");
        animController->AddAnimation(anim1);
        nodes[0].AnimationOnNode(false);
    }

    {  // Line 2
        nodes[0].SetNodeState(GUI::Node::Active);
        nodes[0].SetLabel("head/pre/0");

        nodes[1].SetNodeState(GUI::Node::ActiveGreen);
        nodes[1].SetLabel("temp/1");
        CLLAnimation anim1 = GenerateAnimation(
            0.75, 1, "Set pre to head. And temp to pre->next.");
        anim1.SetAnimation(HighlightArrowFromCur(0));
        visualizer.SetArrowType(0, ArrowType::Active);
        animController->AddAnimation(anim1);
        nodes[1].AnimationOnNode(false);
    }

    nodes[0].AnimationOnNode(false);
    nodes.back().SetNodeState(GUI::Node::Active);
    for (int k = 0; k <= nodes.size() - 2; k++) {
        {  // Line 2
            // if (k == nodes.size() - 1)
            // nodes.back().AnimationOnNode(true);
            CLLAnimation animLoop1 = GenerateAnimation(
                0.75, 2, "Check if temp is pointing at tail yet.");
            animController->AddAnimation(animLoop1);
        }

        if (k == nodes.size() - 2) break;
        nodes[k].AnimationOnNode(true);
        nodes[k + 1].AnimationOnNode(true);
        nodes.back().AnimationOnNode(false);

        {  // Line 3
            nodes[k].SetNodeState(GUI::Node::Iterated);
            nodes[k].ClearLabel();
            if (k == 0) nodes[k].SetLabel("head/0");

            nodes[k + 1].SetLabel("pre/" + std::to_string(k + 1));
            nodes[k + 1].SetNodeState(GUI::Node::Active);

            nodes[k + 2].SetLabel("temp/" + std::to_string(k + 2));
            nodes[k + 2].SetNodeState(GUI::Node::ActiveGreen);

            if (k + 2 == nodes.size() - 1) {
                nodes[k + 2].SetLabel("tail/temp/" + std::to_string(k + 2));
            }

            CLLAnimation animLoop2 =
                GenerateAnimation(0.75, 3,
                                  "temp is not at tail yet.\nSo both pre and "
                                  "temp pointers advance to their next node.");
            animLoop2.SetAnimation(HighlightArrowFromCur(k + 1));
            animController->AddAnimation(animLoop2);
            visualizer.SetArrowType(k + 1, ArrowType::Active);

            nodes[k].AnimationOnNode(false);
            nodes[k + 1].AnimationOnNode(false);
            nodes[k + 2].AnimationOnNode(false);
        }
    }
    {  // Line 5
        nodes[nodes.size() - 2].SetLabel("tail/pre/" +
                                         std::to_string(nodes.size() - 2));
        if (nodes.size() == 2) {
            nodes.front().SetLabel("head/tail/pre/0");
        }
        nodes.back().SetLabel("temp");
        visualizer.SetArrowType(nodes.size() - 2, ArrowType::Hidden);
        visualizer.SetCircularArrowType(ArrowType::Hidden);

        CLLAnimation anim5 = GenerateAnimation(
            0.75, 4,
            "temp is now point to tail. Set the tail to point at pre (the "
            "new "
            "tail) and remove link from current tail to previous tail.");
        anim5.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();
            Vector2 initBack = nodes.back().GetPosition();
            Vector2 newBack = initBack;
            newBack.y -= 60;
            nodes.back().SetPosition(
                AnimationFactory::MoveNode(initBack, newBack, playingAt));
            srcDS.Draw(base, playingAt);
            base.x += srcDS.GetPosition().x;
            base.y += srcDS.GetPosition().y;

            newBack = nodes.back().GetPosition();
            Vector2 nodeFront = nodes.front().GetPosition();
            Vector2 prvBack = nodes[nodes.size() - 2].GetPosition();

            initBack.x += base.x, initBack.y += base.y;
            newBack.x += base.x, newBack.y += base.y;
            nodeFront.x += base.x, nodeFront.y += base.y;
            prvBack.x += base.x, prvBack.y += base.y;

            AnimationFactory::DrawDirectionalArrow(
                prvBack, newBack, true, std::min(1.0f, (1.0f - playingAt) * 2));

            AnimationFactory::DrawCircularArrow(
                nodeFront,
                AnimationFactory::MoveNode(initBack, prvBack, playingAt), false,
                1.0f);

            return srcDS;
        });

        animController->AddAnimation(anim5);

        visualizer.SetCircularArrowType(ArrowType::Default);
        visualizer.SetCircularEnds(0, nodes.size() - 2);

        Vector2 newPosBack = nodes.back().GetPosition();
        newPosBack.y -= 60;
        nodes.back().SetPosition(newPosBack);
    }

    {  // Line 6
        nodes[nodes.size() - 2].SetNodeState(GUI::Node::ActiveBlue);
        nodes[nodes.size() - 2].AnimationOnNode(true);

        CLLAnimation anim6 = GenerateAnimation(
            0.75, 5,
            "Delete temp (the previous tail).\nThe whole process "
            "is O(N) just to find the pre pointer.");
        anim6.SetAnimation([this](GUI::CircularLinkedList srcDS,
                                  float playingAt, Vector2 base) {
            auto& nodes = srcDS.GetList();

            nodes.back().SetRadius(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);
            nodes.back().SetValueFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 24);
            nodes.back().SetLabelFontSize(
                AnimationFactory::ElasticOut(1.0f - playingAt) * 20);

            srcDS.Draw(base, playingAt);

            return srcDS;
        });
        animController->AddAnimation(anim6);

        nodes[nodes.size() - 2].AnimationOnNode(false);
        visualizer.DeleteNode(nodes.size() - 1, true);
    }

    {  // Relayout
        float length = 40 * visualizer.GetList().size() +
                       20 * (visualizer.GetList().size() - 1);
        float actualPosX = (global::SCREEN_WIDTH - length) / 2;
        GenerateRelayoutAnimation(
            (Vector2){actualPosX, visualizer.GetPosition().y});
        visualizer.Relayout();
    }
    ResetVisualizer();
}

void Algorithm::CircularLinkedList::DeleteMiddle(int index) {
    InitAction({"if(head == nullptr) return; // empty, do nothing",
                "Node *pre = head;", "for(int k=0;k<i-1;k++)",
                "	pre = pre->next;",
                "Node *del = pre->next, *aft = del->next;",
                "pre->next = aft; // bypass del", "delete del;"});

    /* Animation goes here */
    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) node.AnimationOnNode(true);

    {  // Line 1
        nodes[0].SetLabel("head/0");
        nodes[0].SetNodeState(GUI::Node::State::Active);
        CLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is exist, so we proceed to the next step");
        animController->AddAnimation(anim1);
        nodes[0].AnimationOnNode(false);
    }

    {  // Line 2
        nodes[0].SetLabel("head/pre/0");
        CLLAnimation anim1 =
            GenerateAnimation(0.75, 1,
                              "Set prev to head.\nPointer prev will stop at "
                              "one vertex before the deleted vertex.");
        animController->AddAnimation(anim1);
    }

    nodes[0].AnimationOnNode(false);
    for (int k = 0; k <= index - 1; k++) {
        {  // Line 3
            CLLAnimation animLoop1 = GenerateAnimation(
                0.75, 2,
                "Increment k, index specified has not been reached.\nk: " +
                    std::to_string(k) + ".");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index - 1)
                animLoop1.SetActionDescription(
                    "k is " + std::to_string(k) +
                    ", prev now points to one vertex behind the vertex "
                    "to-be-deleted.\nWe stop searching and continue with "
                    "the "
                    "removal.");
            else
                animLoop1.SetAnimation(HighlightArrowFromCur(k));
            animController->AddAnimation(animLoop1);
        }

        if (k == index - 1) break;

        {  // Line 4
            nodes[k].SetNodeState(GUI::Node::Iterated);
            nodes[k].ClearLabel();
            if (k == 0) nodes[k].SetLabel("head");

            nodes[k + 1].SetLabel("pre/" + std::to_string(k + 1));
            nodes[k + 1].SetNodeState(GUI::Node::Active);
            nodes[k + 1].AnimationOnNode(true);
            visualizer.SetArrowType(k, ArrowType::Active);

            CLLAnimation animLoop2 = GenerateAnimation(
                0.75, 3, "Pointer pre advances to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    nodes[index].SetLabel("del/" + std::to_string(index));
    nodes[index].SetNodeState(GUI::Node::State::ActiveRed);
    CLLAnimation anim5 = GenerateAnimation(
        0.75, 4,
        "We store reference to the vertex to-be-deleted.\nWe also store "
        "reference to the vertex after the to-be-deleted vertex.");
    anim5.SetAnimation(HighlightArrowFromCur(index - 1));
    visualizer.SetArrowType(index - 1, ArrowType::Active);
    nodes[index].AnimationOnNode(false);

    nodes[index + 1].SetLabel("aft/" + std::to_string(index + 1));
    nodes[index + 1].SetNodeState(GUI::Node::State::ActiveGreen);
    if (index + 1 == nodes.size() - 1)
        nodes[index + 1].SetLabel("tail/aft/" + std::to_string(index + 1));

    CLLAnimation anim5_2 = GenerateAnimation(
        0.75, 4,
        "We store reference to the vertex to-be-deleted.\nWe also store "
        "reference to the vertex after the to-be-deleted vertex.");
    anim5_2.SetAnimation(HighlightArrowFromCur(index));

    animController->AddAnimation(anim5);
    animController->AddAnimation(anim5_2);

    {  // Line 6
        nodes[index + 1].AnimationOnNode(false);
        visualizer.SetArrowType(index - 1, ArrowType::Hidden);
        visualizer.SetArrowType(index, ArrowType::Skip);

        CLLAnimation anim6 =
            GenerateAnimation(1.50, 5,
                              "We connect the vertex behind the vertex "
                              "to-be-deleted (pointer prev) "
                              "with the next vertex after the vertex "
                              "to-be-deleted (pointer after).");
        anim6.SetAnimation([this, index](GUI::CircularLinkedList srcDS,
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

            AnimationFactory::DrawDirectionalArrow(start, end, true, 1.0f);
            AnimationFactory::DrawActiveArrow(beforeStart, end2, 1.0f);

            return srcDS;
        });
        animController->AddAnimation(anim6);

        visualizer.SetArrowType(index - 1, ArrowType::Active);
        nodes[index].SetPosition(nodes[index].GetPosition().x,
                                 nodes[index].GetPosition().y - 60);
    }

    {  // Line 7
        nodes[index + 1].SetLabel("aft/" + std::to_string(index));
        CLLAnimation anim7 =
            GenerateAnimation(0.75, 6, "Now we delete this vertex.");
        anim7.SetAnimation([this, index](GUI::CircularLinkedList srcDS,
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
            AnimationFactory::DrawDirectionalArrow(start, end, true,
                                                   1.0f - playingAt);

            return srcDS;
        });
        animController->AddAnimation(anim7);
        visualizer.DeleteNode(index, false);
    }

    {  // Re-layout
        CLLAnimation anim8 =
            GenerateAnimation(0.75, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked "
                              "List).\nThe whole process is still O(1).");
        anim8.SetAnimation([this, index](GUI::CircularLinkedList srcDS,
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
        visualizer.Relayout();
    }

    ResetVisualizer();
}

void Algorithm::CircularLinkedList::Update(int index, int value) {
    InitAction({"if(head == nullptr) return; // NO_ELEMENT",
                "Node *cur = head;", "for(int k=0;k<i;k++)",
                "	cur = cur->next;", "cur->value = v;"});
    /* Animation goes here */
    auto& nodes = visualizer.GetList();

    if (!nodes.size()) {
        CLLAnimation animNoElement = GenerateAnimation(
            0.75, 0,
            "head is currently NULL, so there is no element to update.");
        animController->AddAnimation(animNoElement);
        return;
    }
    {  // Line 1
        nodes[0].SetNodeState(GUI::Node::Active);
        nodes[0].SetLabel("head/0");
        nodes[0].AnimationOnNode(true);
        CLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is currently NOT NULL, proceed to the next line.");
        animController->AddAnimation(anim1);
        nodes[0].AnimationOnNode(false);
    }

    {  // Line 2
        // nodes[0].SetNodeState(GUI::Node::Active);
        nodes[0].SetLabel("head/cur/0");
        CLLAnimation anim2 = GenerateAnimation(0.75, 1, "Set cur to head.");
        animController->AddAnimation(anim2);
    }

    if (index == 0) {
        CLLAnimation animNoLoop =
            GenerateAnimation(0.75, 1,
                              "We are already at the point we want to update "
                              "(head).\nProceed to update the head.");
    }

    for (int k = 0; k <= index; k++) {
        {  // Line 2
            CLLAnimation animLoop1 = GenerateAnimation(
                0.75, 2, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index)
                animLoop1.SetActionDescription(
                    "We have found the point we want to update.\nWe will "
                    "exit "
                    "the for-loop.");
            else
                animLoop1.SetAnimation(HighlightArrowFromCur(k));
            animController->AddAnimation(animLoop1);
        }

        if (k == index) break;

        {  // Line 3
            nodes[k].SetNodeState(GUI::Node::Iterated);
            nodes[k].ClearLabel();
            if (k == 0) nodes[k].SetLabel("head");

            nodes[k + 1].SetLabel("cur/" + std::to_string(k + 1));
            nodes[k + 1].SetNodeState(GUI::Node::Active);
            nodes[k + 1].AnimationOnNode(true);
            visualizer.SetArrowType(k, ArrowType::Active);

            CLLAnimation animLoop2 =
                GenerateAnimation(0.75, 3, "We set cur to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    // nodes[index].AnimationOnNode(true);
    nodes[index].SetNodeState(GUI::Node::ActiveGreen);
    CLLAnimation animFocusNode =
        GenerateAnimation(0.75, 4,
                          "Updating node " + std::to_string(index) +
                              "'s value to " + std::to_string(value));
    animController->AddAnimation(animFocusNode);

    nodes[index].AnimationOnNode(false);
    nodes[index].SetValue(value);
    CLLAnimation animFinal =
        GenerateAnimation(0.75, 4,
                          "Updated node " + std::to_string(index) +
                              "'s value to " + std::to_string(value) + "!");
    animController->AddAnimation(animFinal);

    ResetVisualizer();
}

void Algorithm::CircularLinkedList::Search(int value) {
    InitAction({"if(head == nullptr) return nullptr; // empty, NOT_FOUND",
                "Node* cur = head;", "do {",
                "    if(cur->value == v) return cur;", "    cur = cur->next;",
                "} while (cur != head);", "return nullptr; // NOT_FOUND"});

    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) node.AnimationOnNode(true);
    if (!nodes.size()) {
        CLLAnimation animNoElement =
            GenerateAnimation(0.75, 0,
                              "head is currently NULL, so there is no element "
                              "to search for, return NULL.");
        animController->AddAnimation(animNoElement);
        return;
    }

    {  // Line 1
        nodes[0].SetLabel("head/0");
        nodes[0].SetNodeState(GUI::Node::State::Active);
        CLLAnimation anim1 = GenerateAnimation(
            0.5, 0, "head is exist, so we proceed to the next step");
        animController->AddAnimation(anim1);
        nodes[0].AnimationOnNode(false);
    }

    {  // Line 2
        nodes[0].SetLabel("head/cur/0");
        CLLAnimation anim2 = GenerateAnimation(0.5, 1, "Set cur to head.");
        animController->AddAnimation(anim2);
    }

    int i = 0;
    bool found = false;
    do {
        if (i == nodes.size()) break;

        CLLAnimation animLoop1 = GenerateAnimation(
            0.5, 3, "Check if the current node's value is equal to v");
        CLLAnimation animLoop2;
        if (nodes[i].GetValue() == value) {
            animLoop1 = GenerateAnimation(
                0.5, 3,
                "Found value v = " + std::to_string(value) +
                    " at this highlighted vertex so we return node at "
                    "index " +
                    std::to_string(i) + ".\nThe whole operation is O(N)");
            found = true;
            nodes[i].ClearLabel();
            if (i == 0)
                nodes[i].SetLabel("head");
            else if (i + 1 == nodes.size())
                nodes[i].SetLabel("tail");

            animController->AddAnimation(animLoop1);
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
            animLoop2 = GenerateAnimation(0.5, 4, "Advance to the next node.");

            if (i + 1 < nodes.size()) {
                animLoop2.SetAnimation(HighlightArrowFromCur(i));
                visualizer.SetArrowType(i, ArrowType::Active);
            } else {
                animLoop2.SetAnimation(HighlightCircularArrow());
                visualizer.SetCircularArrowType(ArrowType::Active);
            }
            nodes[i].AnimationOnNode(false);
            if (i + 1 < nodes.size()) nodes[i + 1].AnimationOnNode(false);

            CLLAnimation animLoop3 = GenerateAnimation(
                0.5, 5,
                "Check whether we have iterated over all of the nodes.");

            animController->AddAnimation(animLoop1);
            animController->AddAnimation(animLoop2);
            animController->AddAnimation(animLoop3);
        }
        nodes[i].AnimationOnNode(false);
    } while (!found && ++i);

    if (!found) {
        CLLAnimation animNotFound = GenerateAnimation(
            0.5, 6,
            "We have iterated over the whole Linked List (we have gone past "
            "the tail after O(N) step(s)). We can conclude that value v = " +
                std::to_string(value) +
                " is NOT FOUND in the Linked "
                "List");
        animController->AddAnimation(animNotFound);
    }

    ResetVisualizer();
}

std::function< GUI::CircularLinkedList(GUI::CircularLinkedList, float,
                                       Vector2) >
Algorithm::CircularLinkedList::HighlightArrowFromCur(int index,
                                                     bool drawVisualizer,
                                                     bool reverse) {
    return [this, index, drawVisualizer, reverse](
               GUI::CircularLinkedList srcDS, float playingAt, Vector2 base) {
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

std::function< GUI::CircularLinkedList(GUI::CircularLinkedList, float,
                                       Vector2) >
Algorithm::CircularLinkedList::HighlightCircularArrow(bool drawVisualizer,
                                                      bool reverse) {
    return [this, drawVisualizer, reverse](GUI::CircularLinkedList srcDS,
                                           float playingAt, Vector2 base) {
        auto& nodes = srcDS.GetList();
        if (drawVisualizer) srcDS.Draw(base, playingAt);
        base.x += srcDS.GetPosition().x;
        base.y += srcDS.GetPosition().y;

        Vector2 start = nodes.front().GetPosition();
        Vector2 end = nodes.back().GetPosition();

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        if (reverse) playingAt = 1.0f - playingAt;
        AnimationFactory::DrawCircularArrow(start, end, true, playingAt);
        return srcDS;
    };
}

void Algorithm::CircularLinkedList::ResetVisualizer() {
    auto& nodes = visualizer.GetList();
    for (GUI::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUI::Node::Default);
    }
    visualizer.ResetArrow();
}
