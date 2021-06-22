#pragma once
#include "Enemy.h"

class Bat :
	public Enemy
{
public:
	Bat(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources);
	virtual ~Bat();
	virtual void matchHitboxesToAnimation();
};