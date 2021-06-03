#pragma once
#include "Weapon.h"
#include "Bullet.h"
#include <cmath>

class Handgun :
	public Weapon
{
public:
	Handgun(const sf::Vector2f& Position, const sf::Vector2f& offset,
		const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile,
		const float fireRateOfWeapon, const float damageOfWeaponProjectile);
	virtual ~Handgun();
	virtual void attack(std::vector< std::unique_ptr< PlayerProjectile > >& Projectile, const sf::Vector2f& mousePosition = sf::Vector2f(0.f, 0.f)) override;
};

