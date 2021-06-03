#pragma once

#include "Projectile.h"
#include "Player.h"

class EnemyProjectile
	: public Projectile
{
public:
	EnemyProjectile(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture,
		const Animation& Animation, const Hitbox& Hitbox, bool isReiquireSATCollision);

	virtual void OnCollisionWithPlayer(Player& player);
	virtual ~EnemyProjectile();
};

