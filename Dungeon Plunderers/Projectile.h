#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "Movable.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "Effect.h"
#include "Blood1.h"
#include "Resources.h"
#include "Blood2.h"
#include "Blood3.h"
#include "Blood4.h"
#include "Blood5.h"

class Projectile
	: public sf::Drawable,
	public Movable
{
public:
	Projectile(const sf::Vector2f& Position, 
		const sf::Vector2f& Velocity, const int Damage,
		const sf::Texture& Texture,
		const Animation& Animation, const Hitbox& Hitbox, bool isReiquireSATCollision);
	virtual ~Projectile();
	HitboxComponent hitboxComponent;
	void animate(const float deltaTime);
	void update(const float deltaTime);
	float getDistanceMoved() const;
	sf::Vector2f getPosition() const;
	int getDamage() const;
	virtual void addEffects(std::vector<std::unique_ptr< Effect> >& effects, const Resources& resources) = 0;
	const sf::FloatRect& getGlobalBoundsOfSprite() const;
	void setPositionOfHitboxes();
	virtual void matchHitboxesToAnimation();
	const sf::Vector2f& getVelocity() const;
	void addVelocity(const sf::Vector2f& velocity);
	void setVelocity(const sf::Vector2f& newVelocity);
	bool split() const;
	void setSplit(bool split);
	float getDistanceOfErase() const;
	const bool isReiquireSATCollision;
protected:
	virtual void move(const float deltaTime) override;
	Animation animation;
	bool hasAnimation{ true };
	sf::Sprite projectile;
	sf::FloatRect globalBoundsOfSprite;
	float distanceMoved;
	float accelerationOfFalling;
	int damage;
	float distanceOfErase;
	bool Split;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

