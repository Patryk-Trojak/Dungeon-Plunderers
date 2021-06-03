#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <memory>
#include "Animation.h"

class PlayerProjectile;

class Weapon
	: public sf::Drawable
{
public:
	Weapon(const sf::Vector2f& Position, const sf::Vector2f& offset,
		const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile,
		const float fireRateOfWeapon, const float damageOfWeaponProjectile);
	virtual ~Weapon();
	virtual void attack(std::vector<std::unique_ptr<PlayerProjectile>>& Projectile, const sf::Vector2f& mousePosition = sf::Vector2f(0.f, 0.f)) = 0;
	void animate(const float deltaTime);
	void updateTimerOfShooting(const float deltaTime);
	void setPosition(const sf::Vector2f& Position);
	void setRotation(const float angle);
	void setScale(const sf::Vector2f& factors);
	sf::Vector2f getInitialScale() const;
	sf::Vector2f getOffset();
	sf::Vector2f getPosition() const;
protected:
	Animation animation;
	bool hasAnimation{ false };
	sf::Sprite weapon;
	const sf::Texture& textureOfProjectile;
	sf::Vector2f offset;
	float fireRate;
	float damageOfProjectile;
	float timerOfShooting;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f initialScale;
	
};


