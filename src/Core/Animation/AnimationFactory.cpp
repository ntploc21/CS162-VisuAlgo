#include "AnimationFactory.hpp"

#include <math.h>

#include <iostream>

float AnimationFactory::BounceOut(float t) {
    // -- Bounce out
    const float nl = 7.5625f;
    const float dl = 2.75f;
    if (t < 1.0 / dl) {
        return nl * t * t;
    } else if (t < 2.0 / dl) {
        t -= 1.5 / dl;
        return (nl * t * t + 0.75);
    } else if (t < 2.5 / dl) {
        t -= 2.25 / dl;
        return (nl * t * t + 0.9375);
    }
    t -= 2.625 / dl;
    return (nl * t * t + 0.984375);
}

float AnimationFactory::ElasticOut(float t) {
    // --
    // -- Elastic out
    return (sin(-13.0 * (t + 1.0) * acos(-1) / 2) * pow(2.0, -10.0 * t) + 1.0);
    // --
}

void AnimationFactory::DrawDirectionalArrow(Vector2 start, Vector2 end,
                                            bool active, float t) {
    if (start.x == end.x && start.y == end.y) return;
    if (t < 0.20f) return;
    ReCalculateEnds(start, end, 20);

    float d = Dist(start, end);
    Vector2 side = (Vector2){end.x - start.x, end.y - start.y};
    end = (Vector2){start.x + side.x * t, start.y + side.y * t};

    Vector2 unitVector = (Vector2){side.x / (d / 3), side.y / (d / 3)};
    Vector2 invVector = InverseVector(unitVector);

    Vector2 arrowPoint = end;
    Vector2 arrowP1 = (Vector2){arrowPoint.x - 2 * unitVector.x + invVector.x,
                                arrowPoint.y - 2 * unitVector.y + invVector.y};
    Vector2 arrowP2 = (Vector2){arrowPoint.x - 2 * unitVector.x - invVector.x,
                                arrowPoint.y - 2 * unitVector.y - invVector.y};

    end = (Vector2){end.x - unitVector.x, end.y - unitVector.y};

    Color lineColor = (active ? (Color){255, 138, 39, 255} : BLACK);

    DrawLineEx(start, end, 3, lineColor);
    DrawTriangle(arrowP1, arrowPoint, arrowP2, BLACK);
}

float AnimationFactory::Dist(Vector2 p1, Vector2 p2) {
    return hypot(p2.x - p1.x, p2.y - p1.y);
}

Vector2 AnimationFactory::InverseVector(Vector2 vector) {
    Vector2 invVector = (Vector2){-vector.y, vector.x};
    return invVector;
}

Vector2 AnimationFactory::MoveNode(Vector2 src, Vector2 dst, float t) {
    Vector2 side = (Vector2){dst.x - src.x, dst.y - src.y};
    return (Vector2){src.x + side.x * t, src.y + side.y * t};
}

Color AnimationFactory::BlendColor(Color src, Color dst, float t) {
    Color answer;
    answer.r = src.r + (dst.r - src.r) * t;
    answer.g = src.g + (dst.g - src.g) * t;
    answer.b = src.b + (dst.b - src.b) * t;
    answer.a = src.a + (dst.a - src.a) * t;
    return answer;
}

void AnimationFactory::DrawActiveArrow(Vector2 start, Vector2 end, float t) {
    if (start.x == end.x && start.y == end.y) return;
    if (t < 0.20f) return;
    ReCalculateEnds(start, end, 20);
    Vector2 side = (Vector2){end.x - start.x, end.y - start.y};

    float d = Dist(start, end);
    end = (Vector2){start.x + side.x * t, start.y + side.y * t};
    DrawLineEx(start, end, 3, (Color){255, 138, 39, 255});
}

void AnimationFactory::ReCalculateEnds(Vector2& start, Vector2& end,
                                       float radius) {
    if (start.x == end.x && start.y == end.y) return;
    Vector2 side = (Vector2){end.x - start.x, end.y - start.y};

    float d = Dist(start, end);
    start.x += side.x * radius / d;
    start.y += side.y * radius / d;
    end.x -= side.x * radius / d;
    end.y -= side.y * radius / d;
}
