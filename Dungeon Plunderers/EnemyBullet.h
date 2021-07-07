#pragma once
#include "EnemyProjectile.h"
#include "RandomEngine.h"

class EnemyBullet :
	public EnemyProjectile
{
public:
	EnemyBullet(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~EnemyBullet();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
private:
	int whichEffectAdd;
};
