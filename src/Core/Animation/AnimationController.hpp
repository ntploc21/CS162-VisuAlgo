#ifndef CORE_ANIMATION_ANIMATIONCONTROLLER_HPP
#define CORE_ANIMATION_ANIMATIONCONTROLLER_HPP

#include "AnimationState.hpp"
#include "Container.hpp"

namespace Animation {
    template< typename T = SLLAnimation >
    class AnimationController {
    public:
        typedef std::shared_ptr< AnimationController > Ptr;

    private:
        std::vector< T > animationGroup;
        static constexpr float defaultSpeed = 1;

    private:
        std::size_t mCurrentAnimationIndex;
        float mSpeed;
        bool Playing;

    public:
        AnimationController();
        ~AnimationController();
        void RunAll();
        void Reset();
        void ResetCurrent();

        void SetAnimation(std::size_t animationIndex);
        std::size_t CurrentAnimationIndex() const;

    public:
        void AddAnimation(T animation);
        void PopAnimation();

    public:
        float GetAnimationDuration();
        float GetAnimateFrame(float dt) const;
        std::size_t GetNumAnimation() const;
        std::size_t GetAnimationIndex() const;
        bool Done() const;
        bool IsPlaying() const;

    public:
        void StepForward();
        void StepBackward();

    public:
        void Pause();
        void Continue();

    public:
        void Update(float dt);
        void SetSpeed(float speed);
        float GetSpeed() const;

    public:
        T GetAnimation();
    };
};  // namespace Animation

#include <iostream>

template< typename T >
Animation::AnimationController< T >::AnimationController()
    : mSpeed(defaultSpeed), animationGroup({}), mCurrentAnimationIndex(0),
      Playing(false) {}

template< typename T >
Animation::AnimationController< T >::~AnimationController() {}

template< typename T >
void Animation::AnimationController< T >::RunAll() {
    if (animationGroup.empty()) return;
    ResetCurrent();
    SetAnimation(animationGroup.size() - 1);
    animationGroup.back().PlayingAt(animationGroup.back().GetDuration());
}

template< typename T >
void Animation::AnimationController< T >::Reset() {
    ResetCurrent();
    SetAnimation(0);
}

template< typename T >
void Animation::AnimationController< T >::StepForward() {
    ResetCurrent();
    SetAnimation(mCurrentAnimationIndex + 1);
}

template< typename T >
void Animation::AnimationController< T >::StepBackward() {
    ResetCurrent();
    SetAnimation(mCurrentAnimationIndex - 1);
}

template< typename T >
void Animation::AnimationController< T >::SetAnimation(std::size_t index) {
    if (0 <= index && index < GetNumAnimation()) {
        mCurrentAnimationIndex = index;
    }
}

template< typename T >
std::size_t Animation::AnimationController< T >::CurrentAnimationIndex() const {
    return mCurrentAnimationIndex;
}

template< typename T >
void Animation::AnimationController< T >::AddAnimation(T animation) {
    animationGroup.emplace_back(animation);
}

template< typename T >
void Animation::AnimationController< T >::PopAnimation() {
    assert(GetNumAnimation() > 0);
    animationGroup.pop_back();
}

template< typename T >
void Animation::AnimationController< T >::Pause() {
    Playing = false;
}

template< typename T >
void Animation::AnimationController< T >::ResetCurrent() {
    if (animationGroup.empty()) return;
    animationGroup[mCurrentAnimationIndex].Reset();
}

template< typename T >
void Animation::AnimationController< T >::Continue() {
    Playing = true;
}

template< typename T >
float Animation::AnimationController< T >::GetAnimationDuration() {
    float totalDuration = 0.0f;
    for (auto &animation : animationGroup) {
        totalDuration += animation.GetDuration();
    }
    return totalDuration;
}

template< typename T >
void Animation::AnimationController< T >::Update(float dt) {
    if (animationGroup.empty()) return;
    animationGroup[mCurrentAnimationIndex].Update(GetAnimateFrame(dt));
    if (IsPlaying() && animationGroup[mCurrentAnimationIndex].Done()) {
        SetAnimation(mCurrentAnimationIndex + 1);
    }
}

template< typename T >
void Animation::AnimationController< T >::SetSpeed(float speed) {
    mSpeed = speed;
}

template< typename T >
float Animation::AnimationController< T >::GetSpeed() const {
    return mSpeed;
}

template< typename T >
T Animation::AnimationController< T >::GetAnimation() {
    if (animationGroup.empty()) return T();
    return animationGroup[mCurrentAnimationIndex];
}

template< typename T >
float Animation::AnimationController< T >::GetAnimateFrame(float dt) const {
    if (!IsPlaying() || animationGroup.empty() || Done()) return 0.0f;
    return dt * mSpeed;
}

template< typename T >
std::size_t Animation::AnimationController< T >::GetNumAnimation() const {
    return animationGroup.size();
}

template< typename T >
std::size_t Animation::AnimationController< T >::GetAnimationIndex() const {
    return mCurrentAnimationIndex;
}

template< typename T >
bool Animation::AnimationController< T >::Done() const {
    if (animationGroup.empty()) return true;
    return animationGroup.back().Done();
}

template< typename T >
bool Animation::AnimationController< T >::IsPlaying() const {
    return Playing;
}

/* */
typedef Animation::AnimationController< SLLAnimation > SLLAnimationController;

#endif  // CORE_ANIMATION_ANIMATIONCONTROLLER_HPP