#include "AnimationFactory.hpp"

#include <math.h>

#include <iostream>
#include <vector>

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

void AnimationFactory::DrawDoubleDirectionalArrow(Vector2 start, Vector2 end,
                                                  bool activeStart,
                                                  bool activeEnd, float tStart,
                                                  float tEnd) {
    if (start.x == end.x && start.y == end.y) return;
    if (std::max(tStart, tEnd) < 0.20f) return;
    float d = Dist(start, end);
    Vector2 side = (Vector2){end.x - start.x, end.y - start.y};

    Vector2 unitVector = (Vector2){side.x / (d / 3), side.y / (d / 3)};
    Vector2 invVector = InverseVector(unitVector);

    {  // from start -> end
        start.x += invVector.x, end.x += invVector.x;
        start.y += invVector.y, end.y += invVector.y;

        DrawDirectionalArrow(start, end, activeStart, tStart);
    }

    {  // from end -> start
        start.x -= 2 * invVector.x, end.x -= 2 * invVector.x;
        start.y -= 2 * invVector.y, end.y -= 2 * invVector.y;
        DrawDirectionalArrow(end, start, activeEnd, tEnd);
    }
}

void AnimationFactory::DrawDoubleActiveArrow(Vector2 start, Vector2 end,
                                             float tStart, float tEnd) {
    if (start.x == end.x && start.y == end.y) return;
    if (std::max(tStart, tEnd) < 0.20f) return;
    float d = Dist(start, end);
    Vector2 side = (Vector2){end.x - start.x, end.y - start.y};

    Vector2 unitVector = (Vector2){side.x / (d / 3), side.y / (d / 3)};
    Vector2 invVector = InverseVector(unitVector);

    {  // from start -> end
        start.x += invVector.x, end.x += invVector.x;
        start.y += invVector.y, end.y += invVector.y;

        DrawActiveArrow(start, end, tStart);
    }

    {  // from end -> start
        start.x -= 2 * invVector.x, end.x -= 2 * invVector.x;
        start.y -= 2 * invVector.y, end.y -= 2 * invVector.y;
        DrawActiveArrow(end, start, tEnd);
    }
}

/*
    -> ... >-
    |       |
    ---------
*/
void AnimationFactory::DrawCircularArrow(Vector2 start, Vector2 end,
                                         bool active, float t) {
    ReCalculateEnds(start, end, -20);

    Color lineColor = (active ? (Color){255, 138, 39, 255} : BLACK);
    float shortHorizontalSegmentLength = 20;
    float verticalSegmentLength = 60;
    float bottomSegmentLength =
        std::abs(start.x - end.x) + 2 * shortHorizontalSegmentLength;

    float totalLength =
        (shortHorizontalSegmentLength + verticalSegmentLength) * 2 +
        bottomSegmentLength;

    std::vector< float > stops;

    // >-
    stops.push_back(0);

    float firstSegmentEnd = shortHorizontalSegmentLength / totalLength;

    // |
    stops.push_back(firstSegmentEnd);
    float secondSegmentEnd =
        firstSegmentEnd + verticalSegmentLength / totalLength;

    // -----...------
    stops.push_back(secondSegmentEnd);
    float thirdSegmentEnd =
        secondSegmentEnd + bottomSegmentLength / totalLength;

    // |
    stops.push_back(thirdSegmentEnd);
    float fourthSegmentEnd =
        thirdSegmentEnd + verticalSegmentLength / totalLength;

    // ->
    stops.push_back(fourthSegmentEnd);

    //
    stops.push_back(1.0f);

    int currentStop = 0;
    for (; currentStop < stops.size() - 1; currentStop++) {
        if (t <= stops[currentStop + 1]) break;
    }

    auto calcProgress = [stops, t](std::size_t index) -> float {
        if (t <= stops[index]) return -1.0f;
        return std::min(1.0f,
                        (t - stops[index]) / (stops[index + 1] - stops[index]));
    };

    Vector2 from = end;
    Vector2 to = (Vector2){0, 0};

    auto DrawArrow = [&](Vector2& _from, Vector2& _end, std::size_t index,
                         Vector2 dt) -> bool {
        _end = (Vector2){_from.x + dt.x, _from.y + dt.y};
        if (calcProgress(index) == -1.0f) return false;
        if (calcProgress(index) < 1.0f || index == 4) {
            ReCalculateEnds(_from, _end, -20);
            DrawDirectionalArrow(_from, _end, active, calcProgress(index));
        } else {
            DrawLineEx(_from, _end, 3, lineColor);
            _from = _end;
        }
        return true;
    };

    // 1
    Vector2 dt = (Vector2){shortHorizontalSegmentLength, 0};
    if (!DrawArrow(from, to, 0, dt)) return;
    // 2
    dt = (Vector2){0, verticalSegmentLength};
    if (!DrawArrow(from, to, 1, dt)) return;
    // 3
    dt = (Vector2){-bottomSegmentLength, 0};
    if (!DrawArrow(from, to, 2, dt)) return;
    // 4
    dt = (Vector2){0, -verticalSegmentLength};
    if (!DrawArrow(from, to, 3, dt)) return;
    // 5
    dt = (Vector2){shortHorizontalSegmentLength, 0};
    if (!DrawArrow(from, to, 4, dt)) return;
}

void AnimationFactory::ReCalculateEnds(Vector2& start, Vector2& end,
                                       float radius) {
    if (start.x == end.x && start.y == end.y) {
        start.x += radius, end.x -= radius;
        return;
    }

    if (start.x == end.x && start.y == end.y) return;
    Vector2 side = (Vector2){end.x - start.x, end.y - start.y};

    float d = Dist(start, end);
    start.x += side.x * radius / d;
    start.y += side.y * radius / d;
    end.x -= side.x * radius / d;
    end.y -= side.y * radius / d;
}
