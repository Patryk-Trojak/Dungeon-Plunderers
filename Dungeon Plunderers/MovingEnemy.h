#pragma once
#include "Enemy.h"

class MovingEnemy :
	public Enemy
{
public:
	MovingEnemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const Resources& resources,
		const Animation& Animation, const sf::Vector2f& healthBarOffset,
		const int InitialHp, const int PlayersDamageAfterCollision,
		const sf::Vector2f& MaxVelocity, const sf::Vector2f ChangeDirectionDistance,
		bool isReiquireSATCollision);
	virtual ~MovingEnemy();
	virtual void move(const float deltaTime) override;
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);
	virtual void updateScale(const float PositionXOfPlayer) override;
	virtual void moveWithBlock(float deltaTime) override;
protected:
	sf::Vector2f distanceMoved;
	const sf::Vector2f changeDirectionDistance;
};

