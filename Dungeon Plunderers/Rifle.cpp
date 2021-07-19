#include "pch.h"
#include "Rifle.h"


Rifle::Rifle(const sf::Vector2f& Position, const sf::Vector2f& offset,
	const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile,
	const float fireRateOfWeapon, const float damageOfWeaponProjectile,
	const int initialNumberOfAmmo)
	:Weapon(Position, offset, TextureOfWeapon, TextureOfProjectile, fireRateOfWeapon, damageOfWeaponProjectile)
{
	weapon.setOrigin(0, 20);
	weapon.setScale(0.45f, 0.6f);
	initialScale = sf::Vector2f(0.45f, 0.6f);
	currentNumberOfAmmo = initialNumberOfAmmo;
}

Rifle::~Rifle()
{
}

void Rifle::attack(std::vector<std::unique_ptr<PlayerProjectile>>& Projectile, const sf::Vector2f& mousePosition)
{
	if (timerOfShooting > fireRate and currentNumberOfAmmo > 0)
	{
		sf::Vector2f velocityOfProjectile = sf::Vector2f(3500 * cos(weapon.getRotation() * M_PI / 180) * weapon.getScale().x, 3500 * sin(weapon.getRotation() * M_PI / 180) * weapon.getScale().x);
		sf::Vector2f InitialPositionOfProjectile = sf::Vector2f(weapon.getPosition().x + cos((weapon.getRotation()) * M_PI / 180) * 185 * weapon.getScale().x + sin(weapon.getRotation() * M_PI / 180) * 3, weapon.getPosition().y + sin(weapon.getRotation() * M_PI / 180) * 185 * weapon.getScale().x - cos(weapon.getRotation() * M_PI / 180) * 3);
		Projectile.emplace_back(std::make_unique<Bullet>(InitialPositionOfProjectile + sf::Vector2f(0.f, 0.f), velocityOfProjectile, damageOfProjectile, textureOfProjectile));
		timerOfShooting = 0;
		currentNumberOfAmmo--;
	}
}

int Rifle::getNumberOfAmmo() const
{
	return currentNumberOfAmmo;
}

void Rifle::addNumberOfAmmo(int value)
{
	currentNumberOfAmmo += value;
}
