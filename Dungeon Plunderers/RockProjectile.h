#pragma once
#include "PlayerProjectile.h"

class RockProjectile :
	public EnemyProjectile
{
public:
	RockProjectile(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~RockProjectile();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};