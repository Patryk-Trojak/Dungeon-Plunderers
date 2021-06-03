#pragma once
#include "PlayerProjectile.h"

class Electroball
	:public PlayerProjectile
{
public:
	Electroball(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~Electroball();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};

