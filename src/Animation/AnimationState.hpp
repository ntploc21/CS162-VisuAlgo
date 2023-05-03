#ifndef CORE_ANIMATION_ANIMATIONSTATE_HPP
#define CORE_ANIMATION_ANIMATIONSTATE_HPP

#include <functional>

#include "Components/Visualization/CircularLinkedList.hpp"
#include "Components/Visualization/DoublyLinkedList.hpp"
#include "Components/Visualization/DynamicArray.hpp"
#include "Components/Visualization/SinglyLinkedList.hpp"
#include "Container.hpp"

namespace Animation {
    /**
     * @brief The animation state class
     * @tparam T the type of the data structure
     */
    template< typename T >
    class AnimationState {
    private:
        /**
         * @brief The duration of the animation
         */
        float mDuration;

        /**
         * @brief The current playing time
         */
        float mCurrentPlayingAt;

        /**
         * @brief The highlighted line
         */
        int mHighlightedLine;

        /**
         * @brief The action description
         */
        std::string actionDescription;

    private:
        /**
         * @brief The sourcee data structure of the animation
         */
        T mDataStructureBefore;

        /**
         * @brief The animation function
         * @param T the type of the data structure
         * @param float the progress of the animation
         * @param Vector2 the base position of the animation
         */
        std::function< T(T, float, Vector2) > mAnimation;

    public:
        /**
         * @brief Construct a new Animation State object
         */
        AnimationState();

        /**
         * @brief Destroy the Animation State object
         */
        ~AnimationState();

        /**
         * @brief Move the current playing time to the given time
         * @param playingAt the time to be moved to
         */
        void PlayingAt(float playingAt);

        /**
         * @brief Get the current playing time
         * @return float the current playing time
         */
        float GetCurrentPlayingAt() const;

        /**
         * @brief Draw the animation
         * @param base the base position of the animation
         */
        void Draw(Vector2 base = (Vector2){0, 0});

        /**
         * @brief Update the current playing time
         * @param dt the delta time
         */
        void Update(float dt);

        /**
         * @brief Reset the animation
         */
        void Reset();

    public:
        /**
         * @brief Set the duration of the animation
         * @param duration the duration of the animation
         */
        void SetDuration(float duration);

        /**
         * @brief Get the duration of the animation
         * @return float the duration of the animation
         */
        float GetDuration() const;

        /**
         * @brief Set the animation function
         * @param animation the animation function
         */
        void SetAnimation(std::function< T(T, float, Vector2) > animation);

        /**
         * @brief Set the source data structure
         * @param dataStructure the source data structure
         */
        void SetSourceDataStructure(T dataStructure);

        /**
         * @brief Get the destination data structure at the given progress
         * @param progress the progress of the animation
         * @param base the base position of the animation
         * @return T the destination data structure
         */
        T GetDataStructure(float progress, Vector2 base = (Vector2){0, 0});

    public:
        /**
         * @brief Check if the animation is done
         * @return true if the animation is done, false otherwise
         */
        bool Done() const;

        /**
         * @brief Set the highlight line
         * @param line the line to be highlighted
         */
        void SetHighlightLine(int line);

        /**
         * @brief Get the highlighted line
         * @return int the highlighted line
         */
        int GetHighlightedLine() const;

        /**
         * @brief Set the action description
         * @param description the action description
         */
        void SetActionDescription(std::string description);

        /**
         * @brief Get the action description
         * @return the action description in std::string type
         */
        std::string GetActionDescription() const;
    };
};  // namespace Animation

#include <cassert>

template< typename T >
Animation::AnimationState< T >::AnimationState()
    : mCurrentPlayingAt(0.0f), mDuration(0.0f), mHighlightedLine(-1),
      mDataStructureBefore(nullptr), actionDescription("") {
    mAnimation = [](T srcDS, float playingAt, Vector2 base) {
        srcDS.Draw(base, playingAt);
        return srcDS;
    };
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
    if (mCurrentPlayingAt > mDuration + 1.0f)
        mCurrentPlayingAt = mDuration + 1.0f;
}

template< typename T >
void Animation::AnimationState< T >::Reset() {
    PlayingAt(0.0f);
}

template< typename T >
bool Animation::AnimationState< T >::Done() const {
    return mCurrentPlayingAt >= mDuration;
}

template< typename T >
void Animation::AnimationState< T >::SetHighlightLine(int line) {
    mHighlightedLine = line;
}

template< typename T >
int Animation::AnimationState< T >::GetHighlightedLine() const {
    return mHighlightedLine;
}

template< typename T >
inline void Animation::AnimationState< T >::SetActionDescription(
    std::string description) {
    actionDescription = description;
}

template< typename T >
inline std::string Animation::AnimationState< T >::GetActionDescription()
    const {
    return actionDescription;
}

template< class T >
void Animation::AnimationState< T >::Draw(Vector2 base) {
    float playingAt = std::min(
        1.0f, (mDuration == 0.0f ? 1.0f : mCurrentPlayingAt / mDuration));
    mAnimation(mDataStructureBefore, playingAt, base);
}

typedef Animation::AnimationState< GUIVisualizer::SinglyLinkedList >
    SLLAnimation;
typedef Animation::AnimationState< GUIVisualizer::DoublyLinkedList >
    DLLAnimation;
typedef Animation::AnimationState< GUIVisualizer::CircularLinkedList >
    CLLAnimation;
typedef Animation::AnimationState< GUIVisualizer::DynamicArray >
    DArrayAnimation;

#endif  // CORE_ANIMATION_ANIMATIONSTATE_HPP