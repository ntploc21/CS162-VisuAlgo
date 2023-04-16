#include "GuiNode.hpp"

#include <iostream>

GUI::Node::Node(int value, FontHolder* fonts)
    : fonts(fonts), mValue(value), mRadius(20.0f), mDefaultColor(WHITE),
      mActiveColor(ORANGE), mBorderColor(BLACK) {}

GUI::Node::Node()
    : mValue(0), mRadius(30.0f), mDefaultColor(WHITE), mActiveColor(ORANGE),
      mBorderColor(BLACK) {}

GUI::Node::~Node() {}

bool GUI::Node::isSelectable() const { return false; }

void GUI::Node::Draw(Vector2 base) {
    float width;
    float x = base.x + mPosition.x;
    float y = base.y + mPosition.y;

    DrawCircleV((Vector2){x, y}, mRadius, mBorderColor);
    DrawCircleV((Vector2){x, y}, 16.0f, mDefaultColor);

    // Draw Value
    width = MeasureTextEx(fonts->Get(Fonts::Default),
                          std::to_string(mValue).c_str(), 24, 0)
                .x;

    float valuePosX = x - width / 2;
    DrawTextEx(fonts->Get(Fonts::Default), std::to_string(mValue).c_str(),
               (Vector2){valuePosX, y - 12}, 24, 0, BLACK);

    // Draw Label
    width =
        MeasureTextEx(fonts->Get(Fonts::Default_Bold), mLabel.c_str(), 20, 0).x;

    float labelPosX = x - width / 2;
    DrawTextEx(fonts->Get(Fonts::Default_Bold), mLabel.c_str(),
               (Vector2){labelPosX, y + mRadius + 2}, 20, 0, RED);
}

void GUI::Node::SetActive(bool active) { mActive = active; }

bool GUI::Node::IsActive() { return mActive; }

void GUI::Node::SetValue(int value) { mValue = value; }

// int GUI::Node::GetValue() const { return mValue; }

void GUI::Node::SetLabel(std::string label) { mLabel = label; }

void GUI::Node::ClearLabel() { mLabel.clear(); }

void GUI::Node::SetRadius(float radius) { mRadius = radius; }
