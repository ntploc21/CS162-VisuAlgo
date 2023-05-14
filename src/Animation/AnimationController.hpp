#ifndef CORE_ANIMATION_ANIMATIONCONTROLLER_HPP
#define CORE_ANIMATION_ANIMATIONCONTROLLER_HPP

#include "AnimationState.hpp"
#include "Container.hpp"
#include "Core/Deque.hpp"

namespace Animation {
    /**
     * @brief The animation controller class
     * @tparam T the type of the animation state
     */
    template< typename T = SLLAnimation >
    class AnimationController {
    public:
        /**
         * @brief The shared pointer of the animation controller
         */
        typedef std::shared_ptr< AnimationController > Ptr;

    private:
        /**
         * @brief The animation group containing all the animation states
         */
        std::vector< T > animationGroup;

        /**
         * @brief The default speed of the animation
         */
        static constexpr float defaultSpeed = 1;

    private:
        /**
         * @brief The current animation index
         */
        std::size_t mCurrentAnimationIndex;

        /**
         * @brief The current animation
         */
        float mSpeed;

        /**
         * @brief The current animation
         */
        bool mPlaying;

        /**
         * @brief The current animation
         */
        bool mInteractionLock;

        /**
         * @brief The default delay between two animations
         */
        static constexpr float stopDuration = 0.25;

        /**
         * @brief The current delay between two animations
         */
        float mCurrStopDuration;

    public:
        /**
         * @brief Construct a new Animation Controller object
         */
        AnimationController();

        /**
         * @brief Destroy the Animation Controller object
         */
        ~AnimationController();

        /**
         * @brief Run all the animations, display the final result
         */
        void RunAll();

        /**
         * @brief Reset the animation controller
         */
        void Reset();

        /**
         * @brief Reset the current animation
         */
        void ResetCurrent();

        /**
         * @brief Set the animation
         * @param animationIndex the index of the animation
         */
        void SetAnimation(std::size_t animationIndex);

        /**
         * @brief Get the current animation running
         * @return the current animation running index
         */
        std::size_t CurrentAnimationIndex() const;

    public:
        /**
         * @brief Add an animation to the end of the animation group
         * @param animation the animation to be added
         */
        void AddAnimation(T animation);

        /**
         * @brief remove the last animation from the animation group
         */
        void PopAnimation();

        /**
         * @brief Clear all the animations
         */
        void Clear();

    public:
        /**
         * @brief Get the animation duration
         * @return the animation duration
         */
        float GetAnimationDuration();

        /**
         * @brief Get the number of animations
         * @return the number of animations
         */
        std::size_t GetNumAnimation() const;

        /**
         * @brief Get the current animation playing
         * @return the current animation playing index
         */
        std::size_t GetAnimationIndex() const;

        /**
         * @brief Check if the animation is done
         * @return true if the animation is done, false otherwise
         */
        bool Done() const;

        /**
         * @brief Check if the animation is playing
         * @return true if the animation is playing, false otherwise
         */
        bool IsPlaying() const;

    public:
        /**
         * @brief Move to the next animation
         * @note It will reset the current animation
         * @note If the current animation is the last one, it will not move
         * (pretty much the same as run all)
         */
        void StepForward();

        /**
         * @brief Move to the previous animation
         * @note It will reset the current animation
         * @note If the current animation is the first one, it will not move
         * (pretty much the same as reset)
         */
        void StepBackward();

        /**
         * @brief Pause the animation
         */
        void Pause();

        /**
         * @brief Continue the animation
         */
        void Continue();

        /**
         * @brief Lock the interaction, so the user cannot interact with the
         * animation
         */
        void InteractionLock();

        /**
         * @brief Allow the interaction, so the user can interact with the
         * animation
         * @note By default, the interaction is allowed
         */
        void InteractionAllow();

        /**
         * @brief Check if the interaction is allowed
         * @return true if the interaction is allowed, false otherwise
         */
        bool IsInteractionAllow() const;

    public:
        /**
         * @brief Update the animation
         * @param dt the delta time
         */
        void Update(float dt);

        /**
         * @brief Adjust the speed of the animation
         * @param speed the speed of the animation
         */
        void SetSpeed(float speed);

        /**
         * @brief Get the speed of the animation
         * @return the speed of the animation
         */
        float GetSpeed() const;

    public:
        /**
         * @brief Get the current animation playing
         * @return the current animation playing
         */
        T GetAnimation();

    private:
        /**
         * @brief Get the current delta time based on the speed
         * @param dt the delta time
         * @return the current delta time based on the speed
         */
        float GetAnimateFrame(float dt) const;

        /**
         * @brief Get the current stop duration
         * @return the current stop duration
         */
        float GetStopDuration();
    };
};  // namespace Animation

template< typename T >
Animation::AnimationController< T >::AnimationController()
    : mSpeed(defaultSpeed), animationGroup({}), mCurrentAnimationIndex(0),
      mPlaying(false), mInteractionLock(false), mCurrStopDuration(0.0f) {}

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
    animationGroup.push_back(animation);
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
    if (IsInteractionAllow()) mPlaying = false;
}

template< typename T >
void Animation::AnimationController< T >::ResetCurrent() {
    if (!IsInteractionAllow()) return;
    if (animationGroup.empty()) return;
    animationGroup[mCurrentAnimationIndex].Reset();
}

template< typename T >
void Animation::AnimationController< T >::Continue() {
    if (IsInteractionAllow()) mPlaying = true;
}

template< typename T >
inline void Animation::AnimationController< T >::InteractionLock() {
    mInteractionLock = true;
}

template< typename T >
inline void Animation::AnimationController< T >::InteractionAllow() {
    mInteractionLock = false;
}

template< typename T >
inline bool Animation::AnimationController< T >::IsInteractionAllow() const {
    return !mInteractionLock;
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
        if (GetStopDuration() >= stopDuration) {
            SetAnimation(mCurrentAnimationIndex + 1);
            mCurrStopDuration = 0.0f;
        } else {
            mCurrStopDuration = mCurrStopDuration + dt;
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
    return mCurrStopDuration;
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
    return mPlaying;
}

/* */
typedef Animation::AnimationController< SLLAnimation > SLLAnimationController;
typedef Animation::AnimationController< DLLAnimation > DLLAnimationController;
typedef Animation::AnimationController< CLLAnimation > CLLAnimationController;
typedef Animation::AnimationController< DArrayAnimation >
    DArrayAnimationController;

#endif  // CORE_ANIMATION_ANIMATIONCONTROLLER_HPP