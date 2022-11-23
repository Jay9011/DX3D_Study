#include "Framework.h"
#include "GameMath.h"

float GameMath::Saturate(const float& value)
{
    return max(0.0f, min(1.0f, value));
}

float GameMath::Distance(const Vector3& v1, const Vector3& v2)
{
    return (v2 - v1).Length();
}

int GameMath::Random(int min, int max)
{
    return rand() % (max - min) + min;
}

float GameMath::Random(float min, float max)
{
    float normal = (float)rand() / (float)RAND_MAX;

    return min + (max - min) * normal;
}

Vector3 GameMath::Random(Vector3 min, Vector3 max)
{
    Vector3 result;
    result.x = Random(min.x, max.x);
    result.y = Random(min.y, max.y);
    result.z = Random(min.z, max.z);

    return result;
}

Vector3 GameMath::ClosestPointOnLine(const Vector3& start, const Vector3& end, const Vector3& point)
{
    Vector3 line = end - start;

    float t = Vector3::Dot(line, point - start) / Vector3::Dot(line, line);
    t = Saturate(t);

    return start + line * t;
}
