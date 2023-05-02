#include "DynamicArray.hpp"

#include <math.h>

#include "Global.hpp"

GUIVisualizer::DynamicArray::DynamicArray()
    : mShape(GUIVisualizer::Node::Shape::Square) {}

GUIVisualizer::DynamicArray::DynamicArray(FontHolder* fonts)
    : fonts(fonts), mShape(GUIVisualizer::Node::Shape::Square) {}

bool GUIVisualizer::DynamicArray::isSelectable() const { return false; }

GUIVisualizer::DynamicArray::~DynamicArray() {}

void GUIVisualizer::DynamicArray::Draw(Vector2 base, float t, bool init) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    for (auto node : list) {
        node.Draw(base, t);
    }
}

std::size_t GUIVisualizer::DynamicArray::GetLength() const { return length; }

std::size_t GUIVisualizer::DynamicArray::GetCapacity() const {
    return capacity;
}

GUIVisualizer::Node& GUIVisualizer::DynamicArray::operator[](
    std::size_t index) {
    if (index >= length)
        throw std::to_string(index) +
            " >= (length = " + std::to_string(length) +
            "), variable inaccessible";
    return list.at(index);
}

const GUIVisualizer::Node& GUIVisualizer::DynamicArray::operator[](
    std::size_t index) const {
    if (index >= length)
        throw std::to_string(index) +
            " >= (length = " + std::to_string(length) +
            "), variable inaccessible";
    return list.at(index);
}

void GUIVisualizer::DynamicArray::SetShape(GUIVisualizer::Node::Shape shape) {
    mShape = shape;
    for (GUIVisualizer::Node& node : list) node.SetShape(shape);
}

GUIVisualizer::Node::Shape GUIVisualizer::DynamicArray::GetShape() const {
    return mShape;
}

void GUIVisualizer::DynamicArray::Reserve(std::size_t size) {
    list.resize(size);
    if (size > capacity) {
        for (int i = capacity; i < size; i++) {
            GUIVisualizer::Node guiNode = GenerateNode(0);
            Vector2 newPos = GetNodeDefaultPosition(i);
            guiNode.SetPosition(newPos.x, newPos.y);
            guiNode.SetReachable(false);
            list[i] = guiNode;
        }
    }
    capacity = size;
}

void GUIVisualizer::DynamicArray::Resize(std::size_t size) {
    if (size > capacity) Reserve(GetCapacityFromLength(size));
    for (int i = size; i < length; i++) {
        list[i] = GenerateNode(0);
        list[i].SetReachable(false);
    }
    length = size;
}

void GUIVisualizer::DynamicArray::Clear() { Resize(0); }

std::vector< GUIVisualizer::Node >& GUIVisualizer::DynamicArray::GetList() {
    return list;
}

GUIVisualizer::Node GUIVisualizer::DynamicArray::GenerateNode(int value) {
    GUIVisualizer::Node node = GUIVisualizer::Node(value, fonts);
    node.SetShape(mShape);
    return node;
}

void GUIVisualizer::DynamicArray::Import(std::vector< int > nodes) {
    list.clear();

    Reserve(GetCapacityFromLength(nodes.size()));

    float sizeX = 40 * capacity + mNodeDistance * (capacity - 1);

    SetPosition((global::SCREEN_WIDTH - sizeX) / 2, 150);

    length = nodes.size();
    for (int i = 0; i < capacity; i++) {
        GUIVisualizer::Node guiNode = GenerateNode(0);
        if (i < length) guiNode.SetValue(nodes[i]);
        Vector2 newPos = GetNodeDefaultPosition(i);
        guiNode.SetPosition(newPos.x, newPos.y);

        if (i >= length) guiNode.SetReachable(false);
        list[i] = guiNode;
    }
}

void GUIVisualizer::DynamicArray::InsertNode(std::size_t index,
                                             GUIVisualizer::Node node,
                                             bool rePosition) {
    assert(index >= 0 && index <= list.size());
    if (length == capacity) {
        capacity = (!capacity ? 0 : capacity * 2);
        Reserve(capacity);
    }

    for (int i = list.size() - 1; i > index; i--) {
        list[i] = list[i - 1];
    }
    list[index] = node;
    length++;

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

void GUIVisualizer::DynamicArray::Relayout() {
    std::vector< int > values;
    for (auto node : list) values.emplace_back(node.GetValue());
    Import(values);
}

void GUIVisualizer::DynamicArray::DeleteNode(std::size_t index,
                                             bool rePosition) {
    if (index >= length)
        throw std::to_string(index) +
            " >= (length = " + std::to_string(length) +
            "), variable inaccessible";
    list.erase(list.begin() + index);
    list.push_back(GenerateNode(0));
    list.back().SetReachable(false);
    length--;

    if (!rePosition) return;
    for (int i = index; i < list.size(); i++) {
        Vector2 newPos = GetNodeDefaultPosition(i);
        list.at(i).SetPosition(newPos.x, newPos.y);
    }
}

Vector2 GUIVisualizer::DynamicArray::GetNodeDefaultPosition(std::size_t index) {
    Vector2 answer = (Vector2){index * (40 + mNodeDistance), 0};
    return answer;
}

// return capacity such that capacity = 2^x >= length (x smallest)
std::size_t GUIVisualizer::DynamicArray::GetCapacityFromLength(
    std::size_t length) {
    if (length == 0) return 0;
    if (length == 1) return 1;
    return (1 << (int(log2(length - 1)) + 1));
}