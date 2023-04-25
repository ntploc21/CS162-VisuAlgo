#include "Node.hpp"

#include <iostream>

#include "Core/Animation/AnimationFactory.hpp"

void GUI::Node::SetShape(Shape shape) { mShape = shape; }

GUI::Node::Shape GUI::Node::GetShape() const { return mShape; }

GUI::Node::Node(int value, FontHolder* fonts)
    : fonts(fonts), mValue(value), mRadius(20.0f), valueFontSize(24),
      labelFontSize(20), mDefaultColor(WHITE), mActiveColor(ORANGE),
      mBorderColor(BLACK), animateNode(false), mNodeState(Default),
      mReachable(true) {
    AddColor();
}

GUI::Node::Node()
    : mValue(0), mRadius(20.0f), valueFontSize(24), labelFontSize(20),
      mDefaultColor(WHITE), mActiveColor(ORANGE), mBorderColor(BLACK),
      animateNode(false), mNodeState(Default), mReachable(true) {
    AddColor();
}

GUI::Node::~Node() {}

bool GUI::Node::isSelectable() const { return false; }

void GUI::Node::Draw(Vector2 base, float t) {
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

void GUI::Node::SetActive(bool active) { mActive = active; }

bool GUI::Node::IsActive() { return mActive; }

void GUI::Node::SetValue(int value) { mValue = value; }

int GUI::Node::GetValue() const { return mValue; }

void GUI::Node::SetLabel(std::string label) { mLabel = label; }

void GUI::Node::ClearLabel() { mLabel.clear(); }

void GUI::Node::AnimationOnNode(bool animate) { animateNode = animate; }

void GUI::Node::SetRadius(float radius) { mRadius = radius; }

void GUI::Node::DrawLabel(Vector2 base) {
    // Draw Label
    float width = MeasureTextEx(fonts->Get(Fonts::Default_Bold), mLabel.c_str(),
                                labelFontSize, 0)
                      .x;

    float labelPosX = base.x - width / 2;
    DrawTextEx(fonts->Get(Fonts::Default_Bold), mLabel.c_str(),
               (Vector2){labelPosX, base.y + mRadius + 2}, labelFontSize, 0,
               RED);
}

void GUI::Node::DrawNode(Vector2 base, float t) {
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

void GUI::Node::SetValueFontSize(int fontSize) { valueFontSize = fontSize; }

void GUI::Node::SetLabelFontSize(int fontSize) { labelFontSize = fontSize; }

void GUI::Node::SetNodeState(State state) { mNodeState = state; }

GUI::Node::State GUI::Node::GetNodeState() const { return mNodeState; }

Color GUI::Node::GetOutlineColor(float t) {
    Color src, dst;
    std::tie(src, dst) = mOutlineColor[GetNodeState()];

    if (!animateNode) return dst;
    return AnimationFactory::BlendColor(src, dst, t);
}

Color GUI::Node::GetBackgroundColor(float t) {
    Color src, dst;
    std::tie(src, dst) = mBackgroundColor[GetNodeState()];

    if (!animateNode) return dst;
    return AnimationFactory::BlendColor(src, dst, t);
}

Color GUI::Node::GetTextColor(float t) {
    Color src, dst;
    std::tie(src, dst) = mTextColor[GetNodeState()];

    if (!animateNode) return dst;
    return AnimationFactory::BlendColor(src, dst, t);
}

void GUI::Node::AddColor() {
    // (src, dst)
    // Outline color
    mOutlineColor[State::Default] = {BLACK, BLACK};
    mOutlineColor[State::Active] = {BLACK, (Color){255, 138, 39, 255}};
    mOutlineColor[State::ActiveBlue] = {BLACK, (Color){46, 187, 209, 255}};
    mOutlineColor[State::ActiveGreen] = {BLACK, (Color){82, 188, 105, 255}};
    mOutlineColor[State::Iterated] = {(Color){255, 138, 39, 255},
                                      (Color){255, 138, 39, 255}};
    mOutlineColor[State::ActiveRed] = {BLACK, (Color){217, 81, 60, 255}};

    // Background color
    mBackgroundColor[State::Default] = {WHITE, WHITE};
    mBackgroundColor[State::Active] = {WHITE, (Color){255, 138, 39, 255}};
    mBackgroundColor[State::ActiveBlue] = {WHITE, (Color){46, 187, 209, 255}};
    mBackgroundColor[State::ActiveGreen] = {WHITE, (Color){82, 188, 105, 255}};
    mBackgroundColor[State::Iterated] = {(Color){255, 138, 39, 255}, WHITE};
    mBackgroundColor[State::ActiveRed] = {WHITE, (Color){217, 81, 60, 255}};

    // Text color
    mTextColor[State::Default] = {BLACK, BLACK};
    mTextColor[State::Active] = {BLACK, WHITE};
    mTextColor[State::ActiveBlue] = {BLACK, WHITE};
    mTextColor[State::ActiveGreen] = {BLACK, WHITE};
    mTextColor[State::Iterated] = {WHITE, (Color){255, 138, 39, 255}};
    mTextColor[State::ActiveRed] = {BLACK, WHITE};
}

void GUI::Node::SetReachable(bool reachable) { mReachable = reachable; }

bool GUI::Node::GetReachable() const { return mReachable; }
