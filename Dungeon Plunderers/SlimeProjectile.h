#pragma once
#include "EnemyProjectile.h"

class SlimeProjectile
	:public EnemyProjectile
{
public:
	SlimeProjectile(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture);
	virtual ~SlimeProjectile();
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources);
	void matchHitboxesToAnimation() override;
};
