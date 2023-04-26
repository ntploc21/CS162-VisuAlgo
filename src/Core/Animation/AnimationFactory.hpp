#ifndef CORE_ANIMATION_ANIMATIONFACTORY_HPP
#define CORE_ANIMATION_ANIMATIONFACTORY_HPP

#include "raylib.h"

namespace AnimationFactory {
    /* Pure Animation */
    float BounceOut(float t);
    float ElasticOut(float t);
    void DrawDirectionalArrow(Vector2 start, Vector2 end, bool active, float t);
    void DrawActiveArrow(Vector2 start, Vector2 end, float t);

    void DrawDoubleDirectionalArrow(Vector2 start, Vector2 end,
                                    bool activeStart, bool activeEnd,
                                    float tStart, float tEnd);

    void DrawDoubleActiveArrow(Vector2 start, Vector2 end, float tStart,
                               float tEnd);

    void DrawCircularArrow(Vector2 start, Vector2 end, bool active, float t);

    float Dist(Vector2 p1, Vector2 p2);
    Vector2 InverseVector(Vector2 vector);
    Vector2 MoveNode(Vector2 src, Vector2 dst, float t);

    Color BlendColor(Color src, Color dst, float t);

    void ReCalculateEnds(Vector2 &start, Vector2 &end, float radius,
                         bool applyX = true, bool applyY = true);
    /* Empty AnimationState */
};  // namespace AnimationFactory

#endif  // CORE_ANIMATION_ANIMATIONFACTORY_HPP