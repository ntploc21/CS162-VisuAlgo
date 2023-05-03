
#ifndef COMPONENTS_VISUALIZATION_GUINODE_HPP
#define COMPONENTS_VISUALIZATION_GUINODE_HPP

#include "Component.hpp"
#include "FontHolder.hpp"
#include "Identifiers/ColorThemeIdentifiers.hpp"

namespace GUIVisualizer {
    /**
     * @brief The node class that is used to represent a node in the
     * visualization.
     */
    class Node : public GUI::Component {
    public:
        /**
         * @brief The state of the node.
         * @details The state of the node is used to determine the color of the
         * node.
         */
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

        /**
         * @brief The shape of the node.
         * @details The shape of the node is used to determine the shape of the
         * node.
         */
        enum Shape {
            Circle,
            Square,

            ShapeCount,
        };

    private:
        /**
         * @brief The shape of the node, by default it is a circle.
         */
        Shape mShape = Shape::Circle;

    public:
        /**
         * @brief Set the shape of the node.
         */
        void SetShape(Shape shape);

        /**
         * @brief Get the shape of the node.
         */
        Shape GetShape() const;

    public:
        /**
         * @brief Construct a new Node object
         * @param value The value of the node.
         * @param fonts The fonts of the application.
         */
        Node(int value, FontHolder* fonts);

        /**
         * @brief Construct a new Node object
         * @param value The value of the node.
         * @param label The label of the node.
         * @param fonts The fonts of the application.
         */
        Node();

        /**
         * @brief Destroy the Node object
         */
        ~Node();

        /**
         * @brief Return true if the node is selectable.
         * @note The node is unselectable.
         */
        bool isSelectable() const;

        /**
         * @brief Draw the node.
         * @param base The base position of the node.
         * @param t The progress of the animation.
         */
        void Draw(Vector2 base = (Vector2){0, 0}, float t = 1.0f);

        /**
         * @brief Set the active state of the node.
         * @param active The active state of the node.
         */
        void SetActive(bool active);

        /**
         * @brief Return true if the node is active.
         */
        bool IsActive();

    public:
        /**
         * @brief Set the value of the node.
         * @param value The value of the node.
         */
        void SetValue(int value);

        /**
         * @brief Get the value of the node.
         */
        int GetValue() const;

        /**
         * @brief Set the label of the node.
         * @param label The label of the node.
         */
        void SetLabel(std::string label);

        /**
         * @brief Get the label of the node.
         */
        void ClearLabel();

    public:
        void AnimationOnNode(bool animate);
        void SetRadius(float radius);

    private:
        void DrawLabel(Vector2 base = (Vector2){0, 0});

        /**
         * @brief Draw the node.
         * @param base The base position of the node.
         * @param t The progress of the animation.
         */
        void DrawNode(Vector2 base = (Vector2){0, 0}, float t = 1.0f);

    public:
        void SetValueFontSize(int fontSize);
        void SetLabelFontSize(int fontSize);

        /**
         * @brief Set the color of the node.
         * @param color The color of the node.
         */
        void SetNodeState(State state);

        /**
         * @brief Get the color of the node.
         */
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
};      // namespace GUIVisualizer

#endif  // COMPONENTS_VISUALIZATION_GUINODE_HPP