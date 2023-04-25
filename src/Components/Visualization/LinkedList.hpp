#ifndef COMPONENTS_VISUALIZATION_LINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_LINKEDLIST_HPP

#include "DataStructure.hpp"
#include "Node.hpp"

namespace GUI {
    class LinkedList : public GUI::DataStructure {
    public:
        enum ArrowType {
            Default,
            Hidden,
            Active,
            Skip,
            ArrowTypeCount,
        };
        enum Orientation {
            Horizontal,
            Vertical,

            OrientationCount,
        };

    public:
        static constexpr float mNodeDistance = 20;

    protected:
        FontHolder* fonts;
        std::vector< GUI::Node > list;
        bool mDisplayHeadAndTail;

        Orientation mOrientation = Orientation::Horizontal;
        GUI::Node::Shape mShape = GUI::Node::Shape::Circle;

    public:
        void SetShape(GUI::Node::Shape shape);
        GUI::Node::Shape GetShape() const;

    public:
        LinkedList();
        LinkedList(FontHolder* fonts);
        ~LinkedList();
        bool isSelectable() const;
        virtual void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                          bool init = false) = 0;

        virtual void SetShowHeadAndTail(bool show);
        virtual void SetOrientation(Orientation orientation);

    public:
        virtual std::vector< GUI::Node >& GetList();
        virtual GUI::Node GenerateNode(int value);
        virtual void Import(std::vector< int > nodes);
        virtual void InsertNode(std::size_t index, GUI::Node node,
                                bool rePosition = true);
        virtual void DeleteNode(std::size_t index, bool rePosition = true);
        virtual void Relayout();

    protected:
        Vector2 GetNodeDefaultPosition(std::size_t index);
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_LINKEDLIST_HPP