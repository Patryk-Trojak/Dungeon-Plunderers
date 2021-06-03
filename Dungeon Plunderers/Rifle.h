#pragma once
#include<SFML/Graphics.hpp>
#include"Weapon.h"
#include "Bullet.h"

class Rifle
	: public Weapon
{
public:
	Rifle(const sf::Vector2f& Position, const sf::Vector2f& offset,
		const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile,
		const float fireRateOfWeapon, const float damageOfWeaponProjectile,
		const int initialNumberOfAmmo);
	virtual ~Rifle();
	virtual void attack(std::vector< std::unique_ptr< PlayerProjectile > >& Projectile, const sf::Vector2f& mousePosition = sf::Vector2f(0.f, 0.f)) override;
	int getNumberOfAmmo() const;
	void addNumberOfAmmo(int value);
private:
	int currentNumberOfAmmo;
};

