#pragma once
#include "EnemyProjectile.h"


class ProjectileOfBoss :
	public EnemyProjectile
{
public:
	ProjectileOfBoss(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture, float distanceOfErase = 5000.f);
	virtual ~ProjectileOfBoss();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};

