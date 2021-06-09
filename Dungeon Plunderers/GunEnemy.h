#pragma once
#include "RangedEnemy.h"
//#include "Bullet.h"
#define _USE_MATH_DEFINES 
#include <math.h>

class GunEnemy:
	public RangedEnemy
{
public:
	GunEnemy(const sf::Vector2f& Position, const Resources& resources, const sf::Vector2f& initialScale = sf::Vector2f(1.f, 1.f));
	virtual ~GunEnemy();
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile> >& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);
	virtual void matchHitboxesToAnimation();
	virtual void updateRotation(const sf::Vector2f& PlayerPosition) override;
	virtual void updateScale(const float PositionXOfPlayer) override;

protected:
	bool canShoot;

	sf::VertexArray laser;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

