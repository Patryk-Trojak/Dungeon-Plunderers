#pragma once
#include "EnemyProjectile.h"


class Laser :
	public EnemyProjectile
{
public:
	Laser(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~Laser();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};



