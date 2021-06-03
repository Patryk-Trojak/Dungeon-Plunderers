#pragma once
#include "PlayerProjectile.h"

class Fireball
	:public PlayerProjectile
{
public:
	Fireball(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture, const float rotation);
	virtual ~Fireball();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};

