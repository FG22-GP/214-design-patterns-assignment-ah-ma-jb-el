#pragma once

#include "Core.hpp"
#include "Data\Visuals\Sprite.hpp"

namespace GameEngine
{
	enum CellSpriteAlignment
	{
		NONE,
		Empty,
		NW_Outer,
		SW_Outer,
		NE_Outer,
		SE_Outer,
		NW_Inner,
		SW_Inner,
		NE_Inner,
		SE_Inner,
		Horizontal_Top,
		Horizontal_Bottom,
		Vertical_Left,
		Vertical_Right,
		Filled
	};


	class IAlignedSpriteMap
	{
	public:
		virtual std::shared_ptr<Sprite> GetAlignedSprite(CellSpriteAlignment Alignment) = 0;
	};
}
