#include "CircularLinkedList.hpp"

#include "Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUI::CircularLinkedList::CircularLinkedList(FontHolder* fonts)
    : GUI::LinkedList(fonts), circularArrowState(ArrowType::Default) {}
GUI::CircularLinkedList::CircularLinkedList()
    : GUI::LinkedList(), circularArrowState(ArrowType::Default) {}
GUI::CircularLinkedList::~CircularLinkedList() {}

bool GUI::CircularLinkedList::isSelectable() const { return false; }

void GUI::CircularLinkedList::Draw(Vector2 base, float t, bool init) {
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

void GUI::CircularLinkedList::Import(std::vector< int > nodes) {
    GUI::LinkedList::Import(nodes);
    SetCircularEnds(0, list.size() - 1);
    ResetArrow();
}

void GUI::CircularLinkedList::InsertNode(std::size_t index, GUI::Node node,
                                         bool rePosition) {
    assert(index >= 0 && index <= list.size());
    list.insert(list.begin() + index, node);
    if (index + 1 < list.size())
        arrowState.insert(arrowState.begin() + index, ArrowType::Default);
    else
        arrowState.insert(arrowState.end(), ArrowType::Default);
    SetCircularEnds(0, list.size() - 1);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

void GUI::CircularLinkedList::SetCircularArrowType(ArrowType type) {
    circularArrowState = type;
}

GUI::LinkedList::ArrowType GUI::CircularLinkedList::GetCircularArrowType(
    std::size_t index) {
    return circularArrowState;
}

void GUI::CircularLinkedList::SetCircularEnds(std::size_t from,
                                              std::size_t to) {
    if (!(from >= 0 && from < list.size())) return;
    if (!(to >= 0 && to < list.size())) return;
    mCircularEnds = std::make_pair(from, to);
}

std::pair< std::size_t, std::size_t >
GUI::CircularLinkedList::GetCircularEnds() {
    return mCircularEnds;
}

void GUI::CircularLinkedList::SetArrowType(std::size_t index, ArrowType type) {
    if (index >= 0 && index < int(arrowState.size())) arrowState[index] = type;
}

GUI::LinkedList::ArrowType GUI::CircularLinkedList::GetArrowType(
    std::size_t index) {
    return arrowState[index];
}

void GUI::CircularLinkedList::ResetArrow() {
    std::size_t resize = std::max(0, int(list.size() - 1));
    arrowState.assign(resize, ArrowType::Default);
    arrowState.resize(resize);
    SetCircularArrowType(ArrowType::Default);
    SetCircularEnds(0, list.size() - 1);
}

void GUI::CircularLinkedList::DrawArrow(Vector2 base, float t) {
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
    }

    /* */
    if (list.empty()) return;
    Vector2 start = list[mCircularEnds.first].GetPosition();
    Vector2 end = list[mCircularEnds.second].GetPosition();
    start.x += base.x, start.y += base.y;
    end.x += base.x, end.y += base.y;

    switch (circularArrowState) {
        case ArrowType::Default:
            AnimationFactory::DrawCircularArrow(start, end, false, t);
            break;
        case ArrowType::Active:
            AnimationFactory::DrawCircularArrow(start, end, true, t);
        case ArrowType::Skip:
        case ArrowType::Hidden:
        default:
            break;
    }
}

void GUI::CircularLinkedList::DeleteNode(std::size_t index, bool rePosition) {
    list.erase(list.begin() + index);
    if (!arrowState.empty())
        arrowState.erase(arrowState.begin() +
                         std::min(index, arrowState.size() - 1));
    if (list.empty()) {
        SetCircularArrowType(ArrowType::Hidden);
    }
    SetCircularEnds(0, list.size() - 1);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}