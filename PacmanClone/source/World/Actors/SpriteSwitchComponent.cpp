#include "PacmanCore.h"
#include "SpriteSwitchComponent.hpp"

// CONSTRUCTORS

	SpriteSwitchComponent::SpriteSwitchComponent(std::shared_ptr<Actor> parent)
		: SpriteComponent(parent), m_Sprites(), m_Index(0){}

// INITIALISATION

	void SpriteSwitchComponent::Initialise(const std::vector<std::shared_ptr<Sprite>>& sprites, const uint8_t start){
		SpriteComponent::Initialize(sprites[start]);
		m_Sprites = sprites;
		m_Index	  = start;
	}

// SWITCHING

	void SpriteSwitchComponent::GoTo(const uint8_t index){
		m_Index = std::clamp(
			index, uint8_t(0), static_cast<uint8_t>(m_Sprites.size() - 1)
		);
		LoadedSprite = m_Sprites[m_Index];
	}

	void SpriteSwitchComponent::Previous(){
		uint8_t size = static_cast<uint8_t>(m_Sprites.size());

		m_Index = (m_Index + size) % size - 1;
		LoadedSprite = m_Sprites[m_Index];
	}

	void SpriteSwitchComponent::Next(){
		uint8_t size = static_cast<uint8_t>(m_Sprites.size());	

		m_Index = (m_Index + 1) % size;
		LoadedSprite = m_Sprites[m_Index];
	}
