#include "AnimationState.hpp"

#include <cassert>

Animation::AnimationState::AnimationState() {}

Animation::AnimationState::~AnimationState() {}

void Animation::AnimationState::SetDuration(float duration) {
    mDuration = duration;
}

float Animation::AnimationState::GetDuration() const { return mDuration; }

void Animation::AnimationState::SetAnimation(
    std::function< GUI::DataStructure(GUI::DataStructure, float, Vector2) >
        animation) {
    mAnimation = animation;
}

void Animation::AnimationState::PlayingAt(float playingAt) {
    mCurrentPlayingAt = playingAt;
}

float Animation::AnimationState::GetCurrentPlayingAt() const {
    return mCurrentPlayingAt;
}

void Animation::AnimationState::SetSourceDataStructure(
    GUI::DataStructure dataStructure) {
    mDataStructureBefore = dataStructure;
}

GUI::DataStructure Animation::AnimationState::GetDataStructure(float progress) {
    assert(progress >= 0.0f && progress <= 1.0f);
    return mAnimation(mDataStructureBefore, progress, (Vector2){0, 0});
}

void Animation::AnimationState::Draw(Vector2 base) {
    mAnimation(mDataStructureBefore,
               std::min(1.0f, mCurrentPlayingAt / mDuration), base);
}

void Animation::AnimationState::Update(float dt) { mCurrentPlayingAt += dt; }

void Animation::AnimationState::Reset() { PlayingAt(0.0f); }

bool Animation::AnimationState::Done() {
    return mCurrentPlayingAt >= mDuration;
}

void Animation::AnimationState::SetHighlightLine(int line) {
    mHighlightedLine = line;
}

int Animation::AnimationState::GetHighlightedLine() const {
    return mHighlightedLine;
}
