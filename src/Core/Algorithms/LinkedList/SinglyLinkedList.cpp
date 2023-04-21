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
    InitAction({});
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
    animController->InteractionLock();
}

void Algorithm::SinglyLinkedList::Insert(int index, int value) {}

void Algorithm::SinglyLinkedList::InsertHead(int value) {
    if (visualizer.GetList().size() == maxN) return;
    InitAction(
        {"Node *node = new Node(v);", "node->next = head;", "head = node;"});

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
}

void Algorithm::SinglyLinkedList::InsertAfterTail(int value) {
    int prvSize = visualizer.GetList().size();
    if (prvSize == 0) InsertHead(value);
    if (prvSize == maxN) return;
    if (visualizer.GetList().size() == maxN) return;

    InitAction(
        {"Node *node = new Node(v);", "tail->next = node;", "tail = node;"});

    /* Animation goes here */

    GUI::Node newNode = visualizer.GenerateNode(value);
    newNode.SetNodeState(GUI::Node::Active);
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
    anim1.SetAnimation(
        [this](GUI::SinglyLinkedList srcDS, float playingAt, Vector2 base) {
            GUI::Node& node = srcDS.GetList().back();
            node.SetRadius(AnimationFactory::ElasticOut(playingAt) * 20);
            node.SetValueFontSize(AnimationFactory::ElasticOut(playingAt) * 24);
            node.SetLabelFontSize(AnimationFactory::ElasticOut(playingAt) * 20);

            srcDS.Draw(base, playingAt);
            return srcDS;
        });
    animController->AddAnimation(anim1);

    visualizer.GetList().back().SetNodeState(GUI::Node::State::Iterated);
    visualizer.GetList()[prvSize - 1].SetNodeState(GUI::Node::State::Active);
    visualizer.GetList()[prvSize - 1].AnimationOnNode(true);
    SLLAnimation anim2 =
        GenerateAnimation(1, 1, "Current tail->next points to the node.");
    anim2.SetAnimation([this, prvSize](GUI::SinglyLinkedList srcDS,
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

    visualizer.GetList()[prvSize - 1].SetNodeState(GUI::Node::State::Default);
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
    anim4.SetAnimation([this, actualPosX](GUI::SinglyLinkedList srcDS,
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

void Algorithm::SinglyLinkedList::InsertMiddle(int index, int value) {
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
        SLLAnimation anim1 = GenerateAnimation(0.75, 0, "Set pre to head.");
        animController->AddAnimation(anim1);
    }

    nodes[0].AnimationOnNode(false);
    for (int k = 0; k <= index - 1; k++) {
        {  // Line 2
            SLLAnimation animLoop1 = GenerateAnimation(
                0.75, 1, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index - 1)
                animLoop1.SetActionDescription(
                    "We have found the insertion point.\nWe continue the next "
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

            SLLAnimation animLoop2 =
                GenerateAnimation(0.75, 2, "We set pre to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    {  // line 4
        nodes[index].SetLabel("aft/" + std::to_string(index));
        nodes[index].SetNodeState(GUI::Node::ActiveBlue);
        nodes[index].AnimationOnNode(true);
        SLLAnimation anim4 = GenerateAnimation(
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
        newNodePos.y += 60;

        visualizer.InsertNode(index, newNode, false);
        visualizer.SetArrowType(index, ArrowType::Skip);

        nodes[index].SetPosition(newNodePos);

        SLLAnimation anim5 = GenerateAnimation(
            0.75, 4,
            "Create new vertex to store value " + std::to_string(value) + ".");
        animController->AddAnimation(anim5);

        nodes[index].AnimationOnNode(false);
    }

    {  // line 6
        nodes[index].SetLabel("node/" + std::to_string(index));
        nodes[index + 1].SetLabel("aft/" + std::to_string(index + 1));
        SLLAnimation anim6 =
            GenerateAnimation(0.75, 5, "node->next points to aft.");
        anim6.SetAnimation([this, index](GUI::SinglyLinkedList srcDS,
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
        SLLAnimation anim7 =
            GenerateAnimation(0.75, 5, "pre->next points to node.");
        anim7.SetAnimation([this, index](GUI::SinglyLinkedList srcDS,
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
        SLLAnimation anim8 =
            GenerateAnimation(0.75, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked "
                              "List).\nThe whole process is still O(1).");
        anim8.SetAnimation([this, index](GUI::SinglyLinkedList srcDS,
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
        SLLAnimation anim9 =
            GenerateAnimation(0.5, -1,
                              "Re-layout the Linked List for visualization "
                              "(not in the actual Linked "
                              "List).\nThe whole process is still O(1).");
        anim9.SetAnimation([this, actualPosX](GUI::SinglyLinkedList srcDS,
                                              float playingAt, Vector2 base) {
            Vector2 newPos = srcDS.GetPosition();
            newPos.x += (actualPosX - newPos.x) * playingAt;
            srcDS.SetPosition(newPos);

            srcDS.Draw(base, playingAt);

            return srcDS;
        });
        animController->AddAnimation(anim9);
    }

    visualizer.Relayout();

    for (GUI::Node& node : nodes) {
        node.AnimationOnNode(false);
        node.SetNodeState(GUI::Node::Default);
    }
    visualizer.ResetArrow();
}

void Algorithm::SinglyLinkedList::Delete(int index) {}

void Algorithm::SinglyLinkedList::DeleteHead() {}

void Algorithm::SinglyLinkedList::DeleteTail() {}

void Algorithm::SinglyLinkedList::DeleteMiddle(int index) {}

void Algorithm::SinglyLinkedList::Update(int index, int value) {
    InitAction({"if(head == nullptr) return; // NO_ELEMENT",
                "Node *cur = head;", "for(int k=0;k<i;k++)",
                "	cur = cur->next;", "cur->value = v;"});
    /* Animation goes here */
    auto& nodes = visualizer.GetList();

    if (!nodes.size()) {
        SLLAnimation animNoElement = GenerateAnimation(
            0.75, 0,
            "head is currently NULL, so there is no element to update.");
        animController->AddAnimation(animNoElement);
        return;
    }
    {  // Line 1
        nodes[0].SetNodeState(GUI::Node::Active);
        nodes[0].SetLabel("head/0");
        nodes[0].AnimationOnNode(true);
        SLLAnimation anim1 = GenerateAnimation(
            0.75, 0, "head is currently NOT NULL, proceed to the next line.");
        animController->AddAnimation(anim1);
        nodes[0].AnimationOnNode(false);
    }

    {  // Line 2
        // nodes[0].SetNodeState(GUI::Node::Active);
        nodes[0].SetLabel("head/cur/0");
        SLLAnimation anim2 = GenerateAnimation(0.75, 1, "Set cur to head.");
        animController->AddAnimation(anim2);
    }

    if (index == 0) {
        SLLAnimation animNoLoop =
            GenerateAnimation(0.75, 1,
                              "We are already at the point we want to update "
                              "(head).\nProceed to update the head.");
    }

    for (int k = 0; k <= index; k++) {
        {  // Line 2
            SLLAnimation animLoop1 = GenerateAnimation(
                0.75, 2, "Increment k, index specified has not been reached.");
            if (k == 0)
                animLoop1.SetActionDescription("Enter the loop.\nk is now: 0");
            if (k == index)
                animLoop1.SetActionDescription(
                    "We have found the point we want to update.\nWe will exit "
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

            SLLAnimation animLoop2 =
                GenerateAnimation(0.75, 3, "We set cur to the next vertex.");
            nodes[k + 1].AnimationOnNode(false);
            animController->AddAnimation(animLoop2);
        }
    }

    // nodes[index].AnimationOnNode(true);
    nodes[index].SetNodeState(GUI::Node::ActiveGreen);
    SLLAnimation animFocusNode =
        GenerateAnimation(0.75, 4,
                          "Updating node " + std::to_string(index) +
                              "'s value to " + std::to_string(value));
    animController->AddAnimation(animFocusNode);

    nodes[index].AnimationOnNode(false);
    nodes[index].SetValue(value);
    SLLAnimation animFinal =
        GenerateAnimation(0.75, 4,
                          "Updated node " + std::to_string(index) +
                              "'s value to " + std::to_string(value) + "!");
    animController->AddAnimation(animFinal);
}

void Algorithm::SinglyLinkedList::Search(int value) {
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
    for (GUI::Node& node : nodes) node.AnimationOnNode(true);

    nodes[0].SetNodeState(GUI::Node::Active);
    nodes[0].SetLabel("head/cur/0");
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
                animLoop3.SetAnimation(HighlightArrowFromCur(i));
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

void Algorithm::SinglyLinkedList::InitAction(std::vector< std::string > code) {
    animController->Reset();
    // animController->Pause();
    animController->InteractionAllow();
    animController->Clear();
    codeHighlighter->AddCode(code);
    codeHighlighter->SetShowCode(true);
    codeHighlighter->SetShowAction(true);
}

std::function< GUI::SinglyLinkedList(GUI::SinglyLinkedList, float, Vector2) >
Algorithm::SinglyLinkedList::HighlightArrowFromCur(int index) {
    return [this, index](GUI::SinglyLinkedList srcDS, float playingAt,
                         Vector2 base) {
        auto& nodes = srcDS.GetList();
        srcDS.Draw(base, playingAt);
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

        AnimationFactory::DrawActiveArrow(start, end, playingAt);
        return srcDS;
    };
}
