#ifndef COMPONENTS_VISUALIZATION_DYNAMICARRAY_HPP
#define COMPONENTS_VISUALIZATION_DYNAMICARRAY_HPP

#include "DataStructure.hpp"

namespace GUI {
    class DynamicArray : public GUI::DataStructure {
    public:
        DynamicArray();
        DynamicArray(FontHolder* fonts);
        bool isSelectable() const;
        ~DynamicArray();

        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

    public:
        std::size_t GetLength() const;
        std::size_t GetCapacity() const;
        GUI::Node& operator[](std::size_t index);
        const GUI::Node& operator[](std::size_t index) const;

    public:
        void SetShape(GUI::Node::Shape shape);
        GUI::Node::Shape GetShape() const;

    public:
        void Reserve(std::size_t size);
        void Resize(std::size_t size);
        void Clear();

    public:
        std::vector< GUI::Node >& GetList();
        GUI::Node GenerateNode(int value);
        void Import(std::vector< int > nodes);
        void InsertNode(std::size_t index, GUI::Node node,
                        bool rePosition = true);
        void Relayout();
        void DeleteNode(std::size_t index, bool rePosition = true);

    private:
        Vector2 GetNodeDefaultPosition(std::size_t index);

    public:
        std::size_t GetCapacityFromLength(std::size_t length);

    public:
        static constexpr float mNodeDistance = 20;

    private:
        FontHolder* fonts;
        std::vector< GUI::Node > list;
        GUI::Node::Shape mShape;

    private:
        std::size_t capacity;
        std::size_t length;
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_DYNAMICARRAY_HPP