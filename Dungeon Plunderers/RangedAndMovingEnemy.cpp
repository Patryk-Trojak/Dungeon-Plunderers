#include "pch.h"
#include "RangedAndMovingEnemy.h"

RangedAndMovingEnemy::RangedAndMovingEnemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const sf::Texture& TextureOfProjectile, const Resources& resources,
	const Animation& Animation, const sf::Vector2f& healthBarOffset,
	const int InitialHp, const int PlayersDamageAfterCollision,
	const sf::Vector2f& MaxVelocity, const sf::Vector2f ChangeDirectionDistance,
	const float TimeBetweenShots, const int DamageOfProjectile,
	bool isReiquireSATCollision)

	:Enemy(Position, TextureOfEnemy, resources, Animation, healthBarOffset, InitialHp, PlayersDamageAfterCollision, isReiquireSATCollision),
	textureOfProjectile(TextureOfProjectile),
	timerOfShooting(0),
	damageOfProjectile(DamageOfProjectile),
	timeBetweenShots(TimeBetweenShots),
	distanceMoved(0.f, 0.f),
	changeDirectionDistance(ChangeDirectionDistance)
{
}

RangedAndMovingEnemy::~RangedAndMovingEnemy()
{
}

void RangedAndMovingEnemy::move(const float deltaTime)
{
	distanceMoved += currentVelocity * deltaTime;
	enemy.move(currentVelocity * deltaTime);
	if (abs(distanceMoved.x) >= abs(changeDirectionDistance.x))
	{
		if (distanceMoved.x >= 0.f)
			enemy.move(abs(changeDirectionDistance.x) - distanceMoved.x, 0.f);
		else
		{
			enemy.move(-abs(changeDirectionDistance.x) - distanceMoved.x, 0.f);
		}

		distanceMoved.x = 0.f;
		currentVelocity.x = -currentVelocity.x;
	}

	if (abs(distanceMoved.y) >= abs(changeDirectionDistance.y))
	{
		if (distanceMoved.y >= 0.f)
			enemy.move(abs(changeDirectionDistance.y) - distanceMoved.y, 0.f);
		else
			enemy.move(-abs(changeDirectionDistance.y) - distanceMoved.y, 0.f);

		distanceMoved.y = 0.f;
		currentVelocity.y = -currentVelocity.y;
	}
}

void RangedAndMovingEnemy::updateScale(const float PositionXOfPlayer)
{
	if (currentVelocity.x != 0)
	{
		if (currentVelocity.x > 0)
			enemy.setScale(initialScale.x, initialScale.y);
		else
			enemy.setScale(-initialScale.x, initialScale.y);
	}
	else
	{
		if (PositionXOfPlayer > enemy.getPosition().x)
			enemy.setScale(initialScale.x, initialScale.y);
		else
			enemy.setScale(-initialScale.x, initialScale.y);
	}
}


void RangedAndMovingEnemy::moveWithBlock(float deltaTime)
{
	if (isStandingOnBlock)
	{
		distanceMoved.x -= blockItsStandingOn->getVelocity().x * deltaTime;
		if (blockItsStandingOn->getVelocity().y != 0)
			enemy.move(0.f, blockItsStandingOn->getVelocity().y * deltaTime);
	}
}