#pragma once
#include "Enemy.h"

class Fly :
	public Enemy
{
public:
	Fly(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources);
	virtual ~Fly();
	virtual void matchHitboxesToAnimation(); 
};

