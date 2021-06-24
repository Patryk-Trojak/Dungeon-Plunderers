#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const Resources& resources,
	const Animation& Animation, const sf::Vector2f& healthBarOffset,
	const int InitialHp, const int PlayersDamageAfterCollision,
	bool isReiquireSATCollision)
	:enemy(TextureOfEnemy),
	animation(Animation),
	currentHp(InitialHp),
	playersDamageAfterCollision(PlayersDamageAfterCollision),
	healthBar(Position, resources, resources.font, InitialHp, healthBarOffset),
	shouldUpdate(false),
	initialScale(1.f, 1.f),
	isCollidingWithPlayer(false),
	isMortal(true),
	isReiquireSATCollision(isReiquireSATCollision),
	currentState(EnemyState::normal),
	timeToChangeToNormalState(0)
{
	enemy.setPosition(Position);
	animation.setFrame(enemy, 1);
	calculeteGlobalBoundsOfSprite();
}

Enemy::~Enemy()
{
}

void Enemy::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime)
{
}

void Enemy::updateScale(const float PositionXOfPlayer)
{
	if (movingEnemyComponent)
		movingEnemyComponent->updateScale(PositionXOfPlayer);
}

void Enemy::updateRotation(const sf::Vector2f& PlayerPosition)
{
}

void Enemy::updateCurrentState(float deltaTime)
{
	if (currentState != EnemyState::normal)
	{
		timeToChangeToNormalState -= deltaTime;

		if (timeToChangeToNormalState <= 0)
			currentState = EnemyState::normal;
	}
}

void Enemy::playAnimation(const float deltaTime)
{
	float newDeltaTime = deltaTime;
	if (currentState == EnemyState::frost)
		newDeltaTime = deltaTime / 2.f; //just to slow down animation because in frost state enemies move slower

	animation.play(enemy, newDeltaTime);
}

void Enemy::moveWithBlock(float deltaTime) 
{
	if(isStandingOnBlock)
	{
		enemy.move(blockItsStandingOn->getVelocity() * deltaTime);
	}
}

void Enemy::updateHealthBar()
{
	if (enemy.getScale().x > 0)
	{
		healthBar.setPosition(enemy.getPosition() + healthBar.getOffset());
	}
	else
	{
		healthBar.setPosition(sf::Vector2f( enemy.getPosition().x - healthBar.getSize().x - healthBar.getOffset().x, enemy.getPosition().y + healthBar.getOffset().y));
	}
}

void Enemy::updatePositionOfHitboxes()
{
	if (enemy.getScale().x > 0)
	{
		for (auto &i : hitboxComponent.hitboxes)
		{
			i.setPosition(enemy.getPosition() + i.getOffset() * initialScale.x);
		}
	}
	else
	{
		for (auto& i : hitboxComponent.hitboxes)
		{
			i.setPosition(sf::Vector2f(enemy.getPosition().x - i.getGlobalBounds().width - i.getOffset().x * initialScale.x, enemy.getPosition().y + i.getOffset().y * initialScale.x));
		}
	}

}

int Enemy::getHp() const
{
	return currentHp;
}


void Enemy::setBlockWhichItsStandingOn(std::vector<Block>::const_iterator& block)
{
	isStandingOnBlock = true;
	blockItsStandingOn = block;
}

float Enemy::getPlayersDamageAfterCollision() const
{
	return playersDamageAfterCollision;
}

sf::Vector2f Enemy::getPosition() const
{
	return enemy.getPosition();
}

const sf::FloatRect& Enemy::getGlobalBoundsOfSprite() const
{
	return globalBoundsOfSprite;
}

void Enemy::calculeteGlobalBoundsOfSprite()
{
	globalBoundsOfSprite = enemy.getGlobalBounds();
}

EnemyType Enemy::getType() const
{
	return name;
}

void Enemy::setIsCollidingWithPlayer(bool isColliding)
{
	isCollidingWithPlayer = isColliding;
}

void Enemy::setWasDamageDealtToPlayer(bool wasDamageDealt)
{
	wasDamageDealtToPlayer = wasDamageDealt;
}

bool Enemy::getIsMortal()
{
	return isMortal;
}

void Enemy::tryTakeDamage(int amount)
{
	if (isMortal)
	{
		currentHp -= amount;
		healthBar.setValue(currentHp);
	}

}

void Enemy::tryChangeState(EnemyState newEnemyState, float newStateDuration)
{
	currentState = newEnemyState;
	timeToChangeToNormalState = newStateDuration;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(enemy, states);
	target.draw(healthBar, states);
}

