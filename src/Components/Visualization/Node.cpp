#include "Node.hpp"

#include <iostream>

#include "Core/Animation/AnimationFactory.hpp"

GUI::Node::Node(int value, FontHolder* fonts)
    : fonts(fonts), mValue(value), mRadius(20.0f), valueFontSize(24),
      labelFontSize(20), mDefaultColor(WHITE), mActiveColor(ORANGE),
      mBorderColor(BLACK), animateNode(false), mNodeState(Default) {}

GUI::Node::Node()
    : mValue(0), mRadius(20.0f), valueFontSize(24), labelFontSize(20),
      mDefaultColor(WHITE), mActiveColor(ORANGE), mBorderColor(BLACK),
      animateNode(false), mNodeState(Default) {}

GUI::Node::~Node() {}

bool GUI::Node::isSelectable() const { return false; }

void GUI::Node::Draw(Vector2 base, float t) {
    float width;
    base.x += mPosition.x;
    base.y += mPosition.y;

    Color borderColor = BLACK;
    Color defaultColor = WHITE;
    Color valueColor = BLACK;
    if (animateNode) {
        if (GetNodeState() == State::Active) {
            borderColor = AnimationFactory::BlendColor(
                BLACK, (Color){255, 138, 39, 255}, t);
            defaultColor = AnimationFactory::BlendColor(
                WHITE, (Color){255, 138, 39, 255}, t);
            valueColor = AnimationFactory::BlendColor(BLACK, WHITE, t);
        } else if (GetNodeState() == State::Iterated) {
            borderColor = (Color){255, 138, 39, 255};
            defaultColor = AnimationFactory::BlendColor(
                (Color){255, 138, 39, 255}, WHITE, t);
            valueColor = AnimationFactory::BlendColor(
                WHITE, (Color){255, 138, 39, 255}, t);
        }
    } else {
        if (GetNodeState() == State::Active) {
            borderColor = (Color){255, 138, 39, 255};
            defaultColor = (Color){255, 138, 39, 255};
            valueColor = WHITE;
        } else if (GetNodeState() == State::Iterated) {
            borderColor = (Color){255, 138, 39, 255};
            defaultColor = WHITE;
            valueColor = (Color){255, 138, 39, 255};
        }
    }

    DrawCircleV((Vector2){base.x, base.y}, mRadius, borderColor);
    DrawCircleV((Vector2){base.x, base.y}, mRadius * 4 / 5, defaultColor);

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

void GUI::Node::SetValueFontSize(int fontSize) { valueFontSize = fontSize; }

void GUI::Node::SetLabelFontSize(int fontSize) { labelFontSize = fontSize; }

void GUI::Node::SetNodeState(State state) { mNodeState = state; }

GUI::Node::State GUI::Node::GetNodeState() const { return mNodeState; }
