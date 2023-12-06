#pragma once

#include "Core.hpp"

namespace GameEngine
{
	enum class RenderFlip : uint8_t
	{
		None		 = 0,
		Horizontally = 1,
		Vertically	 = 2,
	};
}