#pragma once
#include "RangedEnemy.h"
#include "ProjectileOfDeadlyFlower.h"

class DeadlyFlower
	:public RangedEnemy
{
public:
	DeadlyFlower(const sf::Vector2f& Position, const Resources& resources, const sf::Vector2f& initialScale = sf::Vector2f(1.f, 1.f));
	virtual ~DeadlyFlower();
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile> >& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);
	virtual void matchHitboxesToAnimation();
	virtual std::unique_ptr<Enemy> clone() const override;

private:
	bool canShoot;
};

