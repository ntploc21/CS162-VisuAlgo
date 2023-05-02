#ifndef COMPONENTS_COMMON_CODEHIGHLIGHTER_HPP
#define COMPONENTS_COMMON_CODEHIGHLIGHTER_HPP

#include <vector>

// #include "Component.hpp"
#include "Button.hpp"

namespace GUIComponent {
    class CodeHighlighter : public GUI::Component {
    public:
        typedef std::shared_ptr< CodeHighlighter > Ptr;

    private:
        GUIComponent::Button mButtonShowCode;
        bool mShowCode;

        GUIComponent::Button mButtonShowAction;
        bool mShowActionDescription;

        FontHolder* fonts;

    private:
        std::vector< std::string > mCode;
        int mHighlightedLine;
        std::string mActionDescription;

    public:
        CodeHighlighter(FontHolder* fonts);
        ~CodeHighlighter();
        void Draw(Vector2 base = (Vector2){0, 0});
        bool isSelectable() const;
        void InitButtons();

    public:
        void AddCode(std::vector< std::string > code);
        void Highlight(int line);
        void ToggleShowCode();
        void ToggleShowAction();
        void SetShowCode(bool show);
        void SetShowAction(bool show);

    public:
        void AddActionDescription(std::string description);

    private:
        void DrawActionDescription(Vector2 base = (Vector2){0, 0});
        void DrawCodeHighlighter(Vector2 base = (Vector2){0, 0});
    };
};      // namespace GUIComponent

#endif  // COMPONENTS_COMMON_CODEHIGHLIGHTER_HPP