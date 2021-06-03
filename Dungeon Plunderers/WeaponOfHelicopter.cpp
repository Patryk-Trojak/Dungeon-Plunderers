#include "pch.h"
#include "WeaponOfHelicopter.h"


WeaponOfHelicopter::WeaponOfHelicopter(const sf::Vector2f& Position, const sf::Vector2f& offset,
	const sf::Texture& TextureOfProjectile,
	const float fireRateOfWeapon, const float damageOfWeaponProjectile)
	:Weapon(Position, offset, sf::Texture(), TextureOfProjectile, fireRateOfWeapon, damageOfWeaponProjectile)
{
	weapon.setScale(1, 1);
}

WeaponOfHelicopter::~WeaponOfHelicopter()
{
}

void WeaponOfHelicopter::attack(std::vector<std::unique_ptr<PlayerProjectile>>& Projectile, const sf::Vector2f& mousePosition)
{
	if (timerOfShooting >= fireRate)
	{
		sf::Vector2f velocityOfProjectile = sf::Vector2f(800 * cos(weapon.getRotation() * M_PI / 180), 800 * sin(weapon.getRotation() * M_PI / 180));
		sf::Vector2f InitialPositionOfProjectile = sf::Vector2f((weapon.getPosition().x) + cos(weapon.getRotation() * M_PI / 180) + sin(weapon.getRotation() * M_PI / 180) , (weapon.getPosition().y) + sin(weapon.getRotation() * M_PI / 180)- cos(weapon.getRotation() * M_PI / 180) );
		Projectile.emplace_back(std::make_unique<Bullet>(InitialPositionOfProjectile, velocityOfProjectile, 20, textureOfProjectile));
		timerOfShooting = 0;
	}
}

void WeaponOfHelicopter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}
