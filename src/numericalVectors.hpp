#pragma once

#include <raylib.h>
#include <iostream>
#include <string>

// Component-wise plussing by a vector
Vector2 operator+(const Vector2& left, const Vector2& right)
{
	return {
		left.x + right.x,
		left.y + right.y
	};
}

// Component-wise minusing by a vector
Vector2 operator-(const Vector2& left, const Vector2& right)
{
	return {
		left.x - right.x,
		left.y - right.y
	};
}

// Component-wise timesing by a vector
Vector2 operator*(const Vector2& left, const Vector2& right)
{
	return {
		left.x * right.x,
		left.y * right.y
	};
}

// Component-wise dividing by a vector
Vector2 operator/(const Vector2& left, const Vector2& right)
{
	return {
		left.x / right.x,
		left.y / right.y
	};
}

// scalar timesing by a vector
Vector2 operator+(const Vector2& vector, const float& scalar)
{
	return {
		vector.x * scalar,
		vector.y * scalar
	};
}

// scalar dividing by a vector
Vector2 operator/(const Vector2& vector, const float& scalar)
{
	if (scalar == 0) return vector;

	return {
		vector.x / scalar,
		vector.y / scalar
	};
}

// Printing a vector
std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
{
	stream << "<" << vector.x << ", " << vector.y << ">";
	return stream;
}