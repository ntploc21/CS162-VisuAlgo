#ifndef COMPONENTS_GUIBUTTON_HPP
#define COMPONENTS_GUIBUTTON_HPP

#include <functional>

#include "../Component.hpp"
#include "../FontHolder.hpp"

class Button : public GUI::Component {
public:
    enum TextAlignment { Left, Center, Right, AlignmentCount };
    typedef std::shared_ptr< Button > Ptr;
    Button(std::string text, FontHolder* fonts);
    Button();
    ~Button();
    void Draw(Vector2 base = (Vector2){0, 0});

    void SetAction(std::function< void() > clickedAction);

    bool isSelectable() const;

public:
    void SetButtonHoverColor(Color color);
    void SetButtonColor(Color color);
    void SetTextColor(Color color);
    void SetSize(float width, float height);
    void SetText(std::string text);

public:
    void SetFontSize(float textFontSize);
    float GetFontSize() const;
    void SetTextAlignment(TextAlignment textAlignment);

    void EnableFitContent();
    void DisableFitContent();

    Vector2 GetSize();

    void SetActionOnHover(bool actionOnHover);

private:
    bool IsClicked();
    void DrawButtonText();
    Vector2 GetContentPos();
    Vector2 GetContentSize();

    void FitContent();

private:
    FontHolder* fonts;
    std::string content;
    Color buttonColor;
    Color buttonHoverColor;
    Color textColor;
    TextAlignment alignment;
    float fontSize;

private:
    bool fitContent;
    bool mActionOnHover;

private:
    bool isHover;
    Rectangle bound;
    std::function< void() > action;
};

#endif  // COMPONENTS_GUIBUTTON_HPP