#include "pch.h"
#include "Handgun.h"

Handgun::Handgun(const sf::Vector2f& Position, const sf::Vector2f& offset,
	const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile,
	const float fireRateOfWeapon, const float damageOfWeaponProjectile)
	:Weapon(Position, offset, TextureOfWeapon, TextureOfProjectile, fireRateOfWeapon, damageOfWeaponProjectile)
{
	weapon.setOrigin(0, 20);
}

Handgun::~Handgun()
{
}

void Handgun::attack(std::vector<std::unique_ptr<PlayerProjectile>>& Projectile, const sf::Vector2f& mousePosition)
{
	if (timerOfShooting >= fireRate)
	{
		sf::Vector2f velocityOfProjectile = sf::Vector2f(800 * cos(weapon.getRotation() * M_PI / 180) * weapon.getScale().x, 800 * sin(weapon.getRotation() * M_PI / 180) * weapon.getScale().x);
		sf::Vector2f InitialPositionOfProjectile = sf::Vector2f((weapon.getPosition().x) + cos(weapon.getRotation() * M_PI / 180) * 45 * weapon.getScale().x + sin(weapon.getRotation() * M_PI / 180) * 15, (weapon.getPosition().y) + sin(weapon.getRotation() * M_PI / 180) * 45 * weapon.getScale().x - cos(weapon.getRotation() * M_PI / 180) * 15);
		Projectile.emplace_back(std::make_unique<Bullet>(InitialPositionOfProjectile, velocityOfProjectile, damageOfProjectile, textureOfProjectile));
		timerOfShooting = 0;
	}
}