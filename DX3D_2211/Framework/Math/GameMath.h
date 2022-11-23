#pragma once

namespace GameMath
{
	float Saturate(const float& value);

	float Distance(const Vector3& v1, const Vector3& v2);

	int Random(int min, int max);
	float Random(float min, float max);
	Vector3 Random(Vector3 min, Vector3 max);

	Vector3 ClosestPointOnLine(const Vector3& start, const Vector3& end, const Vector3& point);
}