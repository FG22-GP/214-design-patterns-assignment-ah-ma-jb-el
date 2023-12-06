#pragma once

#include "Core.hpp"

namespace GameEngine
{
	enum class RenderFlip : uint8_t;
	struct Texture;
	struct Rectangle;
	struct Point2;
	class Renderer;

	class Sprite
	{
	public:

		GAME_API Sprite(std::shared_ptr<Texture> texture);

		GAME_API double GetRotation() const;
		GAME_API RenderFlip GetFlip() const;
		GAME_API const Texture& GetTexture() const;
		GAME_API const Rectangle& GetCrop() const;
		GAME_API const Rectangle& GetRect() const;
		GAME_API const Point2& GetCentre() const;

	private:

		double m_Rotation;
		RenderFlip m_Flip;

		std::shared_ptr<Texture> m_Texture;

		struct CropDeleter { void operator()(Rectangle*) const noexcept; };
		std::unique_ptr<Rectangle> m_Crop;

		struct RectDeleter { void operator()(Rectangle*) const noexcept; };
		std::unique_ptr<Rectangle> m_Rect;

		struct CentreDeleter { void operator()(Point2*) const noexcept; };
		std::unique_ptr<Point2> m_Centre;

	};
}