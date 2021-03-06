#pragma once
#include "Movable.h"
#include "EnemyStates.h"

class MovingEnemyComponent
	: public Movable
{
public:
	MovingEnemyComponent(sf::Sprite& enemy, const EnemyState& currentEnemyState, const sf::Vector2f& initialScaleOfEnemy,
		const sf::Vector2f& MaxVelocity, const sf::Vector2f ChangeDirectionDistance);
	virtual ~MovingEnemyComponent();
	void move(const float deltaTime);
	void updateScale(const float PositionXOfPlayer);
private:
	sf::Sprite& enemy;
	const EnemyState& currentEnemyState;
	void updateCurrentVelocityDependsOnCurrentState();
	const sf::Vector2f initialScaleOfEnemy;
	sf::Vector2f distanceMoved;
	const sf::Vector2f changeDirectionDistance;
};

