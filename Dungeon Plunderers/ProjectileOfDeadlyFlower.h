#pragma once
#include "EnemyProjectile.h"

class ProjectileOfDeadlyFlower
	:public EnemyProjectile
{
public:
	ProjectileOfDeadlyFlower(const sf::Vector2f& Position, 
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~ProjectileOfDeadlyFlower();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};

