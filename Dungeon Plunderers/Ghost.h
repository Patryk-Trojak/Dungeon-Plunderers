#pragma once
#include "Enemy.h"

class Ghost :
	public Enemy
{
public:
	Ghost(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources);
	virtual ~Ghost();
	virtual void matchHitboxesToAnimation();
};