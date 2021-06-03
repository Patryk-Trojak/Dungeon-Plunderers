#pragma once
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include "Movable.h"
#include "HitboxComponent.h"
#include "AnimationComponent.h"
#include "Weapon.h"
#include "PlayerData.h"
#include "Bonus.h"
#include "Keybinds.h"
#include "Resources.h"
#include "StatsPlayerCreator.h"

class GameplayState;

enum class PlayerType {
	stormtrooper, wizard, helicopter, wizardOnCloud
};

class Player
	:public Movable, 
	public sf::Drawable
{
public:
	Player(const sf::Vector2f& Position, const sf::Texture& TextureOfPlayer, const Keybinds& keybinds);
	virtual ~Player();
	HitboxComponent hitboxComponent;
	Hitbox globalBoundsOfHitboxes;

	void update(const sf::Vector2f& MousePosition);
	void attack(std::vector< std::unique_ptr< PlayerProjectile > >& Projectile, const sf::Vector2f& mousePosition);
	void animateWeapon(float deltaTime);
	virtual void matchHitboxesToAnimation() = 0;
	virtual void setPosition(const sf::Vector2f& Position);
	virtual void setPositionRelativeToHitbox(const sf::Vector2f& Position);
	virtual void handleGettingBonus(BonusesTypes name) = 0;
	void move(const sf::Vector2f& offset);
	sf::Vector2f getPosition() const;
	const sf::FloatRect& getGlobalBoundsOfSprite() const;
	float centerX() const;
	float right() const;
	float left() const;
	float top() const;
	float bottom() const;
	void addHp(const int value);
	const int& getCurrentHp() const;
	const int& getInitialHp() const;
	virtual void animate(const float deltaTime) = 0;
	void updateMove(const float deltaTime);
	void updateCurrentWeaponShootTimer(const float deltaTime);
	void calculateGlobalBoundsOfSprite();
	void setValue(int currentHp);
	void setInitialHp(int initHp);
	PlayerType getType();
	int collectedMoney{ 0 };
protected:
	PlayerType name;
	void move(const float deltaTime) override;
	virtual void setCurrentVelocityX(const float deltaTime) = 0;
	virtual void setCurrentVelocityY(const float deltaTime) = 0;
	virtual void setRotationOfArm(const sf::Vector2f& MousePosition);
	virtual void setScaleOfPlayer(const sf::Vector2f& MousePosition);
	virtual void setPositionOfHitboxes();
	virtual void setPositionOfArm() = 0;
	void setPositionOfWeapon();
	virtual void setCurrentWeapon() = 0;
	virtual void handleDrinkingPotions() = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect globalBoundsOfSprite;

	sf::Sprite player;
	Animation animation;
	sf::Sprite arm;
	sf::Vector2f pointOfArmRotation;
	std::shared_ptr<Weapon> currentWeapon;
	const Keybinds& keybinds;
 
	int currentHp;
	int initialHp;


	float accelerationOfJumping{-10100};
	float accelerationOfFalling{6000};
	float timeOfJump{0};

	bool isAbleToMoveLeft{ true };
	bool isAbleToMoveRight{ true };
	bool isAbleToFall{ true };
	bool isJumping{ true };
	bool isAbleToMoveUp{ true };
	bool isTurnedLeft{ true };
	bool isMovingLeft{ true };
	bool isMovingRight{ true };
	bool stopJump{ true };

	friend class GameplayState;
	friend class CollisionsHandler;
};

