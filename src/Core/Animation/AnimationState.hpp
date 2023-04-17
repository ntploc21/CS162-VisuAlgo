#ifndef CORE_ANIMATION_ANIMATIONSTATE_HPP
#define CORE_ANIMATION_ANIMATIONSTATE_HPP

#include <functional>

#include "Components/Visualization/DataStructure.hpp"
#include "Container.hpp"

namespace Animation {
    class AnimationState {
    public:
        typedef std::shared_ptr< AnimationState > Ptr;

    private:
        float mDuration;
        float mCurrentPlayingAt;
        int mHighlightedLine;

    private:
        GUI::DataStructure mDataStructureBefore;
        std::function< GUI::DataStructure(GUI::DataStructure, float, Vector2) >
            mAnimation;

    public:
        AnimationState();
        ~AnimationState();

        void PlayingAt(float playingAt);
        float GetCurrentPlayingAt() const;
        void Draw(Vector2 base);
        void Update(float dt);
        void Reset();

    public:
        void SetDuration(float duration);
        float GetDuration() const;
        void SetAnimation(std::function< GUI::DataStructure(GUI::DataStructure,
                                                            float, Vector2) >
                              animation);
        void SetSourceDataStructure(GUI::DataStructure dataStructure);
        GUI::DataStructure GetDataStructure(float progress);

    public:
        bool Done();
        void SetHighlightLine(int line);
        int GetHighlightedLine() const;
    };
};  // namespace Animation

#endif  // CORE_ANIMATION_ANIMATIONSTATE_HPP