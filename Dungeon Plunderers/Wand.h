#pragma once
#include "Weapon.h"
#include "Fireball.h"
#include "Icicle.h"
#include "Electroball.h"
#include "ShadowBall.h"
#include <cmath>

enum class WandsTypes {
	basic,
	fire,
	ice,
	shadow
};

class Wand :
	public Weapon
{
public:
	Wand(const sf::Vector2f& Position, const sf::Vector2f& offset,
		const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile, int& ownerMana,
		const float fireRateOfWeapon, const float damageOfWeaponProjectile, const int manaCostOfShot, const WandsTypes name);
	virtual ~Wand();
	virtual void attack(std::vector< std::unique_ptr< PlayerProjectile > >& Projectile, const sf::Vector2f& mousePosition = sf::Vector2f(0.f, 0.f)) override;
	int getManaCostOfShot() const;
	WandsTypes getType() const;
private:
	int& ownerMana;
	WandsTypes name;
	int manaCostOfShot;
};

