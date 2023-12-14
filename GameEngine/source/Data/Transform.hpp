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

		GAME_API const Vector2& GetLocation() const { return Location; }
		GAME_API float GetRotation() const { return Rotation; }
		GAME_API const Vector2& GetScale() const { return Scale; }

		GAME_API void SetLocation(const Vector2& NewLocation) { Location = NewLocation; }
		GAME_API void AddLocation(const Vector2& DeltaLocation) { Location += DeltaLocation; }

		GAME_API void SetRotation(const float NewRotation);
		GAME_API void Rotate(const float DeltaRotation);

		GAME_API void SetScale(const Vector2& NewScale) { Scale = NewScale; }

	protected:

		Vector2 Location;
		float Rotation;
		Vector2 Scale;
	};
}