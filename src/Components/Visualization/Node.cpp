#include "Node.hpp"

#include <iostream>

#include "Animation/AnimationFactory.hpp"
#include "Settings.hpp"

void GUIVisualizer::Node::SetShape(Shape shape) { mShape = shape; }

GUIVisualizer::Node::Shape GUIVisualizer::Node::GetShape() const {
    return mShape;
}

GUIVisualizer::Node::Node(int value, FontHolder* fonts)
    : fonts(fonts), mValue(value), mRadius(20.0f), valueFontSize(24),
      labelFontSize(20), mDefaultColor(WHITE), mActiveColor(ORANGE),
      mBorderColor(BLACK), animateNode(false), mNodeState(Default),
      mReachable(true) {
    AddColor();
}

GUIVisualizer::Node::Node()
    : mValue(0), mRadius(20.0f), valueFontSize(24), labelFontSize(20),
      mDefaultColor(WHITE), mActiveColor(ORANGE), mBorderColor(BLACK),
      animateNode(false), mNodeState(Default), mReachable(true) {
    AddColor();
}

GUIVisualizer::Node::~Node() {}

bool GUIVisualizer::Node::isSelectable() const { return false; }

void GUIVisualizer::Node::Draw(Vector2 base, float t) {
    if (mNodeState == State::Hide) return;
    float width;
    base.x += mPosition.x;
    base.y += mPosition.y;

    Color valueColor = GetTextColor(t);

    DrawNode(base, t);

    // Draw Value
    width = MeasureTextEx(fonts->Get(Fonts::Default),
                          std::to_string(mValue).c_str(), valueFontSize, 0)
                .x;

    float valuePosX = base.x - width / 2;
    DrawTextEx(fonts->Get(Fonts::Default), std::to_string(mValue).c_str(),
               (Vector2){valuePosX, base.y - 12}, valueFontSize, 0, valueColor);

    DrawLabel(base);
}

void GUIVisualizer::Node::SetActive(bool active) { mActive = active; }

bool GUIVisualizer::Node::IsActive() { return mActive; }

void GUIVisualizer::Node::SetValue(int value) { mValue = value; }

int GUIVisualizer::Node::GetValue() const { return mValue; }

void GUIVisualizer::Node::SetLabel(std::string label) { mLabel = label; }

void GUIVisualizer::Node::ClearLabel() { mLabel.clear(); }

void GUIVisualizer::Node::AnimationOnNode(bool animate) {
    animateNode = animate;
}

void GUIVisualizer::Node::SetRadius(float radius) { mRadius = radius; }

void GUIVisualizer::Node::DrawLabel(Vector2 base) {
    const Color labelColor =
        Settings::getInstance().getColor(ColorTheme::Visualizer_Label);
    // Draw Label
    float width = MeasureTextEx(fonts->Get(Fonts::Default_Bold), mLabel.c_str(),
                                labelFontSize, 0)
                      .x;

    float labelPosX = base.x - width / 2;
    DrawTextEx(fonts->Get(Fonts::Default_Bold), mLabel.c_str(),
               (Vector2){labelPosX, base.y + mRadius + 2}, labelFontSize, 0,
               labelColor);
}

void GUIVisualizer::Node::DrawNode(Vector2 base, float t) {
    Color borderColor = GetOutlineColor(t);
    Color defaultColor = GetBackgroundColor(t);
    Color valueColor = GetTextColor(t);

    if (mShape == Shape::Circle) {
        DrawCircleV((Vector2){base.x, base.y}, mRadius, borderColor);
        DrawCircleV((Vector2){base.x, base.y}, mRadius * 4 / 5, defaultColor);

        if (!GetReachable())
            DrawCircleV((Vector2){base.x, base.y}, mRadius,
                        (Color){0, 0, 0, 64});
    } else if (mShape == Shape::Square) {
        DrawRectangleRec((Rectangle){base.x - mRadius, base.y - mRadius,
                                     mRadius * 2, mRadius * 2},
                         borderColor);
        DrawRectangleRec(
            (Rectangle){base.x - mRadius * 4 / 5, base.y - mRadius * 4 / 5,
                        mRadius * 8 / 5, mRadius * 8 / 5},
            defaultColor);

        if (!GetReachable())
            DrawRectangleRec((Rectangle){base.x - mRadius, base.y - mRadius,
                                         mRadius * 2, mRadius * 2},
                             (Color){0, 0, 0, 64});
    }
}

void GUIVisualizer::Node::SetValueFontSize(int fontSize) {
    valueFontSize = fontSize;
}

void GUIVisualizer::Node::SetLabelFontSize(int fontSize) {
    labelFontSize = fontSize;
}

void GUIVisualizer::Node::SetNodeState(State state) { mNodeState = state; }

GUIVisualizer::Node::State GUIVisualizer::Node::GetNodeState() const {
    return mNodeState;
}

Color GUIVisualizer::Node::GetOutlineColor(float t) {
    Color src =
        Settings::getInstance().getColor(mOutlineColor[GetNodeState()].first);
    Color dst =
        Settings::getInstance().getColor(mOutlineColor[GetNodeState()].second);

    if (!animateNode) return dst;
    return AnimationFactory::BlendColor(src, dst, t);
}

Color GUIVisualizer::Node::GetBackgroundColor(float t) {
    Color src = Settings::getInstance().getColor(
        mBackgroundColor[GetNodeState()].first);
    Color dst = Settings::getInstance().getColor(
        mBackgroundColor[GetNodeState()].second);

    if (!animateNode) return dst;
    return AnimationFactory::BlendColor(src, dst, t);
}

Color GUIVisualizer::Node::GetTextColor(float t) {
    Color src =
        Settings::getInstance().getColor(mTextColor[GetNodeState()].first);
    Color dst =
        Settings::getInstance().getColor(mTextColor[GetNodeState()].second);

    if (!animateNode) return dst;
    return AnimationFactory::BlendColor(src, dst, t);
}

void GUIVisualizer::Node::AddColor() {
    // (src, dst)
    // Outline color
    mOutlineColor[State::Default] = {
        ColorTheme::Visualizer_Node_Default_Outline1,
        ColorTheme::Visualizer_Node_Default_Outline2};
    mOutlineColor[State::Active] = {
        ColorTheme::Visualizer_Node_Active_Outline1,
        ColorTheme::Visualizer_Node_Active_Outline2};
    mOutlineColor[State::ActiveBlue] = {
        ColorTheme::Visualizer_Node_ActiveBlue_Outline1,
        ColorTheme::Visualizer_Node_ActiveBlue_Outline2};
    mOutlineColor[State::ActiveGreen] = {
        ColorTheme::Visualizer_Node_ActiveGreen_Outline1,
        ColorTheme::Visualizer_Node_ActiveGreen_Outline2};
    mOutlineColor[State::Iterated] = {
        ColorTheme::Visualizer_Node_Iterated_Outline1,
        ColorTheme::Visualizer_Node_Iterated_Outline2};
    mOutlineColor[State::ActiveRed] = {
        ColorTheme::Visualizer_Node_ActiveRed_Outline1,
        ColorTheme::Visualizer_Node_ActiveRed_Outline2};

    // Background color
    mBackgroundColor[State::Default] = {
        ColorTheme::Visualizer_Node_Default_Background1,
        ColorTheme::Visualizer_Node_Default_Background2};
    mBackgroundColor[State::Active] = {
        ColorTheme::Visualizer_Node_Active_Background1,
        ColorTheme::Visualizer_Node_Active_Background2};
    mBackgroundColor[State::ActiveBlue] = {
        ColorTheme::Visualizer_Node_ActiveBlue_Background1,
        ColorTheme::Visualizer_Node_ActiveBlue_Background2};
    mBackgroundColor[State::ActiveGreen] = {
        ColorTheme::Visualizer_Node_ActiveGreen_Background1,
        ColorTheme::Visualizer_Node_ActiveGreen_Background2};
    mBackgroundColor[State::Iterated] = {
        ColorTheme::Visualizer_Node_Iterated_Background1,
        ColorTheme::Visualizer_Node_Iterated_Background2};
    mBackgroundColor[State::ActiveRed] = {
        ColorTheme::Visualizer_Node_ActiveRed_Background1,
        ColorTheme::Visualizer_Node_ActiveRed_Background2};

    // Text color
    mTextColor[State::Default] = {ColorTheme::Visualizer_Node_Default_Text1,
                                  ColorTheme::Visualizer_Node_Default_Text2};
    mTextColor[State::Active] = {ColorTheme::Visualizer_Node_Active_Text1,
                                 ColorTheme::Visualizer_Node_Active_Text2};
    mTextColor[State::ActiveBlue] = {
        ColorTheme::Visualizer_Node_ActiveBlue_Text1,
        ColorTheme::Visualizer_Node_ActiveBlue_Text2};
    mTextColor[State::ActiveGreen] = {
        ColorTheme::Visualizer_Node_ActiveGreen_Text1,
        ColorTheme::Visualizer_Node_ActiveGreen_Text2};
    mTextColor[State::Iterated] = {ColorTheme::Visualizer_Node_Iterated_Text1,
                                   ColorTheme::Visualizer_Node_Iterated_Text2};
    mTextColor[State::ActiveRed] = {
        ColorTheme::Visualizer_Node_ActiveRed_Text1,
        ColorTheme::Visualizer_Node_ActiveRed_Text2};
}

void GUIVisualizer::Node::SetReachable(bool reachable) {
    mReachable = reachable;
}

bool GUIVisualizer::Node::GetReachable() const { return mReachable; }
