
#ifndef COMPONENTS_VISUALIZATION_GUINODE_HPP
#define COMPONENTS_VISUALIZATION_GUINODE_HPP

#include "Component.hpp"
#include "FontHolder.hpp"

namespace GUI {
    class Node : public GUI::Component {
    public:
        Node(int value, FontHolder* fonts);
        Node();
        ~Node();
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0});
        void SetActive(bool active);
        bool IsActive();

    public:
        void SetValue(int value);
        // int GetValue() const;
        void SetLabel(std::string label);
        void ClearLabel();

        void SetRadius(float radius);

    private:
        int mValue;
        float mRadius;

        std::string mLabel;

    private:
        bool mActive;
        FontHolder* fonts;
        Color mDefaultColor;
        Color mActiveColor;
        Color mBorderColor;
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_GUINODE_HPP