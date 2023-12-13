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

	void SpriteSwitchComponent::Previous(){
		m_Index = (m_Index + m_Sprites.size()) % m_Sprites.size() - 1;
		LoadedSprite = m_Sprites[m_Index];
	}

	void SpriteSwitchComponent::Next(){
		m_Index = (m_Index + 1) % m_Sprites.size();
		LoadedSprite = m_Sprites[m_Index];
	}
