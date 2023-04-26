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
        bool interactionLock;

        static constexpr float stopDuration = 0.25;
        float currStopDuration;

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
        void Clear();

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
        void Pause();
        void Continue();
        void InteractionLock();
        void InteractionAllow();
        bool IsInteractionAllow() const;

    public:
        void Update(float dt);
        void SetSpeed(float speed);
        float GetSpeed() const;

    public:
        T GetAnimation();

    private:
        float GetStopDuration();
    };
};  // namespace Animation

#include <iostream>

template< typename T >
Animation::AnimationController< T >::AnimationController()
    : mSpeed(defaultSpeed), animationGroup({}), mCurrentAnimationIndex(0),
      Playing(false), interactionLock(false), currStopDuration(0.0f) {}

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
    if (!IsInteractionAllow()) return;
    for (auto &animation : animationGroup) {
        animation.Reset();
    }
    SetAnimation(0);
    Continue();
}

template< typename T >
void Animation::AnimationController< T >::StepForward() {
    if (mCurrentAnimationIndex == animationGroup.size() - 1) {
        RunAll();
        return;
    }
    ResetCurrent();
    SetAnimation(mCurrentAnimationIndex + 1);
    ResetCurrent();
}

template< typename T >
void Animation::AnimationController< T >::StepBackward() {
    ResetCurrent();
    SetAnimation(mCurrentAnimationIndex - 1);
    ResetCurrent();
}

template< typename T >
void Animation::AnimationController< T >::SetAnimation(std::size_t index) {
    if (!IsInteractionAllow()) return;
    if (0 <= index && index < GetNumAnimation()) {
        if (mCurrentAnimationIndex > index) {
            for (; mCurrentAnimationIndex > index; mCurrentAnimationIndex--) {
                ResetCurrent();
            }
        }
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
inline void Animation::AnimationController< T >::Clear() {
    animationGroup.clear();
}

template< typename T >
void Animation::AnimationController< T >::Pause() {
    if (IsInteractionAllow()) Playing = false;
}

template< typename T >
void Animation::AnimationController< T >::ResetCurrent() {
    if (!IsInteractionAllow()) return;
    if (animationGroup.empty()) return;
    animationGroup[mCurrentAnimationIndex].Reset();
}

template< typename T >
void Animation::AnimationController< T >::Continue() {
    if (IsInteractionAllow()) Playing = true;
}

template< typename T >
inline void Animation::AnimationController< T >::InteractionLock() {
    interactionLock = true;
}

template< typename T >
inline void Animation::AnimationController< T >::InteractionAllow() {
    interactionLock = false;
}

template< typename T >
inline bool Animation::AnimationController< T >::IsInteractionAllow() const {
    return !interactionLock;
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
    dt = GetAnimateFrame(dt);
    animationGroup[mCurrentAnimationIndex].Update(dt);
    if (IsPlaying() && animationGroup[mCurrentAnimationIndex].Done()) {
        // std::cout << dt << " | " << mCurrentAnimationIndex << " - "
        //           << GetStopDuration() << " " << stopDuration << std::endl;
        if (GetStopDuration() >= stopDuration) {
            SetAnimation(mCurrentAnimationIndex + 1);
            currStopDuration = 0.0f;
        } else {
            currStopDuration = currStopDuration + dt;
        }
    }
    if (Done()) Pause();
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
inline float Animation::AnimationController< T >::GetStopDuration() {
    return currStopDuration;
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
typedef Animation::AnimationController< DLLAnimation > DLLAnimationController;
typedef Animation::AnimationController< CLLAnimation > CLLAnimationController;
typedef Animation::AnimationController< DArrayAnimation >
    DArrayAnimationController;

#endif  // CORE_ANIMATION_ANIMATIONCONTROLLER_HPP