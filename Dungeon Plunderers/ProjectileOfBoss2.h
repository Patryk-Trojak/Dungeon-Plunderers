#pragma once
#include "EnemyProjectile.h"


class ProjectileOfBoss2 :
	public EnemyProjectile
{
public:
	ProjectileOfBoss2(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture, const float distanceOfErase = 5000);
	virtual ~ProjectileOfBoss2();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};


