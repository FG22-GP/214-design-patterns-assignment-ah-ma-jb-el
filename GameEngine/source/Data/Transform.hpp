#pragma once

#include "Core.hpp"
#include "Vectors/Vector2.hpp"

namespace GameEngine
{
	struct Transform
	{
	public:
		Vector2 GetLocation() const { return Location; }
		float GetRotation() const { return Rotation; }
		float GetScale() const { return Scale; }

		void SetLocation(const Vector2& NewLocation) { Location = NewLocation; }
		void AddLocation(const Vector2& DeltaLocation) { Location += DeltaLocation; }

		void SetRotation(const float NewRotation);
		void Rotate(const float DeltaRotation);

		void SetScale(const float NewScale) { Scale = NewScale; }

	protected:

		Vector2 Location;
		float Rotation;
		float Scale = 1.0f;
	};
}