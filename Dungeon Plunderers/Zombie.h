#pragma once
#include "Enemy.h"


class Zombie :
	public Enemy
{
public:
	Zombie(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale = sf::Vector2f(1.f, 1.f));
	virtual ~Zombie();
	virtual void matchHitboxesToAnimation();
};

