#include "CodeHighlighter.hpp"

#include <iostream>

#include "Utils.hpp"

GUI::CodeHighlighter::CodeHighlighter(FontHolder *fonts)
    : fonts(fonts), mShowCode(false), mShowActionDescription(false) {
    mButtonShowAction = GUI::Button(">", fonts);
    mButtonShowCode = GUI::Button(">", fonts);
}

GUI::CodeHighlighter::~CodeHighlighter() {}

void GUI::CodeHighlighter::Draw(Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    mButtonShowAction.Draw(base);
    mButtonShowCode.Draw(base);
    DrawActionDescription((Vector2){base.x - 4, base.y});
    DrawCodeHighlighter((Vector2){base.x - 4, base.y + 64});
}

bool GUI::CodeHighlighter::isSelectable() const { return false; }

void GUI::CodeHighlighter::AddCode(std::vector< std::string > code) {
    mHighlightedLine = -1;
    mCode = code;
}

void GUI::CodeHighlighter::Highlight(int line) {
    if (!(line >= 0 && line <= mCode.size())) line = -1;
    mHighlightedLine = line;
}

void GUI::CodeHighlighter::ToggleShowCode() {
    if (mShowCode) {
        mButtonShowCode.SetText(">");
        mShowCode = false;
    } else {
        mButtonShowCode.SetText("<");
        mShowCode = true;
    }
}

void GUI::CodeHighlighter::ToggleShowAction() {
    if (mShowActionDescription) {
        mButtonShowAction.SetText(">");
        mShowActionDescription = false;
    } else {
        mButtonShowAction.SetText("<");
        mShowActionDescription = true;
    }
}

void GUI::CodeHighlighter::SetShowCode(bool show) {
    if (show) {
        mButtonShowCode.SetText("<");
        mShowCode = true;
    } else {
        mButtonShowCode.SetText(">");
        mShowCode = false;
    }
}

void GUI::CodeHighlighter::SetShowAction(bool show) {
    if (show) {
        mButtonShowAction.SetText("<");
        mShowActionDescription = true;
    } else {
        mButtonShowAction.SetText(">");
        mShowActionDescription = false;
    }
}

void GUI::CodeHighlighter::AddActionDescription(std::string description) {
    mActionDescription = description;
}

void GUI::CodeHighlighter::DrawActionDescription(Vector2 base) {
    if (!mShowActionDescription) return;
    float x = base.x - 450;
    float y = base.y;
    DrawRectangleRec((Rectangle){x, y, 450, 60}, (Color){255, 138, 39, 255});
    Utils::DrawTextBoxed(fonts->Get(Fonts::Default), mActionDescription.c_str(),
                         (Rectangle){x + 5, y + 4, 450, 60}, 20, 0, true,
                         WHITE);
}

void GUI::CodeHighlighter::DrawCodeHighlighter(Vector2 base) {
    if (!mShowCode) return;
    float x = base.x - 450;
    float y = base.y;

    DrawRectangleRec((Rectangle){x, y, 450, 210}, (Color){46, 187, 209, 255});

    float fontSize = 15;
    for (int i = 0; i < mCode.size(); i++) {
        Color textColor = WHITE;
        if (i == mHighlightedLine) {
            DrawRectangleRec((Rectangle){x, y + i * 30, 450, 30}, BLACK);
        }
        float textX = x + 5;
        float textY = y + i * 30 + 8;
        DrawTextEx(fonts->Get(Fonts::Courier), mCode[i].c_str(),
                   (Vector2){textX, textY}, fontSize, 0, textColor);
    }
}

void GUI::CodeHighlighter::InitButtons() {
    mButtonShowAction.SetSize(40, 60);
    mButtonShowAction.SetTextAlignment(mButtonShowAction.Center);
    mButtonShowAction.SetFontSize(32);
    mButtonShowAction.SetButtonColor((Color){255, 138, 39, 255});
    mButtonShowAction.SetButtonHoverColor((Color){255, 138, 39, 255});
    mButtonShowAction.SetAction([this]() { this->ToggleShowAction(); });

    mButtonShowCode.SetPosition(0, 64);
    mButtonShowCode.SetSize(40, 210);
    mButtonShowCode.SetTextAlignment(mButtonShowAction.Center);
    mButtonShowCode.SetFontSize(32);
    mButtonShowCode.SetButtonColor((Color){46, 187, 209, 255});
    mButtonShowCode.SetButtonHoverColor((Color){46, 187, 209, 255});
    mButtonShowCode.SetAction([this]() { this->ToggleShowCode(); });
}
