#pragma once
#include "MovingEnemy.h"
class Fly :
	public MovingEnemy
{
public:
	Fly(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources);
	virtual ~Fly();
	virtual void matchHitboxesToAnimation(); 
	virtual std::unique_ptr<Enemy> clone() const override;
};

