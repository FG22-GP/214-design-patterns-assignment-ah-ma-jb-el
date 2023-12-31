#include "Core.hpp"
#include "Vector2.hpp"
#include "Point2.hpp"

namespace GameEngine
{
	Vector2::Vector2()
	{
		X = 0.0f;
		Y = 0.0f;
	}
	Vector2::Vector2(const Point2& Point)
	{
		X = static_cast<float>(Point.GetX());
		Y = static_cast<float>(Point.GetY());
	}
	Vector2::Vector2(int X, int Y)
	{
		this->X = static_cast<float>(X);
		this->Y = static_cast<float>(Y);
	}
	Vector2::Vector2(float X, float Y)
	{
		this->X = X;
		this->Y = Y;
	}
	Vector2 Vector2::operator+(const Vector2& other) const
	{
		Vector2 Result;
		Result.X = X + other.X;
		Result.Y = Y + other.Y;
		return Result;
	}

	void Vector2::operator+=(const Vector2& other)
	{
		X += other.X;
		Y += other.Y;
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		Vector2 Result;
		Result.X = X - other.X;
		Result.Y = Y - other.Y;
		return Result;
	}

	void Vector2::operator-=(const Vector2& other)
	{
		X -= other.X;
		Y -= other.Y;
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return X == other.X && Y == other.Y;
	}

	Vector2 Vector2::operator/(const float& other) const
	{
		Vector2 Result;
		Result.X = X / other;
		Result.Y = Y / other;
		return Result;
	}

	Vector2 Vector2::operator*(const float& other) const
	{
		Vector2 Result;
		Result.X = X * other;
		Result.Y = Y * other;
		return Result;
	}

	Vector2 Vector2::Lerp(const Vector2& A, const Vector2& B, float Alpha)
	{
		return A * (1.0f - Alpha) + B * Alpha;
	}
	Vector2 Vector2::InverseLerpByAxis(const Vector2& A, const Vector2& B, const Vector2& Point)
	{
		Vector2 NormalizedVector;
		NormalizedVector.X = (Point.X - A.X) / (B.X - A.X);
		NormalizedVector.Y = (Point.Y - A.Y) / (B.Y - A.Y);
		return NormalizedVector;
	}

	float Vector2::Distance(const Vector2& A, const Vector2& B)
	{
		const float dSquared = DistanceSquared(A, B);
		return sqrtf(dSquared);
	}

	float Vector2::DistanceSquared(const Vector2& A, const Vector2& B)
	{
		const float dx = A.X - B.X;
		const float dy = A.Y - B.Y;
		return dx * dx + dy * dy;
	}

	float Vector2::Magnitude(const Vector2& A)
	{
		return std::sqrt(A.X * A.X + A.Y * A.Y); 
	}

	Vector2 Vector2::ClampMagnitude(const Vector2& A, float MaxMagnitude)
	{
		const float mag = Magnitude(A);
		if (mag > MaxMagnitude) {
			const float ratio = MaxMagnitude / mag;
			return {A.X * ratio, A.Y * ratio};
		}
		return A;
	}
}

