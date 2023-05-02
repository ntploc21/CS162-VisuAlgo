#include "CodeHighlighter.hpp"

#include "Settings.hpp"
#include "Utils/Utils.hpp"

GUIComponent::CodeHighlighter::CodeHighlighter(FontHolder *fonts)
    : fonts(fonts), mShowCode(false), mShowActionDescription(false) {
    mButtonShowAction = GUIComponent::Button(">", fonts);
    mButtonShowCode = GUIComponent::Button(">", fonts);
}

GUIComponent::CodeHighlighter::~CodeHighlighter() {}

void GUIComponent::CodeHighlighter::Draw(Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    mButtonShowAction.Draw(base);
    mButtonShowCode.Draw(base);
    DrawActionDescription((Vector2){base.x - 4, base.y});
    DrawCodeHighlighter((Vector2){base.x - 4, base.y + 64});
}

bool GUIComponent::CodeHighlighter::isSelectable() const { return false; }

void GUIComponent::CodeHighlighter::AddCode(std::vector< std::string > code) {
    mHighlightedLine = -1;
    mCode = code;
}

void GUIComponent::CodeHighlighter::Highlight(int line) {
    if (!(line >= 0 && line <= mCode.size())) line = -1;
    mHighlightedLine = line;
}

void GUIComponent::CodeHighlighter::ToggleShowCode() {
    if (mShowCode) {
        mButtonShowCode.SetText(">");
        mShowCode = false;
    } else {
        mButtonShowCode.SetText("<");
        mShowCode = true;
    }
}

void GUIComponent::CodeHighlighter::ToggleShowAction() {
    if (mShowActionDescription) {
        mButtonShowAction.SetText(">");
        mShowActionDescription = false;
    } else {
        mButtonShowAction.SetText("<");
        mShowActionDescription = true;
    }
}

void GUIComponent::CodeHighlighter::SetShowCode(bool show) {
    if (show) {
        mButtonShowCode.SetText("<");
        mShowCode = true;
    } else {
        mButtonShowCode.SetText(">");
        mShowCode = false;
    }
}

void GUIComponent::CodeHighlighter::SetShowAction(bool show) {
    if (show) {
        mButtonShowAction.SetText("<");
        mShowActionDescription = true;
    } else {
        mButtonShowAction.SetText(">");
        mShowActionDescription = false;
    }
}

void GUIComponent::CodeHighlighter::AddActionDescription(
    std::string description) {
    mActionDescription = description;
}

void GUIComponent::CodeHighlighter::DrawActionDescription(Vector2 base) {
    if (!mShowActionDescription) return;
    const Color backgroundColor = Settings::getInstance().getColor(
        ColorTheme::ActionDescription_Background);
    const Color textColor =
        Settings::getInstance().getColor(ColorTheme::ActionDescription_Text);

    float x = base.x - 450;
    float y = base.y;
    DrawRectangleRec((Rectangle){x, y, 450, 60}, backgroundColor);
    Utils::DrawTextBoxed(fonts->Get(Fonts::Default), mActionDescription.c_str(),
                         (Rectangle){x + 5, y + 4, 450, 60}, 20, 0, true,
                         textColor);
}

void GUIComponent::CodeHighlighter::DrawCodeHighlighter(Vector2 base) {
    if (!mShowCode) return;
    const Color backgroundColor = Settings::getInstance().getColor(
        ColorTheme::CodeHighlighter_Background);
    const Color textColor =
        Settings::getInstance().getColor(ColorTheme::CodeHighlighter_Text);
    const Color highlightColor = Settings::getInstance().getColor(
        ColorTheme::CodeHighlighter_HighlightedLineBackground);

    float x = base.x - 450;
    float y = base.y;

    DrawRectangleRec((Rectangle){x, y, 450, 210}, backgroundColor);

    float fontSize = 15;
    for (int i = 0; i < mCode.size(); i++) {
        if (i == mHighlightedLine) {
            DrawRectangleRec((Rectangle){x, y + i * 30, 450, 30},
                             highlightColor);
        }
        float textX = x + 5;
        float textY = y + i * 30 + 8;
        DrawTextEx(fonts->Get(Fonts::Courier), mCode[i].c_str(),
                   (Vector2){textX, textY}, fontSize, 0, textColor);
    }
}

void GUIComponent::CodeHighlighter::InitButtons() {
    mButtonShowAction.SetSize(40, 60);
    mButtonShowAction.SetTextAlignment(mButtonShowAction.Center);
    mButtonShowAction.SetFontSize(32);
    mButtonShowAction.SetButtonColor(ColorTheme::ActionDescription_Background);
    mButtonShowAction.SetButtonHoverColor(
        ColorTheme::ActionDescription_Background);
    mButtonShowAction.SetAction([this]() { this->ToggleShowAction(); });

    mButtonShowCode.SetPosition(0, 64);
    mButtonShowCode.SetSize(40, 210);
    mButtonShowCode.SetTextAlignment(mButtonShowAction.Center);
    mButtonShowCode.SetFontSize(32);
    mButtonShowCode.SetButtonColor(ColorTheme::CodeHighlighter_Background);
    mButtonShowCode.SetButtonHoverColor(ColorTheme::CodeHighlighter_Background);
    mButtonShowCode.SetAction([this]() { this->ToggleShowCode(); });
}
