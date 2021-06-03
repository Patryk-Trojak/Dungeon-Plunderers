#include "pch.h"
#include "Shotgun.h"

Shotgun::Shotgun(const sf::Vector2f& Position, const sf::Vector2f& offset,
				const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile,
				const float fireRateOfWeapon, const float damageOfWeaponProjectile,
				const int initialNumberOfAmmo)
	:Weapon(Position, offset, TextureOfWeapon, TextureOfProjectile, fireRateOfWeapon, damageOfWeaponProjectile)
{
	weapon.setOrigin(0, 15);
	//weapon.setScale(1.2f, 1.2f);
	initialScale = sf::Vector2f(1.2f, 1.2f);
	currentNumberOfAmmo = initialNumberOfAmmo;
}

Shotgun::~Shotgun()
{
}

void Shotgun::attack(std::vector<std::unique_ptr<PlayerProjectile>>& Projectile, const sf::Vector2f& mousePosition)
{
	if (timerOfShooting > 0.4/*fireRate and currentNumberOfAmmo > 0*/)
	{
		sf::Vector2f velocityOfNextProjectile = sf::Vector2f(800 * cos(weapon.getRotation() * M_PI / 180) * weapon.getScale().x, 800 * sin(weapon.getRotation() * M_PI / 180) * weapon.getScale().x);
		sf::Vector2f PositionOfProjectiles = sf::Vector2f(weapon.getPosition().x + cos(weapon.getRotation() * M_PI / 180) * 70 * weapon.getScale().x + sin(weapon.getRotation() * M_PI / 180) * 9, weapon.getPosition().y + sin(weapon.getRotation() * M_PI / 180) * 70 * weapon.getScale().x - cos(weapon.getRotation() * M_PI / 180) * 9);
		sf::Vector2f velocityOfFirstProjectile = velocityOfNextProjectile;
	//	Projectile.reserve(Projectile.size() + 5);

		Projectile.emplace_back(std::make_unique<Bullet>(PositionOfProjectiles, velocityOfNextProjectile, 20, textureOfProjectile));

		velocityOfNextProjectile.x -= sin(weapon.getRotation() * M_PI / 180) * 50;
		velocityOfNextProjectile.y += cos(weapon.getRotation() * M_PI / 180) * 50;
		Projectile.emplace_back(std::make_unique<Bullet>(PositionOfProjectiles, velocityOfNextProjectile, 20, textureOfProjectile));

		velocityOfNextProjectile = velocityOfFirstProjectile;
		velocityOfNextProjectile.x += sin(weapon.getRotation() * M_PI / 180) * 50;
		velocityOfNextProjectile.y -= cos(weapon.getRotation() * M_PI / 180) * 50;
		Projectile.emplace_back(std::make_unique<Bullet>(PositionOfProjectiles, velocityOfNextProjectile, 20, textureOfProjectile));

		velocityOfNextProjectile = velocityOfFirstProjectile;
		velocityOfNextProjectile.x -= sin(weapon.getRotation() * M_PI / 180) * 100;
		velocityOfNextProjectile.y += cos(weapon.getRotation() * M_PI / 180) * 100;
		Projectile.emplace_back(std::make_unique<Bullet>(PositionOfProjectiles, velocityOfNextProjectile, 20, textureOfProjectile));

		velocityOfNextProjectile = velocityOfFirstProjectile;
		velocityOfNextProjectile.x += sin(weapon.getRotation() * M_PI / 180) * 100;
		velocityOfNextProjectile.y -= cos(weapon.getRotation() * M_PI / 180) * 100;
		Projectile.emplace_back(std::make_unique<Bullet>(PositionOfProjectiles, velocityOfNextProjectile, 20, textureOfProjectile));
		timerOfShooting = 0;
		currentNumberOfAmmo--;
	}
}

int Shotgun::getNumberOfAmmo() const
{
	return currentNumberOfAmmo;
}

void Shotgun::addNumberOfAmmo(int value)
{
	currentNumberOfAmmo += value;
}
