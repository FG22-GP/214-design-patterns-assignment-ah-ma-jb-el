#include "Core.hpp"
#include "AssetLoader.hpp"

#include "SDL.h"

namespace GameEngine
{
	std::string AssetLoader::GetApplicationPath(){	
		return SDL_GetBasePath();
	}
}