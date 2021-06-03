#pragma once
#include "PlayerProjectile.h"


class ShadowBall :
	public PlayerProjectile
{
public:
	ShadowBall(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~ShadowBall();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
};

