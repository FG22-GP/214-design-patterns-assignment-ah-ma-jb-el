#include "Core.hpp"
#include "Transform.hpp"

namespace GameEngine
{
	void Transform::SetRotation(float NewRotation)
	{
		Rotation = 0.0f;
		Rotate(NewRotation);
	}

	void Transform::Rotate(float DeltaRotation)
	{
		Rotation += DeltaRotation;
		while (DeltaRotation > 180.0f)
			DeltaRotation -= 360.0f;
		while (DeltaRotation < -180.0f)
			DeltaRotation += 360.0f;
	}
}