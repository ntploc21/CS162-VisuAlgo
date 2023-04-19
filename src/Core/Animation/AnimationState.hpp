#ifndef CORE_ANIMATION_ANIMATIONSTATE_HPP
#define CORE_ANIMATION_ANIMATIONSTATE_HPP

#include <functional>

#include "Components/Visualization/DataStructure.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"
#include "Container.hpp"

namespace Animation {
    template< typename T >
    class AnimationState {
    public:
        typedef std::shared_ptr< AnimationState< T > > Ptr;

    private:
        float mDuration;
        float mCurrentPlayingAt;
        int mHighlightedLine;

    private:
        T mDataStructureBefore;
        std::function< T(T, float, Vector2) > mAnimation;

    public:
        AnimationState();
        ~AnimationState();

        void PlayingAt(float playingAt);
        float GetCurrentPlayingAt() const;
        void Draw(Vector2 base = (Vector2){0, 0});
        void Update(float dt);
        void Reset();

    public:
        void SetDuration(float duration);
        float GetDuration() const;
        void SetAnimation(std::function< T(T, float, Vector2) > animation);
        void SetSourceDataStructure(T dataStructure);
        T GetDataStructure(float progress, Vector2 base = (Vector2){0, 0});

    public:
        bool Done() const;
        void SetHighlightLine(int line);
        int GetHighlightedLine() const;
    };
};  // namespace Animation

#include <cassert>
#include <iostream>

// #include "AnimationState.hpp"

template< typename T >
Animation::AnimationState< T >::AnimationState()
    : mCurrentPlayingAt(0.0f), mDuration(0.0f), mHighlightedLine(-1),
      mDataStructureBefore(nullptr) {
    mAnimation = [](T srcDS, float playingAt, Vector2 base) { return srcDS; };
}

template< typename T >
Animation::AnimationState< T >::~AnimationState() {}

template< typename T >
void Animation::AnimationState< T >::SetDuration(float duration) {
    mDuration = duration;
}

template< typename T >
float Animation::AnimationState< T >::GetDuration() const {
    return mDuration;
}

template< typename T >
void Animation::AnimationState< T >::SetAnimation(
    std::function< T(T, float, Vector2) > animation) {
    mAnimation = animation;
}

template< typename T >
void Animation::AnimationState< T >::PlayingAt(float playingAt) {
    mCurrentPlayingAt = playingAt;
}

template< typename T >
float Animation::AnimationState< T >::GetCurrentPlayingAt() const {
    return mCurrentPlayingAt;
}

template< typename T >
void Animation::AnimationState< T >::SetSourceDataStructure(T dataStructure) {
    mDataStructureBefore = dataStructure;
}

template< typename T >
T Animation::AnimationState< T >::GetDataStructure(float progress,
                                                   Vector2 base) {
    assert(progress >= 0.0f && progress <= 1.0f);
    return mAnimation(mDataStructureBefore, progress, base);
}

template< typename T >
void Animation::AnimationState< T >::Update(float dt) {
    mCurrentPlayingAt += dt;
    if (mCurrentPlayingAt > mDuration) mCurrentPlayingAt = mDuration;
}

template< typename T >
void Animation::AnimationState< T >::Reset() {
    PlayingAt(0.0f);
}

template< typename T >
bool Animation::AnimationState< T >::Done() const {
    return mCurrentPlayingAt == mDuration;
}

template< typename T >
void Animation::AnimationState< T >::SetHighlightLine(int line) {
    mHighlightedLine = line;
}

template< typename T >
int Animation::AnimationState< T >::GetHighlightedLine() const {
    return mHighlightedLine;
}

template< class T >
void Animation::AnimationState< T >::Draw(Vector2 base) {
    int playingAt = std::min(
        1.0f, (mDuration == 0.0f ? 1.0f : mCurrentPlayingAt / mDuration));
    mAnimation(mDataStructureBefore, playingAt, base);
}

typedef Animation::AnimationState< GUI::SinglyLinkedList > SLLAnimation;

#endif  // CORE_ANIMATION_ANIMATIONSTATE_HPP