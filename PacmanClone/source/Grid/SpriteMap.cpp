#include "PacmanCore.h"
#include "SpriteMap.hpp"

std::shared_ptr<Sprite> SpriteMap::GetAlignedSprite(CellSpriteAlignment Alignment)
{
	switch (Alignment)
	{
	case GameEngine::NW_Outer:
		return AssetLoader::GetSprite("NW_Outer");

	case GameEngine::SW_Outer:
		return AssetLoader::GetSprite("SW_Outer");

	case GameEngine::NE_Outer:
		return AssetLoader::GetSprite("NE_Outer");

	case GameEngine::SE_Outer:
		return AssetLoader::GetSprite("SE_Outer");

	case GameEngine::NW_Inner:
		return AssetLoader::GetSprite("NW_Inner");

	case GameEngine::SW_Inner:
		return AssetLoader::GetSprite("SW_Inner");

	case GameEngine::NE_Inner:
		return AssetLoader::GetSprite("NE_Inner");

	case GameEngine::SE_Inner:
		return AssetLoader::GetSprite("SE_Inner");

	case GameEngine::Horizontal_Top:
		return AssetLoader::GetSprite("Horizontal_Top");

	case GameEngine::Horizontal_Bottom:
		return AssetLoader::GetSprite("Horizontal_Bottom");

	case GameEngine::Vertical_Left:
		return AssetLoader::GetSprite("Vertical_Left");

	case GameEngine::Vertical_Right:
		return AssetLoader::GetSprite("Vertical_Right");

	case GameEngine::Filled:
		return AssetLoader::GetSprite("Filled");

	case GameEngine::Empty:
		return AssetLoader::GetSprite("Empty");

	default: case GameEngine::NONE:
		return std::shared_ptr<Sprite>();
	}
}