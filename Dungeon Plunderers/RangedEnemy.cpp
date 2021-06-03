#include "pch.h"
#include "RangedEnemy.h"

RangedEnemy::RangedEnemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const sf::Texture& TextureOfProjectile, const Resources& resources,
	const Animation& Animation, const sf::Vector2f& healthBarOffset,
	const int InitialHp, const int PlayersDamageAfterCollision,
	const float TimeBetweenShots, const int DamageOfProjectile, bool isReiquireSATCollision)
	:Enemy(Position, TextureOfEnemy, resources, Animation, healthBarOffset, InitialHp, PlayersDamageAfterCollision, isReiquireSATCollision),
	textureOfProjectile(TextureOfProjectile),
	timerOfShooting(0),
	damageOfProjectile(DamageOfProjectile),
	timeBetweenShots(TimeBetweenShots)
{
}

RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::move(const float deltaTime)
{
	//They don't move. They only shooting
}


void RangedEnemy::updateScale(const float PositionXOfPlayer)
{
	if (PositionXOfPlayer >= enemy.getPosition().x)
		enemy.setScale(initialScale);
	else
		enemy.setScale(sf::Vector2f(initialScale.x * -1.f, initialScale.y));
}
