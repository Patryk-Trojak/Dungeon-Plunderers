#pragma once
#include "RangedEnemy.h"
#include "RockProjectile.h"

class ZombieInGround
	:public RangedEnemy
{
public:
	ZombieInGround(const sf::Vector2f& Position, const Resources& resources, const sf::Vector2f& initialScale = sf::Vector2f(1.f, 1.f));
	virtual ~ZombieInGround();
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile> >& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);
	virtual void matchHitboxesToAnimation();

private:
	bool canShoot;
};

