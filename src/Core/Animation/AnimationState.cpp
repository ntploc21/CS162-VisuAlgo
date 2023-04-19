// #include "AnimationState.hpp"

// #include <cassert>
// #include <iostream>

// Animation::AnimationState::AnimationState()
//     : mCurrentPlayingAt(0.0f), mDuration(0.0f), mHighlightedLine(-1),
//       mDataStructureBefore(nullptr) {
//     mAnimation = [](GUI::DataStructure::Ptr srcDS, float playingAt,
//                     Vector2 base) { return srcDS; };
// }

// Animation::AnimationState::~AnimationState() {}

// void Animation::AnimationState::SetDuration(float duration) {
//     mDuration = duration;
// }

// float Animation::AnimationState::GetDuration() const { return mDuration; }

// void Animation::AnimationState::SetAnimation(
//     std::function< GUI::DataStructure::Ptr(GUI::DataStructure::Ptr, float,
//                                            Vector2) >
//         animation) {
//     mAnimation = animation;
// }

// void Animation::AnimationState::PlayingAt(float playingAt) {
//     mCurrentPlayingAt = playingAt;
// }

// float Animation::AnimationState::GetCurrentPlayingAt() const {
//     return mCurrentPlayingAt;
// }

// void Animation::AnimationState::SetSourceDataStructure(
//     GUI::DataStructure::Ptr dataStructure) {
//     mDataStructureBefore = dataStructure;
// }

// GUI::DataStructure::Ptr Animation::AnimationState::GetDataStructure(
//     float progress, Vector2 base) {
//     assert(progress >= 0.0f && progress <= 1.0f);
//     return mAnimation(mDataStructureBefore, progress, base);
// }

// void Animation::AnimationState::Update(float dt) {
//     mCurrentPlayingAt += dt;
//     if (mCurrentPlayingAt > mDuration) mCurrentPlayingAt = mDuration;
// }

// void Animation::AnimationState::Reset() { PlayingAt(0.0f); }

// bool Animation::AnimationState::Done() {
//     return mCurrentPlayingAt == mDuration;
// }

// void Animation::AnimationState::SetHighlightLine(int line) {
//     mHighlightedLine = line;
// }

// int Animation::AnimationState::GetHighlightedLine() const {
//     return mHighlightedLine;
// }
