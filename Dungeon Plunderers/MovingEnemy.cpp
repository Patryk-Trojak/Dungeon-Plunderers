#include "pch.h"
#include "MovingEnemy.h"

MovingEnemy::MovingEnemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const Resources& resources,
	const Animation& Animation, const sf::Vector2f& healthBarOffset,
	const int InitialHp, const int PlayersDamageAfterCollision,
	const sf::Vector2f& MaxVelocity, const sf::Vector2f ChangeDirectionDistance,
	bool isReiquireSATCollision)

	:Enemy(Position, TextureOfEnemy, resources, Animation, healthBarOffset, InitialHp, PlayersDamageAfterCollision, isReiquireSATCollision),
	distanceMoved(0.f, 0.f),
	changeDirectionDistance(ChangeDirectionDistance)
{
	maxVelocity = MaxVelocity;

	if (ChangeDirectionDistance.x > 0)
		currentVelocity.x = maxVelocity.x;
	else if (ChangeDirectionDistance.x != 0)
		currentVelocity.x = -maxVelocity.x;
	else
		currentVelocity.x = 0.f;

	if (ChangeDirectionDistance.y > 0)
		currentVelocity.y = maxVelocity.y;
	else if (ChangeDirectionDistance.y != 0)
		currentVelocity.y = -maxVelocity.y;
	else
		currentVelocity.y = 0.f;

	distanceMoved = sf::Vector2f(0.f, 0.f);

}

MovingEnemy::~MovingEnemy()
{
}

void MovingEnemy::move(const float deltaTime)
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

void MovingEnemy::attack(std::vector<std::unique_ptr<EnemyProjectile> >& Projectiles, const sf::Vector2f & PlayerPosition, const float deltaTime)
{
	//They don't attack. They only move
}

void MovingEnemy::updateScale(const float PositionXOfPlayer)
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

void MovingEnemy::moveWithBlock(float deltaTime)
{
	if (isStandingOnBlock)
	{
		distanceMoved.x -= blockItsStandingOn->getVelocity().x * deltaTime;
		if(blockItsStandingOn->getVelocity().y != 0)
			enemy.move(0.f, blockItsStandingOn->getVelocity().y * deltaTime);
	}
}
