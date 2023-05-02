#include "DoublyLinkedList.hpp"

#include "Animation/AnimationFactory.hpp"
#include "Global.hpp"

GUIVisualizer::DoublyLinkedList::DoublyLinkedList(FontHolder* fonts)
    : GUIVisualizer::LinkedList(fonts) {}
GUIVisualizer::DoublyLinkedList::DoublyLinkedList()
    : GUIVisualizer::LinkedList() {}
GUIVisualizer::DoublyLinkedList::~DoublyLinkedList() {}

bool GUIVisualizer::DoublyLinkedList::isSelectable() const { return false; }

void GUIVisualizer::DoublyLinkedList::Draw(Vector2 base, float t, bool init) {
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

void GUIVisualizer::DoublyLinkedList::Import(std::vector< int > nodes) {
    GUIVisualizer::LinkedList::Import(nodes);
    ResetArrow();
}

void GUIVisualizer::DoublyLinkedList::InsertNode(std::size_t index,
                                                 GUIVisualizer::Node node,
                                                 bool rePosition) {
    assert(index >= 0 && index <= list.size());
    list.insert(list.begin() + index, node);
    if (index + 1 < list.size()) {
        arrowStateNext.insert(arrowStateNext.begin() + index,
                              ArrowType::Default);
        arrowStatePrev.insert(arrowStatePrev.begin() + index,
                              ArrowType::Default);
    } else {
        arrowStateNext.insert(arrowStateNext.end(), ArrowType::Default);
        arrowStatePrev.insert(arrowStatePrev.end(), ArrowType::Default);
    }

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

void GUIVisualizer::DoublyLinkedList::SetArrowTypeNext(std::size_t index,
                                                       ArrowType type) {
    if (!(index >= 0 && index < int(list.size()) - 1)) return;
    arrowStateNext[index] = type;
}

void GUIVisualizer::DoublyLinkedList::SetArrowTypePrev(std::size_t index,
                                                       ArrowType type) {
    if (!(index >= 0 && index < int(list.size()) - 1)) return;
    arrowStatePrev[index] = type;
}

GUIVisualizer::DoublyLinkedList::ArrowType
GUIVisualizer::DoublyLinkedList::GetArrowTypeNext(std::size_t index) {
    return arrowStateNext[index];
}

GUIVisualizer::DoublyLinkedList::ArrowType
GUIVisualizer::DoublyLinkedList::GetArrowTypePrev(std::size_t index) {
    return arrowStatePrev[index];
}

void GUIVisualizer::DoublyLinkedList::ResetArrow() {
    std::size_t resize = std::max(0, int(list.size() - 1));
    arrowStateNext.assign(resize, ArrowType::Default);
    arrowStateNext.resize(resize);

    arrowStatePrev.assign(resize, ArrowType::Default);
    arrowStatePrev.resize(resize);
}

void GUIVisualizer::DoublyLinkedList::DrawArrow(Vector2 base, float t) {
    for (int i = 0; i < int(list.size()) - 1; i++) {
        if (list[i].GetNodeState() == GUIVisualizer::Node::State::Hide)
            continue;
        if ((arrowStateNext[i] == ArrowType::Hidden &&
             arrowStatePrev[i] == ArrowType::Hidden) ||
            (arrowStateNext[i] == ArrowType::Skip &&
             arrowStatePrev[i] == ArrowType::Skip))
            continue;

        Vector2 start = list[i].GetPosition();

        int nextIndex;
        for (nextIndex = i + 1; nextIndex < list.size(); nextIndex++)
            if (list[nextIndex].GetNodeState() ==
                    GUIVisualizer::Node::State::Hide ||
                (arrowStateNext[nextIndex] != ArrowType::Skip &&
                 arrowStatePrev[nextIndex] != ArrowType::Skip))
                break;

        if (nextIndex == list.size())
            break;  // all of the nodes behind the current node is hidden, so we
                    // don't need to draw any arrow
        Vector2 end = list[nextIndex].GetPosition();

        start.x += base.x, start.y += base.y;
        end.x += base.x, end.y += base.y;

        float lengthNext = (arrowStateNext[i] == ArrowType::Hidden ? 0.0f : t);
        float lengthPrev = (arrowStatePrev[i] == ArrowType::Hidden ? 0.0f : t);

        AnimationFactory::DrawDoubleDirectionalArrow(
            start, end, arrowStateNext[i] == ArrowType::Active,
            arrowStatePrev[i] == ArrowType::Active, lengthNext, lengthPrev);
    }
}

void GUIVisualizer::DoublyLinkedList::DeleteNode(std::size_t index,
                                                 bool rePosition) {
    list.erase(list.begin() + index);
    if (!arrowStateNext.empty()) {
        arrowStateNext.erase(arrowStateNext.begin() +
                             std::min(index, arrowStateNext.size() - 1));
        arrowStatePrev.erase(arrowStatePrev.begin() +
                             std::min(index, arrowStatePrev.size() - 1));
    }

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}
