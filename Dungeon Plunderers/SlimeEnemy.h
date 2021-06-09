#pragma once
#include "RangedEnemy.h"
#include "SlimeProjectile.h"

class SlimeEnemy
	:public RangedEnemy
{
public:
	SlimeEnemy(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale = sf::Vector2f(1.f, 1.f));
	virtual ~SlimeEnemy();
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile> >& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);
	virtual void matchHitboxesToAnimation();

private:
	bool canShoot;
};

