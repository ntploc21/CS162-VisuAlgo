#include "LinkedList.hpp"

#include "Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUI::LinkedList::LinkedList(FontHolder* fonts)
    : mDisplayHeadAndTail(true), fonts(fonts) {}
GUI::LinkedList::LinkedList() : mDisplayHeadAndTail(true) {}
GUI::LinkedList::~LinkedList() {}

void GUI::LinkedList::SetShape(GUI::Node::Shape shape) {
    mShape = shape;
    for (GUI::Node& node : list) node.SetShape(shape);
}

GUI::Node::Shape GUI::LinkedList::GetShape() const { return mShape; }

bool GUI::LinkedList::isSelectable() const { return false; }

void GUI::LinkedList::SetShowHeadAndTail(bool show) {
    mDisplayHeadAndTail = show;
}

void GUI::LinkedList::SetOrientation(Orientation orientation) {
    mOrientation = orientation;
    Relayout();
}

std::vector< GUI::Node >& GUI::LinkedList::GetList() { return list; }

GUI::Node GUI::LinkedList::GenerateNode(int value) {
    GUI::Node node = GUI::Node(value, fonts);
    return node;
}

void GUI::LinkedList::Import(std::vector< int > nodes) {
    list.clear();

    float length = 40 * nodes.size() + mNodeDistance * (int(nodes.size()) - 1);

    if (mOrientation == Orientation::Horizontal)
        SetPosition((global::SCREEN_WIDTH - length) / 2, 150);
    else if (mOrientation == Orientation::Vertical)
        SetPosition(100 + (global::SCREEN_WIDTH - 40) / 2, 150);

    for (int i = 0; i < nodes.size(); i++) {
        GUI::Node guiNode = GenerateNode(nodes[i]);
        Vector2 newPos = GetNodeDefaultPosition(i);
        guiNode.SetPosition(newPos.x, newPos.y);
        list.emplace_back(guiNode);
    }

    if (!mDisplayHeadAndTail) return;

    if (!list.empty()) list.at(0).SetLabel("head");
    if (list.size() > 1) list.back().SetLabel("tail");
}

void GUI::LinkedList::InsertNode(std::size_t index, GUI::Node node,
                                 bool rePosition) {
    assert(index >= 0 && index <= list.size());
    list.insert(list.begin() + index, node);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

void GUI::LinkedList::Relayout() {
    std::vector< int > values;
    for (auto node : list) values.emplace_back(node.GetValue());
    Import(values);
}

Vector2 GUI::LinkedList::GetNodeDefaultPosition(std::size_t index) {
    Vector2 answer = (Vector2){0, 0};
    switch (mOrientation) {
        case Orientation::Horizontal:
            answer = (Vector2){index * (40 + mNodeDistance), 0};
            break;
        case Orientation::Vertical:
            answer = (Vector2){0, index * (40 + mNodeDistance)};
            break;
        default:
            break;
    }
    return answer;
}

void GUI::LinkedList::DeleteNode(std::size_t index, bool rePosition) {
    list.erase(list.begin() + index);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}