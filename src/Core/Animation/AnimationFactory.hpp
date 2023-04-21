#ifndef CORE_ANIMATION_ANIMATIONFACTORY_HPP
#define CORE_ANIMATION_ANIMATIONFACTORY_HPP

#include "raylib.h"

namespace AnimationFactory {
    /* Pure Animation */
    float BounceOut(float t);
    float ElasticOut(float t);
    void DrawDirectionalArrow(Vector2 start, Vector2 end, bool active, float t);

    float Dist(Vector2 p1, Vector2 p2);
    Vector2 InverseVector(Vector2 vector);

    Color BlendColor(Color src, Color dst, float t);
    void DrawActiveArrow(Vector2 start, Vector2 end, float t);
    /* Empty AnimationState */
};  // namespace AnimationFactory

#endif  // CORE_ANIMATION_ANIMATIONFACTORY_HPP