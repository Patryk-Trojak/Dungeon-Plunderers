#include "pch.h"
#include "MovingEnemyComponent.h"

MovingEnemyComponent::MovingEnemyComponent(sf::Sprite& enemy, const sf::Vector2f& initialScaleOfEnemy,
	const sf::Vector2f& MaxVelocity, const sf::Vector2f ChangeDirectionDistance)
	: enemy(enemy),
	initialScaleOfEnemy(initialScaleOfEnemy),
	Movable(MaxVelocity),
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

MovingEnemyComponent::~MovingEnemyComponent()
{
}

void MovingEnemyComponent::move(const float deltaTime)
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

void MovingEnemyComponent::updateScale(const float PositionXOfPlayer)
{
	if (currentVelocity.x != 0)
	{
		if (currentVelocity.x > 0)
			enemy.setScale(initialScaleOfEnemy.x, initialScaleOfEnemy.y);
		else
			enemy.setScale(-initialScaleOfEnemy.x, initialScaleOfEnemy.y);
	}
	else
	{
		if (PositionXOfPlayer > enemy.getPosition().x)
			enemy.setScale(initialScaleOfEnemy.x, initialScaleOfEnemy.y);
		else
			enemy.setScale(-initialScaleOfEnemy.x, initialScaleOfEnemy.y);
	}
}