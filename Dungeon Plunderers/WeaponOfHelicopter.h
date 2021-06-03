#pragma once
#include"Weapon.h"
#include"Bullet.h"

class WeaponOfHelicopter
	:public Weapon
{
public:
	WeaponOfHelicopter(const sf::Vector2f& Position, const sf::Vector2f& offset,
		const sf::Texture& TextureOfProjectile,
		const float fireRateOfWeapon, const float damageOfWeaponProjectile);
	virtual ~WeaponOfHelicopter();
	virtual void attack(std::vector< std::unique_ptr< PlayerProjectile > >& Projectile, const sf::Vector2f& mousePosition) override;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

