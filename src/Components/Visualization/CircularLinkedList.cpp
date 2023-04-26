#include "CircularLinkedList.hpp"

#include "Core/Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUI::CircularLinkedList::CircularLinkedList(FontHolder* fonts)
    : GUI::LinkedList(fonts) {}
GUI::CircularLinkedList::CircularLinkedList() : GUI::LinkedList() {}
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

    if (list.empty()) return;
    Vector2 start = list[0].GetPosition();
    Vector2 end = list.back().GetPosition();
    start.x += base.x, start.y += base.y;
    end.x += base.x, end.y += base.y;

    AnimationFactory::DrawCircularArrow(start, end, false, t);
}

void GUI::CircularLinkedList::SetDefaultArrowType(ArrowType arrowType) {
    defaultArrowType = arrowType;
}

void GUI::CircularLinkedList::Import(std::vector< int > nodes) {
    GUI::LinkedList::Import(nodes);
    ResetArrow();
}

void GUI::CircularLinkedList::InsertNode(std::size_t index, GUI::Node node,
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

void GUI::CircularLinkedList::SetArrowType(std::size_t index, ArrowType type) {
    if (index >= 0 && index < int(arrowState.size())) arrowState[index] = type;
}

GUI::CircularLinkedList::ArrowType GUI::CircularLinkedList::GetArrowType(
    std::size_t index) {
    return arrowState[index];
}

void GUI::CircularLinkedList::ResetArrow() {
    std::size_t resize = std::max(0, int(list.size() - 1));
    arrowState.assign(resize, defaultArrowType);
    arrowState.resize(resize);
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
        // if(arrowState[i])
    }
}

void GUI::CircularLinkedList::DeleteNode(std::size_t index, bool rePosition) {
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