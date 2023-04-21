#include "SinglyLinkedList.hpp"

#include "Core/Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUI::SinglyLinkedList::SinglyLinkedList(FontHolder* fonts) : fonts(fonts) {}
GUI::SinglyLinkedList::SinglyLinkedList() {}
GUI::SinglyLinkedList::~SinglyLinkedList() {}

bool GUI::SinglyLinkedList::isSelectable() const { return false; }

void GUI::SinglyLinkedList::Draw(Vector2 base, float t, bool init) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    for (auto node : list) {
        node.Draw(base, t);
    }
    if (init)
        DrawArrow(base, t);
    else
        DrawArrow(base, 1.0f);
}

std::vector< GUI::Node >& GUI::SinglyLinkedList::GetList() { return list; }

GUI::Node GUI::SinglyLinkedList::GenerateNode(int value) {
    return GUI::Node(value, fonts);
}

void GUI::SinglyLinkedList::Import(std::vector< int > nodes) {
    list.clear();

    float nodeDist = 20;
    float length = 40 * nodes.size() + nodeDist * (nodes.size() - 1);
    SetPosition((global::SCREEN_WIDTH - length) / 2, 150);

    for (int i = 0; i < nodes.size(); i++) {
        GUI::Node guiNode = GenerateNode(nodes[i]);
        guiNode.SetPosition(i * (40 + nodeDist), 0);
        list.emplace_back(guiNode);
    }
    ClearActiveArrow();

    if (!list.empty()) list.at(0).SetLabel("head");
    if (list.size() > 1) list.back().SetLabel("tail");
}

void GUI::SinglyLinkedList::SetActiveArrow(std::size_t index) {
    if (index >= 0 && index < int(arrowState.size())) arrowState[index] = true;
}

void GUI::SinglyLinkedList::ClearActiveArrow() {
    arrowState.assign(list.size() - 1, false);
    arrowState.resize(list.size() - 1);
}

void GUI::SinglyLinkedList::DrawArrow(Vector2 base, float t) {
    for (int i = 0; i < int(list.size()) - 1; i++) {
        Vector2 start = list[i].GetPosition();
        Vector2 end = list[i + 1].GetPosition();

        start.x += base.x + 20, start.y += base.y;
        end.x += base.x - 20, end.y += base.y;

        bool activeArrow = (i + 2 < int(list.size()) &&
                            list[i + 1].GetNodeState() != GUI::Node::Default &&
                            list[i + 2].GetNodeState() != GUI::Node::Default);

        AnimationFactory::DrawDirectionalArrow(start, end, arrowState[i], t);
    }
}
