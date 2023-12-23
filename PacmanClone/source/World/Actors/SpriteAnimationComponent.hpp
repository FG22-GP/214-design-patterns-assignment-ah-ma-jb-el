#pragma once

#include "PacmanCore.h"
#include "SpriteComponent.hpp"

class SpriteAnimationComponent : public SpriteComponent 
{
public:

	SpriteAnimationComponent(std::shared_ptr<Actor> parent);

	void Initialise(const std::vector<std::shared_ptr<Sprite>>& sprites, const float duration);
	
	void OnStart() override;
	void Tick(float DeltaTime) override;

private:

	float m_Time;
	float m_Duration;
	float m_Framerate;
	uint8_t m_Frame;

	std::vector<std::shared_ptr<Sprite>> m_Sprites;

};