#pragma once

#include <math.h>
#include "raylib.h"

inline Vector2 operator+(const Vector2& Operator1, const Vector2& Operator2)
{
	return { Operator1.x + Operator2.x, Operator1.y + Operator2.y };
}

inline Vector2 operator-(const Vector2& Operator1, const Vector2& Operator2)
{
	return { Operator1.x - Operator2.x, Operator1.y - Operator2.y };
}

inline Vector2 operator-(const Vector2& Operator)
{
	return { -Operator.x, -Operator.y };
}

inline Vector2 operator*(const Vector2& Operator, float Multiplier)
{
	return { Operator.x * Multiplier, Operator.y * Multiplier };
}

inline Vector2 operator*=(Vector2 Operator, float Multiplier)
{
	Operator.x *= Multiplier;
	Operator.y *= Multiplier;
	return Operator;
}

inline float Module(const Vector2& Vector)
{
	return sqrtf(Vector.x * Vector.x + Vector.y * Vector.y);
}

inline Vector2 ClampSize(const Vector2& Vector, float MaxSize)
{
	float CurSize = Module(Vector);
	return CurSize > MaxSize ? Vector * (MaxSize / CurSize) : Vector;
}
