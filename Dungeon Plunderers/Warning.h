#pragma once
#include "EnemyProjectile.h"


class Warning :
	public EnemyProjectile
{
public:
	Warning(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~Warning();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};

