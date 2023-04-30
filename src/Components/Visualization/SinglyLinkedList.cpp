#include "SinglyLinkedList.hpp"

#include "Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUI::SinglyLinkedList::SinglyLinkedList(FontHolder* fonts)
    : GUI::LinkedList(fonts) {}
GUI::SinglyLinkedList::SinglyLinkedList() : GUI::LinkedList() {}
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

void GUI::SinglyLinkedList::Import(std::vector< int > nodes) {
    GUI::LinkedList::Import(nodes);
    ResetArrow();
}

void GUI::SinglyLinkedList::InsertNode(std::size_t index, GUI::Node node,
                                       bool rePosition) {
    assert(index >= 0 && index <= list.size());
    list.insert(list.begin() + index, node);
    if (index + 1 < list.size())
        arrowState.insert(arrowState.begin() + index, ArrowType::Default);
    else
        arrowState.insert(arrowState.end(), ArrowType::Default);

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
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
    arrowState.assign(resize, ArrowType::Default);
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