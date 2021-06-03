#pragma once
#include "Enemy.h"
#include "Enemy.h"

class RangedEnemy :
	public Enemy
{
public:
	RangedEnemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const sf::Texture& TextureOfProjectile, const Resources& resources,
		const Animation& Animation, const sf::Vector2f& healthBarOffset,
		const int InitialHp, const int PlayersDamageAfterCollision,
		const float TimeBetweenShots, const int DamageOfProjectile,
		bool isReiquireSATCollision);
	virtual ~RangedEnemy();
	virtual void move(const float deltaTime) override;
	virtual void updateScale(const float PositionXOfPlayer) override;

protected:
	const sf::Texture& textureOfProjectile;
	const int damageOfProjectile;
	float timerOfShooting;
	const float timeBetweenShots;
};

