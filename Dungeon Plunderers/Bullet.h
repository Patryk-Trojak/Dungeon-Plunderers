#pragma once
#include "PlayerProjectile.h"

class Bullet :
	public PlayerProjectile
{
public:
	Bullet(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~Bullet();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
private:
	int whichEffectAdd;

};

