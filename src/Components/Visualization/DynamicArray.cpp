#include "DynamicArray.hpp"

#include <math.h>

#include "Global.hpp"

GUI::DynamicArray::DynamicArray() : mShape(GUI::Node::Shape::Square) {}

GUI::DynamicArray::DynamicArray(FontHolder* fonts)
    : fonts(fonts), mShape(GUI::Node::Shape::Square) {}

bool GUI::DynamicArray::isSelectable() const { return false; }

GUI::DynamicArray::~DynamicArray() {}

void GUI::DynamicArray::Draw(Vector2 base, float t, bool init) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    for (auto node : list) {
        node.Draw(base, t);
    }
}

void GUI::DynamicArray::SetShape(GUI::Node::Shape shape) {
    mShape = shape;
    for (GUI::Node& node : list) node.SetShape(shape);
}

GUI::Node::Shape GUI::DynamicArray::GetShape() const { return mShape; }

void GUI::DynamicArray::Reserve(std::size_t size) {
    capacity = size;
    list.resize(size);
}

void GUI::DynamicArray::Resize(std::size_t size) {
    if (size > capacity) Reserve(GetCapacityFromLength(size));
    for (int i = size; i < length; i++) {
        list[i] = GenerateNode(0);
        list[i].SetReachable(false);
    }
    length = size;
}

void GUI::DynamicArray::Clear() { Resize(0); }

std::vector< GUI::Node >& GUI::DynamicArray::GetList() { return list; }

GUI::Node GUI::DynamicArray::GenerateNode(int value) {
    GUI::Node node = GUI::Node(value, fonts);
    node.SetShape(mShape);
    return node;
}

void GUI::DynamicArray::Import(std::vector< int > nodes) {
    list.clear();

    Reserve(GetCapacityFromLength(nodes.size()));

    float sizeX = 40 * capacity + mNodeDistance * (capacity - 1);

    SetPosition((global::SCREEN_WIDTH - sizeX) / 2, 150);

    length = nodes.size();
    for (int i = 0; i < capacity; i++) {
        GUI::Node guiNode = GenerateNode(0);
        if (i < length) guiNode.SetValue(nodes[i]);
        Vector2 newPos = GetNodeDefaultPosition(i);
        guiNode.SetPosition(newPos.x, newPos.y);

        if (i >= length) guiNode.SetReachable(false);
        list[i] = guiNode;
    }
}

void GUI::DynamicArray::InsertNode(std::size_t index, GUI::Node node,
                                   bool rePosition) {
    assert(index >= 0 && index <= list.size());
    if (length == capacity) {
        capacity = (!capacity ? 0 : capacity * 2);
        Reserve(capacity);
    }

    list.insert(list.begin() + index, node);
    length++;

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

void GUI::DynamicArray::Relayout() {
    std::vector< int > values;
    for (auto node : list) values.emplace_back(node.GetValue());
    Import(values);
}

void GUI::DynamicArray::DeleteNode(std::size_t index, bool rePosition) {
    list.erase(list.begin() + index);
    length--;

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

Vector2 GUI::DynamicArray::GetNodeDefaultPosition(std::size_t index) {
    Vector2 answer = (Vector2){index * (40 + mNodeDistance), 0};
    return answer;
}

// return capacity such that capacity = 2^x >= length (x smallest)
std::size_t GUI::DynamicArray::GetCapacityFromLength(std::size_t length) {
    if (length == 0) return 0;
    if (length == 1) return 1;
    return (1 << (int(log2(length - 1)) + 1));
}