#include "SinglyLinkedList.hpp"

#include "Core/Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUI::SinglyLinkedList::SinglyLinkedList(FontHolder* fonts)
    : mDisplayHeadAndTail(true), fonts(fonts) {}

void GUI::SinglyLinkedList::SetShape(GUI::Node::Shape shape) {
    mShape = shape;
    for (GUI::Node& node : list) node.SetShape(shape);
}

GUI::Node::Shape GUI::SinglyLinkedList::GetShape() const { return mShape; }
GUI::SinglyLinkedList::SinglyLinkedList() : mDisplayHeadAndTail(true) {}
GUI::SinglyLinkedList::~SinglyLinkedList() {}

bool GUI::SinglyLinkedList::isSelectable() const { return false; }

void GUI::SinglyLinkedList::Draw(Vector2 base, float t, bool init) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    if (init)
        DrawArrow(base, t);
    else
        DrawArrow(base, 1.0f);
    for (auto node : list) {
        node.Draw(base, t);
    }
}

void GUI::SinglyLinkedList::SetDefaultArrowType(ArrowType arrowType) {
    defaultArrowType = arrowType;
}

void GUI::SinglyLinkedList::SetShowHeadAndTail(bool show) {
    mDisplayHeadAndTail = show;
}

void GUI::SinglyLinkedList::SetOrientation(Orientation orientation) {
    mOrientation = orientation;
    Relayout();
}

std::vector< GUI::Node >& GUI::SinglyLinkedList::GetList() { return list; }

GUI::Node GUI::SinglyLinkedList::GenerateNode(int value) {
    GUI::Node node = GUI::Node(value, fonts);
    return node;
}

void GUI::SinglyLinkedList::Import(std::vector< int > nodes) {
    list.clear();

    float length = 40 * nodes.size() + mNodeDistance * (nodes.size() - 1);

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
    ResetArrow();

    if (!mDisplayHeadAndTail) return;

    if (!list.empty()) list.at(0).SetLabel("head");
    if (list.size() > 1) list.back().SetLabel("tail");
}

void GUI::SinglyLinkedList::InsertNode(std::size_t index, GUI::Node node,
                                       bool rePosition) {
    assert(index >= 0 && index <= list.size());
    list.insert(list.begin() + index, node);
    if (index + 1 < list.size())
        arrowState.insert(arrowState.begin() + index, defaultArrowType);
    else
        arrowState.insert(arrowState.end(), defaultArrowType);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
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

GUI::SinglyLinkedList::ArrowType GUI::SinglyLinkedList::GetArrowType(
    std::size_t index) {
    return arrowState[index];
}

void GUI::SinglyLinkedList::ResetArrow() {
    std::size_t resize = std::max(0, int(list.size() - 1));
    arrowState.assign(resize, defaultArrowType);
    arrowState.resize(resize);
}

void GUI::SinglyLinkedList::DrawArrow(Vector2 base, float t) {
    for (int i = 0; i < int(list.size()) - 1; i++) {
        Vector2 start = list[i].GetPosition();
        Vector2 end = list[i + 1].GetPosition();
        if (arrowState[i + 1] == ArrowType::Skip) {
            if (!(i + 2 < list.size())) break;
            end = list[i + 2].GetPosition();
        }

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        switch (arrowState[i]) {
            case ArrowType::Default:
                AnimationFactory::DrawDirectionalArrow(start, end, false, t);
                break;
            case ArrowType::Active:
                AnimationFactory::DrawDirectionalArrow(start, end, true, t);
            case ArrowType::Skip:
            case ArrowType::Hidden:
            default:
                break;
        }
        // if(arrowState[i])
    }
}

Vector2 GUI::SinglyLinkedList::GetNodeDefaultPosition(std::size_t index) {
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

void GUI::SinglyLinkedList::DeleteNode(std::size_t index, bool rePosition) {
    list.erase(list.begin() + index);
    if (!arrowState.empty())
        arrowState.erase(arrowState.begin() +
                         std::min(index, arrowState.size() - 1));

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}