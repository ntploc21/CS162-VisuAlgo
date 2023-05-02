#include "LinkedList.hpp"

#include "Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUIVisualizer::LinkedList::LinkedList(FontHolder* fonts)
    : mDisplayHeadAndTail(true), fonts(fonts) {}
GUIVisualizer::LinkedList::LinkedList() : mDisplayHeadAndTail(true) {}
GUIVisualizer::LinkedList::~LinkedList() {}

void GUIVisualizer::LinkedList::SetShape(GUIVisualizer::Node::Shape shape) {
    mShape = shape;
    for (GUIVisualizer::Node& node : list) node.SetShape(shape);
}

GUIVisualizer::Node::Shape GUIVisualizer::LinkedList::GetShape() const {
    return mShape;
}

bool GUIVisualizer::LinkedList::isSelectable() const { return false; }

std::size_t GUIVisualizer::LinkedList::size() const { return list.size(); }

void GUIVisualizer::LinkedList::SetShowHeadAndTail(bool show) {
    mDisplayHeadAndTail = show;
}

void GUIVisualizer::LinkedList::SetOrientation(Orientation orientation) {
    mOrientation = orientation;
    Relayout();
}

std::vector< GUIVisualizer::Node >& GUIVisualizer::LinkedList::GetList() {
    return list;
}

GUIVisualizer::Node GUIVisualizer::LinkedList::GenerateNode(int value) {
    GUIVisualizer::Node node = GUIVisualizer::Node(value, fonts);
    return node;
}

void GUIVisualizer::LinkedList::Import(std::vector< int > nodes) {
    list.clear();

    float length = 40 * nodes.size() + mNodeDistance * (int(nodes.size()) - 1);

    if (mOrientation == Orientation::Horizontal)
        SetPosition((global::SCREEN_WIDTH - length) / 2, 150);
    else if (mOrientation == Orientation::Vertical)
        SetPosition(100 + (global::SCREEN_WIDTH - 40) / 2, 150);

    for (int i = 0; i < nodes.size(); i++) {
        GUIVisualizer::Node guiNode = GenerateNode(nodes[i]);
        Vector2 newPos = GetNodeDefaultPosition(i);
        guiNode.SetPosition(newPos.x, newPos.y);
        list.emplace_back(guiNode);
    }

    if (!mDisplayHeadAndTail) return;

    if (!list.empty()) list.at(0).SetLabel("head");
    if (list.size() > 1) list.back().SetLabel("tail");
}

void GUIVisualizer::LinkedList::InsertNode(std::size_t index,
                                           GUIVisualizer::Node node,
                                           bool rePosition) {
    assert(index >= 0 && index <= list.size());
    list.insert(list.begin() + index, node);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

void GUIVisualizer::LinkedList::Relayout() {
    std::vector< int > values;
    for (auto node : list) values.emplace_back(node.GetValue());
    Import(values);
}

Vector2 GUIVisualizer::LinkedList::GetNodeDefaultPosition(std::size_t index) {
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

void GUIVisualizer::LinkedList::DeleteNode(std::size_t index, bool rePosition) {
    list.erase(list.begin() + index);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}