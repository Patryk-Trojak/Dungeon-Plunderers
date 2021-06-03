#pragma once
#include "Projectile.h"
#include "Enemy.h"

class PlayerProjectile
	: public Projectile
{
public:
	PlayerProjectile(const sf::Vector2f& Position,
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture,
		const Animation& Animation, const Hitbox& Hitbox, bool isReiquireSATCollision);
	virtual ~PlayerProjectile();
	virtual void onCollisionWithEnemy(Enemy& enemy);
};

