#pragma once
#include "PlayerProjectile.h"

class Icicle
	:public PlayerProjectile
{
public:
	Icicle(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture, const float rotation);
	virtual ~Icicle();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
	virtual void onCollisionWithEnemy(Enemy& enemy) override;
};

