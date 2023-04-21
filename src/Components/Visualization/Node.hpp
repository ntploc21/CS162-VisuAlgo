
#ifndef COMPONENTS_VISUALIZATION_GUINODE_HPP
#define COMPONENTS_VISUALIZATION_GUINODE_HPP

#include "Component.hpp"
#include "FontHolder.hpp"

namespace GUI {
    class Node : public GUI::Component {
    public:
        enum State {
            Default,
            Active,
            ActiveBlue,
            ActiveGreen,
            Iterated,
            Count,
        };

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

    private:
        std::map< State, std::pair< Color, Color > > mOutlineColor;
        std::map< State, std::pair< Color, Color > > mBackgroundColor;
        std::map< State, std::pair< Color, Color > > mTextColor;

    private:
        int mValue;
        float mRadius;
        float valueFontSize;
        float labelFontSize;

        std::string mLabel;
        State mNodeState;

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