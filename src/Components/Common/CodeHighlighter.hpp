#ifndef COMPONENTS_COMMON_CODEHIGHLIGHTER_HPP
#define COMPONENTS_COMMON_CODEHIGHLIGHTER_HPP

#include <vector>

// #include "Component.hpp"
#include "Button.hpp"

namespace GUI {
    class CodeHighlighter : public GUI::Component {
    public:
        typedef std::shared_ptr< CodeHighlighter > Ptr;

    private:
        GUI::Button mButtonShowCode;
        bool mShowCode;

        GUI::Button mButtonShowAction;
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

    public:
        void AddActionDescription(std::string description);

    private:
        void DrawActionDescription(Vector2 base = (Vector2){0, 0});
        void DrawCodeHighlighter(Vector2 base = (Vector2){0, 0});
    };
};  // namespace GUI

#endif  // COMPONENTS_COMMON_CODEHIGHLIGHTER_HPP