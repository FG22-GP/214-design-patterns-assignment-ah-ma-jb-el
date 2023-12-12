#pragma once

#include "PacmanCore.h"

class SpriteMap : public IAlignedSpriteMap
{
public:

	std::shared_ptr<Sprite> GetAlignedSprite(CellSpriteAlignment Alignment) override;

};