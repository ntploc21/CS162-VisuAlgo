#include "AnimationController.hpp"

Animation::AnimationController::AnimationController()
    : mSpeed(defaultSpeed), animationGroup({}), mCurrentAnimationIndex(0),
      Playing(false) {}

Animation::AnimationController::~AnimationController() {}
void Animation::AnimationController::RunAll() {
    if (!animationGroup.size()) return;
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
    if (!animationGroup.size()) return;
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
    if (!animationGroup.size()) return;
    animationGroup[mCurrentAnimationIndex].get()->Update(GetAnimateFrame(dt));
}
void Animation::AnimationController::SetSpeed(float speed) { mSpeed = speed; }
float Animation::AnimationController::GetSpeed() const { return mSpeed; }

float Animation::AnimationController::GetAnimateFrame(float dt) const {
    if (!Playing || !animationGroup.size() || animationGroup.back()->Done())
        return 0.0f;
    return dt * mSpeed;
}

std::size_t Animation::AnimationController::GetNumAnimation() const {
    return animationGroup.size();
}

std::size_t Animation::AnimationController::GetAnimationIndex() const {
    return mCurrentAnimationIndex;
}

bool Animation::AnimationController::Done() {
    if (!animationGroup.size()) return true;
    return animationGroup.back()->Done();
}

bool Animation::AnimationController::IsPlaying() { return Playing; }
