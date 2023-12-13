#pragma once

#include "PacmanCore.h"
#include "SpriteComponent.hpp"

class SpriteSwitchComponent : public SpriteComponent
{
public:

	SpriteSwitchComponent(std::shared_ptr<Actor> parent);

	void Initialise(const std::vector<std::shared_ptr<Sprite>>& sprites, const uint8_t start = 0);

	void Previous();
	void Next();

private:

	uint8_t m_Index;

	std::vector<std::shared_ptr<Sprite>> m_Sprites;

};