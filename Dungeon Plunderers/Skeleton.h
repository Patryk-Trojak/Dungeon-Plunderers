#pragma once
#include "MovingEnemy.h"

class Skeleton :
	public MovingEnemy
{
public:
	Skeleton(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale = sf::Vector2f(1.f, 1.f));
	virtual ~Skeleton();
	virtual void matchHitboxesToAnimation();
	virtual std::unique_ptr<Enemy> clone() const override;

};

