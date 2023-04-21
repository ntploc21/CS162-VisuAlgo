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
    ResetArrow();

    if (!list.empty()) list.at(0).SetLabel("head");
    if (list.size() > 1) list.back().SetLabel("tail");
}

void GUI::SinglyLinkedList::InsertNode(std::size_t index, GUI::Node node) {
    assert(index >= 0 && index <= list.size());
    list.insert(list.begin() + index, node);
    if (index + 1 < list.size())
        arrowState.insert(arrowState.begin() + index, ArrowType::Default);
    else
        arrowState.insert(arrowState.end(), ArrowType::Default);

    float nodeDist = 20;
    for (int i = index; i < list.size(); i++) {
        list.at(i).SetPosition(i * (40 + nodeDist), 0);
    }
}

void GUI::SinglyLinkedList::Relayout() {
    std::vector< int > values;
    for (auto node : list) values.emplace_back(node.GetValue());
    Import(values);
}

void GUI::SinglyLinkedList::SetArrowType(std::size_t index, ArrowType type) {
    if (index >= 0 && index < int(arrowState.size())) arrowState[index] = type;
}

void GUI::SinglyLinkedList::ResetArrow() {
    arrowState.assign(list.size() - 1, ArrowType::Default);
    arrowState.resize(list.size() - 1);
}

void GUI::SinglyLinkedList::DrawArrow(Vector2 base, float t) {
    for (int i = 0; i < int(list.size()) - 1; i++) {
        Vector2 start = list[i].GetPosition();
        Vector2 end = list[i + 1].GetPosition();

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        switch (arrowState[i]) {
            case ArrowType::Default:
                AnimationFactory::DrawDirectionalArrow(start, end, false, t);
                break;
            case ArrowType::Active:
                AnimationFactory::DrawDirectionalArrow(start, end, true, t);
            case ArrowType::Hidden:
            default:
                break;
        }
        // if(arrowState[i])
    }
}
