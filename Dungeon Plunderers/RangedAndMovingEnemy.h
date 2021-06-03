#pragma once
#include "Enemy.h"


class RangedAndMovingEnemy
	:public Enemy
{
public:
	RangedAndMovingEnemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const sf::Texture& TextureOfProjectile, const Resources& resources,
		const Animation& Animation, const sf::Vector2f& healthBarOffset,
		const int InitialHp, const int PlayersDamageAfterCollision,
		const sf::Vector2f& MaxVelocity, const sf::Vector2f ChangeDirectionDistance,
		const float TimeBetweenShots, const int DamageOfProjectile, bool isReiquireSATCollision);
	virtual ~RangedAndMovingEnemy();
	virtual void move(const float deltaTime) override;
	virtual void updateScale(const float PositionXOfPlayer) override;
	virtual void moveWithBlock(float deltaTime) override;
protected:
	const sf::Texture& textureOfProjectile;
	const int damageOfProjectile;
	float timerOfShooting;
	const float timeBetweenShots;
	sf::Vector2f distanceMoved;
	const sf::Vector2f changeDirectionDistance;
};

