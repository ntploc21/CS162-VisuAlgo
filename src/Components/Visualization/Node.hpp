
#ifndef COMPONENTS_VISUALIZATION_GUINODE_HPP
#define COMPONENTS_VISUALIZATION_GUINODE_HPP

#include "Component.hpp"
#include "FontHolder.hpp"
#include "Identifiers/ColorThemeIdentifiers.hpp"

namespace GUI {
    class Node : public GUI::Component {
    public:
        enum State {
            Default,
            Active,
            ActiveBlue,
            ActiveGreen,
            ActiveRed,
            Iterated,
            Hide,
            StateCount,
        };

        enum Shape {
            Circle,
            Square,

            ShapeCount,
        };

    private:
        Shape mShape = Shape::Circle;

    public:
        void SetShape(Shape shape);
        Shape GetShape() const;

    public:
        Node(int value, FontHolder* fonts);
        Node();
        ~Node();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f);
        void SetActive(bool active);
        bool IsActive();

    public:
        void SetValue(int value);
        int GetValue() const;
        void SetLabel(std::string label);
        void ClearLabel();

    public:
        void AnimationOnNode(bool animate);
        void SetRadius(float radius);

    private:
        void DrawLabel(Vector2 base = (Vector2){0, 0});
        void DrawNode(Vector2 base = (Vector2){0, 0}, float t = 1.0f);

    public:
        void SetValueFontSize(int fontSize);
        void SetLabelFontSize(int fontSize);

        void SetNodeState(State state);
        State GetNodeState() const;

    private:
        Color GetOutlineColor(float t = 1.0f);
        Color GetBackgroundColor(float t = 1.0f);
        Color GetTextColor(float t = 1.0f);
        void AddColor();

    public:
        void SetReachable(bool reachable);
        bool GetReachable() const;

    private:
        std::map< State, std::pair< ColorTheme::ID, ColorTheme::ID > >
            mOutlineColor;
        std::map< State, std::pair< ColorTheme::ID, ColorTheme::ID > >
            mBackgroundColor;
        std::map< State, std::pair< ColorTheme::ID, ColorTheme::ID > >
            mTextColor;

    private:
        int mValue;
        float mRadius;
        float valueFontSize;
        float labelFontSize;

        std::string mLabel;
        State mNodeState;
        bool mReachable;

    private:
        bool animateNode;
        bool mActive;
        FontHolder* fonts;
        Color mDefaultColor;
        Color mActiveColor;
        Color mBorderColor;
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_GUINODE_HPP