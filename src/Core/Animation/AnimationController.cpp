// #include "AnimationController.hpp"

// #include <iostream>

// Animation::AnimationController::AnimationController()
//     : mSpeed(defaultSpeed), animationGroup({}), mCurrentAnimationIndex(0),
//       Playing(false) {}

// Animation::AnimationController::~AnimationController() {}
// void Animation::AnimationController::RunAll() {
//     if (animationGroup.empty()) return;
//     ResetCurrent();
//     SetAnimation(animationGroup.size() - 1);
//     animationGroup.back()->PlayingAt(animationGroup.back()->GetDuration());
// }
// void Animation::AnimationController::Reset() {
//     ResetCurrent();
//     SetAnimation(0);
// }
// void Animation::AnimationController::StepForward() {
//     ResetCurrent();
//     SetAnimation(mCurrentAnimationIndex + 1);
// }

// void Animation::AnimationController::StepBackward() {
//     ResetCurrent();
//     SetAnimation(mCurrentAnimationIndex - 1);
// }

// void Animation::AnimationController::SetAnimation(std::size_t index) {
//     if (0 <= index && index < GetNumAnimation()) {
//         mCurrentAnimationIndex = index;
//     }
// }

// std::size_t Animation::AnimationController::CurrentAnimationIndex() const {
//     return mCurrentAnimationIndex;
// }

// void Animation::AnimationController::AddAnimation(
//     AnimationState::Ptr animation) {
//     animationGroup.emplace_back(animation);
// }

// void Animation::AnimationController::PopAnimation() {
//     assert(GetNumAnimation() > 0);
//     animationGroup.pop_back();
// }

// void Animation::AnimationController::Pause() { Playing = false; }

// void Animation::AnimationController::ResetCurrent() {
//     if (animationGroup.empty()) return;
//     animationGroup[mCurrentAnimationIndex]->Reset();
// }

// void Animation::AnimationController::Continue() { Playing = true; }

// float Animation::AnimationController::GetAnimationDuration() {
//     float totalDuration = 0.0f;
//     for (auto &animation : animationGroup) {
//         totalDuration += animation.get()->GetDuration();
//     }
//     return totalDuration;
// }

// void Animation::AnimationController::Update(float dt) {
//     if (animationGroup.empty()) return;
//     animationGroup[mCurrentAnimationIndex].get()->Update(GetAnimateFrame(dt));
//     if (IsPlaying() && animationGroup[mCurrentAnimationIndex].get()->Done())
//     {
//         SetAnimation(mCurrentAnimationIndex + 1);
//     }
// }
// void Animation::AnimationController::SetSpeed(float speed) { mSpeed = speed;
// } float Animation::AnimationController::GetSpeed() const { return mSpeed; }

// Animation::AnimationState::Ptr Animation::AnimationController::GetAnimation()
// {
//     if (animationGroup.empty())
//         return AnimationState::Ptr(new Animation::AnimationState());
//     return animationGroup[mCurrentAnimationIndex];
// }

// float Animation::AnimationController::GetAnimateFrame(float dt) const {
//     if (!IsPlaying() || animationGroup.empty() ||
//     animationGroup.back()->Done())
//         return 0.0f;
//     return dt * mSpeed;
// }

// std::size_t Animation::AnimationController::GetNumAnimation() const {
//     return animationGroup.size();
// }

// std::size_t Animation::AnimationController::GetAnimationIndex() const {
//     return mCurrentAnimationIndex;
// }

// bool Animation::AnimationController::Done() const {
//     if (animationGroup.empty()) return true;
//     return animationGroup.back()->Done();
// }

// bool Animation::AnimationController::IsPlaying() const { return Playing; }
