#pragma once

#include "Core.hpp"
#include "Vectors/Vector2.hpp"

namespace GameEngine
{
	struct Transform
	{
	public:
		//Default constructor
		Transform() : Location(Vector2(0, 0)), Rotation(0.0f), Scale(Vector2(1, 1)) {}

		const Vector2& GetLocation() const { return Location; }
		float GetRotation() const { return Rotation; }
		const Vector2& GetScale() const { return Scale; }

		void SetLocation(const Vector2& NewLocation) { Location = NewLocation; }
		void AddLocation(const Vector2& DeltaLocation) { Location += DeltaLocation; }

		void SetRotation(const float NewRotation);
		void Rotate(const float DeltaRotation);

		void SetScale(const Vector2& NewScale) { Scale = NewScale; }

	protected:

		Vector2 Location;
		float Rotation;
		Vector2 Scale;
	};
}