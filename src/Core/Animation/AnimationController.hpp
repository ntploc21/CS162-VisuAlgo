#ifndef CORE_ANIMATION_ANIMATIONCONTROLLER_HPP
#define CORE_ANIMATION_ANIMATIONCONTROLLER_HPP

#include "AnimationState.hpp"
#include "Container.hpp"

namespace Animation {
    class AnimationController {
    public:
        typedef std::shared_ptr< AnimationController > Ptr;

    private:
        std::vector< AnimationState::Ptr > animationGroup;
        static constexpr float defaultSpeed = 1;

    private:
        std::size_t mCurrentAnimationIndex;
        float mSpeed;
        // float
        bool Playing;

    public:
        AnimationController();
        ~AnimationController();

    public:
        void RunAll();
        void Reset();
        void ResetCurrent();

        void SetAnimation(std::size_t animationIndex);
        std::size_t CurrentAnimationIndex() const;
        // AnimationState::Ptr GetCurrent
    public:
        float GetAnimationDuration();

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
        float GetAnimateFrame(float dt) const;
        std::size_t GetNumAnimation() const;
        std::size_t GetAnimationIndex() const;
        bool Done();
        bool IsPlaying();
    };
};  // namespace Animation

#endif  // CORE_ANIMATION_ANIMATIONCONTROLLER_HPP