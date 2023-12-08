#pragma once

#include "Core.hpp"

namespace GameEngine
{
	struct Texture;
	class Sprite;

	class AssetLoader
	{
	public:

	// GETTERS

		GAME_API static uint16_t GetTextureCount();
		GAME_API static uint16_t GetSpriteCount();

		GAME_API static std::shared_ptr<Texture> GetTexture(const std::string& name);
		GAME_API static std::shared_ptr<Sprite> GetSprite(const std::string& name);
		
		GAME_API static std::string GetAssetName(const std::string& path);
		GAME_API static std::string GetApplicationPath();

	// ASSETS

		// Loads and stores the texture at path
		GAME_API static void LoadTexture(const std::string& path);

		// Loads and stores the sprites from the texture, going from top left to bottom right
		// Names need to be specified for all of the tiles (columns * rows)
		GAME_API static void LoadSprites(const std::shared_ptr<Texture> texture, const std::vector<std::string>& names, const uint32_t columns, const uint32_t rows);

	private:

		static std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;
		static std::unordered_map<std::string, std::shared_ptr<Sprite>>  s_Sprites;

	};
}