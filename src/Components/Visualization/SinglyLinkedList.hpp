#ifndef COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP
#define COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP

#include "DataStructure.hpp"
#include "Node.hpp"

namespace GUI {
    class SinglyLinkedList : public GUI::DataStructure {
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

    private:
        FontHolder* fonts;
        std::vector< GUI::Node > list;
        std::vector< ArrowType > arrowState;

        ArrowType defaultArrowType = ArrowType::Default;
        bool mDisplayHeadAndTail;

        Orientation mOrientation = Orientation::Horizontal;

    public:
        SinglyLinkedList();
        SinglyLinkedList(FontHolder* fonts);
        ~SinglyLinkedList();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f,
                  bool init = false);

        void SetDefaultArrowType(ArrowType arrowType);
        void SetShowHeadAndTail(bool show);
        void SetOrientation(Orientation orientation);

    public:
        std::vector< GUI::Node >& GetList();
        GUI::Node GenerateNode(int value);
        void Import(std::vector< int > nodes);
        void InsertNode(std::size_t index, GUI::Node node,
                        bool rePosition = true);
        void DeleteNode(std::size_t index, bool rePosition = true);
        void Relayout();

    public:
        void SetArrowType(std::size_t index, ArrowType type);
        ArrowType GetArrowType(std::size_t index);
        void ResetArrow();

    private:
        void DrawArrow(Vector2 base, float t);

    private:
        Vector2 GetNodeDefaultPosition(std::size_t index);
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_SINGLYLINKEDLIST_HPP