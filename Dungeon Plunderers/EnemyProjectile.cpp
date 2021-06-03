#include "pch.h"
#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(const sf::Vector2f& Position, const sf::Vector2f& Velocity, 
	const int Damage, const sf::Texture& Texture, 
	const Animation& Animation, const Hitbox& Hitbox, bool isReiquireSATCollision)
	: Projectile(Position, Velocity, Damage, Texture, Animation, Hitbox, isReiquireSATCollision)
{
}

void EnemyProjectile::OnCollisionWithPlayer(Player& player)
{
	player.addHp(-damage);
}

EnemyProjectile::~EnemyProjectile()
{
}
