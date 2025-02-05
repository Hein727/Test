#include "Utils.h"

VECTOR2 vec2Lerp(const VECTOR2& start, const VECTOR2& end, float t)
{
    return start * (1 - t) + end * (t);
}

float vec2Cross(const VECTOR2& v0, const VECTOR2& v1)
{
    return v0.x * v1.y - v0.y * v1.x;
}
