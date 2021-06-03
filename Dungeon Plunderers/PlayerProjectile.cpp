#include "pch.h"
#include "PlayerProjectile.h"

PlayerProjectile::PlayerProjectile(const sf::Vector2f& Position, const sf::Vector2f& Velocity,
	const int Damage, const sf::Texture& Texture,
	const Animation& Animation, const Hitbox& Hitbox, bool isReiquireSATCollision)
	: Projectile(Position, Velocity, Damage, Texture, Animation, Hitbox, isReiquireSATCollision)
{
}
PlayerProjectile::~PlayerProjectile()
{
}
void PlayerProjectile::onCollisionWithEnemy(Enemy& enemy)
{
	enemy.tryTakeDamage(damage);
}
