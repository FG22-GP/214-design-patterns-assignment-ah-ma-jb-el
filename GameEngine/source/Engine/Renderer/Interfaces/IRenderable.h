#pragma once

#include "Core.hpp"

namespace GameEngine
{
	enum class RenderFlip : uint8_t;
	struct Texture;
	struct Rectangle;
	struct Point2;
	struct Vector2;

	class IRenderable
	{
	public:

		virtual const Texture& GetTexture() = 0;
		virtual const Rectangle& GetCrop() = 0;
		//virtual const Rectangle& GetRect() = 0;
		virtual const Vector2& GetWorldLocation() = 0;
		virtual const Vector2& GetWorldScale() = 0;
		virtual const Point2& GetCentre() = 0;
		virtual double GetRotation() = 0;
		virtual RenderFlip GetFlip() = 0;

	};
}


