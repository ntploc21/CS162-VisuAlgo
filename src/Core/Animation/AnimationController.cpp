#include "AnimationController.hpp"

Animation::AnimationController::AnimationController() : mSpeed(defaultSpeed) {}

Animation::AnimationController::~AnimationController() {}
void Animation::AnimationController::RunAll() {
    ResetCurrent();
    SetAnimation(animationGroup.size() - 1);
    animationGroup.back()->PlayingAt(animationGroup.back()->GetDuration());
}
void Animation::AnimationController::Reset() {
    ResetCurrent();
    SetAnimation(0);
}
void Animation::AnimationController::StepForward() {
    ResetCurrent();
    SetAnimation(mCurrentAnimationIndex + 1);
}

void Animation::AnimationController::StepBackward() {
    ResetCurrent();
    SetAnimation(mCurrentAnimationIndex - 1);
}

void Animation::AnimationController::SetAnimation(std::size_t index) {
    mCurrentAnimationIndex = index;
}

std::size_t Animation::AnimationController::CurrentAnimationIndex() const {
    return mCurrentAnimationIndex;
}

void Animation::AnimationController::Pause() { Playing = false; }

void Animation::AnimationController::ResetCurrent() {
    animationGroup[mCurrentAnimationIndex]->Reset();
}

void Animation::AnimationController::Continue() { Playing = true; }

float Animation::AnimationController::GetAnimationDuration() {
    float totalDuration = 0.0f;
    for (auto &animation : animationGroup) {
        totalDuration += animation.get()->GetDuration();
    }
    return totalDuration;
}

void Animation::AnimationController::Update(float dt) {
    animationGroup[mCurrentAnimationIndex].get()->Update(GetAnimateFrame(dt));
}
void Animation::AnimationController::SetSpeed(float speed) {}
float Animation::AnimationController::GetSpeed() const { return 0.0f; }

float Animation::AnimationController::GetAnimateFrame(float dt) const {
    if (!Playing || animationGroup.back()->Done()) return 0.0f;
    return dt * mSpeed;
}
