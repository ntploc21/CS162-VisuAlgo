#ifndef COMPONENTS_VISUALIZATION_LINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_LINKEDLIST_HPP

#include "Container.hpp"
#include "Node.hpp"

namespace GUIVisualizer {
    class LinkedList : public GUI::Container {
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
        std::vector< Node > list;
        bool mDisplayHeadAndTail;

        Orientation mOrientation = Orientation::Horizontal;
        Node::Shape mShape = Node::Shape::Circle;

    public:
        void SetShape(Node::Shape shape);
        Node::Shape GetShape() const;

    public:
        LinkedList();
        LinkedList(FontHolder* fonts);
        ~LinkedList();
        bool isSelectable() const;
        virtual void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                          bool init = false) = 0;
        virtual std::size_t size() const;

        virtual void SetShowHeadAndTail(bool show);
        virtual void SetOrientation(Orientation orientation);

    public:
        virtual std::vector< Node >& GetList();
        virtual Node GenerateNode(int value);
        virtual void Import(std::vector< int > nodes);
        virtual void InsertNode(std::size_t index, Node node,
                                bool rePosition = true);
        virtual void DeleteNode(std::size_t index, bool rePosition = true);
        virtual void Relayout();

    protected:
        Vector2 GetNodeDefaultPosition(std::size_t index);
    };
};      // namespace GUIVisualizer

#endif  // COMPONENTS_VISUALIZATION_LINKEDLIST_HPP