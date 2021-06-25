#pragma once
#include<SFML/Graphics.hpp>
#include<memory>
#include<unordered_map>
#include "HitboxComponent.h"
#include "AnimationComponent.h"
#include "EnemyProjectile.h"
#include "EnemyHealthBar.h"
#include "Block.h"
#include "Resources.h"
#include "MovingEnemyComponent.h"
#include "EnemiesTypes.h"
#include "EnemyStates.h"
#include "Fire.h"

class Enemy
	:public sf::Drawable
{
public:
	Enemy(const sf::Vector2f& Position, const sf::Texture& TextureOfEnemy, const Resources& resources,
		const Animation& Animation, const sf::Vector2f& healthBarOffset,
		const int InitialHp, const int PlayersDamageAfterCollision,
		bool isReiquireSATCollision);
	virtual ~Enemy();
	HitboxComponent hitboxComponent;
	HitboxComponent base;
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile> >& Projectiles, const sf::Vector2f & PlayerPosition, const float deltaTime);
	virtual void updateScale(const float PositionXOfPlayer);
	virtual void updateRotation(const sf::Vector2f& PlayerPosition);
	virtual void matchHitboxesToAnimation() = 0;
	void updateCurrentState(float deltaTime);
	virtual void playAnimation(const float deltaTime);
	virtual void moveWithBlock(float deltaTime);
	void updateHealthBar();
	void updatePositionOfHitboxes();
	int getHp() const;
	void setBlockWhichItsStandingOn(std::vector<Block>::const_iterator& block);
	float getPlayersDamageAfterCollision() const;
	sf::Vector2f getPosition() const;

	bool shouldUpdate;

	const sf::FloatRect& getGlobalBoundsOfSprite() const;
	void calculeteGlobalBoundsOfSprite();
	EnemyType getType() const;
	void setIsCollidingWithPlayer(bool isColliding);
	void setWasDamageDealtToPlayer(bool wasDamageDealt);
	bool getIsMortal();

	void tryTakeDamage(int amount);
	void tryChangeState(EnemyState newEnemyState, float newStateDuration);

	const bool isReiquireSATCollision;
	std::unique_ptr<MovingEnemyComponent> movingEnemyComponent;
protected:
	EnemyHealthBar healthBar;
	Animation animation;
	sf::Sprite enemy;
	sf::Vector2f initialScale;
	bool isGunEnemy{ false };
	EnemyType name;
	EnemyState currentState;
	float timeToChangeToNormalState;
	sf::FloatRect globalBoundsOfSprite;
	bool isCollidingWithPlayer;
	bool wasDamageDealtToPlayer;
	bool isMortal;
	int currentHp;
	float fireDamage;
	Fire fire;
	void tryTakeDamageWhenIsInFireState(float deltaTime);
	void updatePositionOfFireWhenIsInFireState();
	void animateFireWhenIsInFireState(float deltaTime);
	std::vector<Block>::const_iterator blockItsStandingOn;
	bool isStandingOnBlock{ false };
	const float playersDamageAfterCollision;
	std::unordered_map<EnemyState, bool> isResistantToGivenState;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
