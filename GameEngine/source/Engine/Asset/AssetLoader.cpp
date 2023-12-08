#include "Core.hpp"
#include "AssetLoader.hpp"

#include "Data/Enums/RenderFlip.hpp"
#include "Data/Bounds/Rectangle.hpp"
#include "Data/Vectors/Point2.hpp"
#include "Data/Visuals/Texture.hpp"
#include "Data/Visuals/Sprite.hpp"
#include "Engine/Window/Window.hpp"
#include "SDL.h"

namespace GameEngine
{
	std::unordered_map<std::string, std::shared_ptr<Texture>> AssetLoader::s_Textures;
	std::unordered_map<std::string, std::shared_ptr<Sprite>>  AssetLoader::s_Sprites;

// GETTERS

	uint16_t AssetLoader::GetTextureCount(){
		return static_cast<uint16_t>(s_Textures.size());
	}

	uint16_t AssetLoader::GetSpriteCount(){
		return static_cast<uint16_t>(s_Sprites.size());
	}


	std::shared_ptr<Texture> AssetLoader::GetTexture(const std::string& name){
		return s_Textures[name];
	}

	std::shared_ptr<Sprite> AssetLoader::GetSprite(const std::string& name){
		return s_Sprites[name];
	}


	std::string AssetLoader::GetAssetName(const std::string& path){
		std::ifstream file(path);
		
		if (!file.good()) throw std::runtime_error(
			std::format("No such file found at path {}", path)
		);
		auto name  = std::filesystem::path(path).filename().string();
		return name.substr(0, name.find_first_of('.'));
	}

	std::string AssetLoader::GetApplicationPath(){
		return SDL_GetBasePath();
	}

// ASSETS

	void AssetLoader::LoadTexture(const std::string& path){
		auto window = Window::GetMain();

		auto texture = std::shared_ptr<Texture>(
			new Texture(window->GetRenderer(), path)
		);
		auto name = GetAssetName(path);
		s_Textures.insert(std::pair(name, texture));
	}

	void AssetLoader::LoadSprites(const std::shared_ptr<Texture> texture, const std::vector<std::string>& names, const uint32_t columns, const uint32_t rows){
		uint32_t width  = texture->GetWidth()  / columns;
		uint32_t height = texture->GetHeight() / rows;

		for (uint32_t y = 0; y < rows; y++){
			for (uint32_t x = 0; x < columns; x++){
				uint32_t index = (y * width) + x;
				if (index > names.size() - 1) break;

				auto crop   = Rectangle(x, y, width, height);
				auto rect   = Rectangle(0, 0, width, height);
				auto centre = Point2(width / 2, height / 2);

				std::shared_ptr<Sprite> sprite(
					new Sprite(texture, crop, rect, centre, RenderFlip::None, 0)
				);
				s_Sprites.insert(std::pair(names[index], sprite));
			}
		}
	}

}