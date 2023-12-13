#include "PacmanCore.h"
#include "SpriteAnimationComponent.hpp"

// CONSTRUCTORS

	SpriteAnimationComponent::SpriteAnimationComponent(std::shared_ptr<Actor> ParentActor)
		: SpriteComponent(ParentActor), m_Sprites(), m_Duration(1.0f), m_Framerate(0.5f), m_Frame(1), m_Time(0){}

// INITIALISATION

	void SpriteAnimationComponent::Initialise(const std::vector<std::shared_ptr<Sprite>>& sprites, const float duration){
		SpriteComponent::Initialize(sprites[0]);

		m_Sprites   = sprites;
		m_Duration  = duration;
		m_Framerate = duration / sprites.size();
	}

	void SpriteAnimationComponent::OnStart(){
		m_Time  = 0;
		m_Frame = 1;
	}

// ANIMATION

	void SpriteAnimationComponent::Tick(float DeltaTime){
		m_Time += DeltaTime;

		if (m_Time >= m_Duration){
			LoadedSprite = m_Sprites[0];
			m_Time  = 0;
			m_Frame = 1;
		}
		if (m_Time >= m_Frame * m_Framerate){
			LoadedSprite = m_Sprites[++m_Frame - 1];
		}
	}
