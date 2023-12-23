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

		// Returns a loaded texture from name, without file extension
		GAME_API static std::shared_ptr<Texture> GetTexture(const std::string& name);

		// Returns a loaded sprite from assigned name
		GAME_API static std::shared_ptr<Sprite> GetSprite(const std::string& name);
		
		// Returns the name of the asset at absolute path
		GAME_API static std::string GetAssetName(const std::string& path);
		
		// Returns the absolute path to the asset in the Asssets directory
		// Filename must include its file type extension (filename.type)
		GAME_API static std::string GetAssetPath(const std::string& filename);
		
		// Returns the absolute path to the application directory
		GAME_API static std::string GetApplicationPath();

	// ASSETS

		// Loads and stores the texture at path
		GAME_API static void LoadTexture(const std::string& path);

		// Loads and stores the sprites from the texture, going from top left to bottom right
		GAME_API static void LoadSprites(const std::shared_ptr<Texture> texture, const std::vector<std::string>& names, const uint16_t columns, const uint16_t rows);
		
		// Loads and stores the sprite, at XY tile location with tile width and height, from the texture
		GAME_API static void LoadSprite(const std::shared_ptr<Texture> texture, const std::string& name, const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height, const uint16_t columns, const uint16_t rows);

	private:

		static std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;
		static std::unordered_map<std::string, std::shared_ptr<Sprite>>  s_Sprites;

	};
}