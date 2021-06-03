#include "pch.h"
#include "Wand.h"

Wand::Wand(const sf::Vector2f& Position, const sf::Vector2f& offset,
	const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile, int& ownerMana,
	const float fireRateOfWeapon, const float damageOfWeaponProjectile, const int manaCostOfShot, const WandsTypes name)
	:Weapon(Position, offset, TextureOfWeapon, TextureOfProjectile, fireRateOfWeapon, damageOfWeaponProjectile),
	name(name),
	manaCostOfShot(manaCostOfShot),
	ownerMana(ownerMana)
{
	weapon.setOrigin(30.f, 50.f);
	weapon.setScale(1, 1);
	initialScale = sf::Vector2f(1.f, 1.f);
	if (name == WandsTypes::basic)
	{
		weapon.setOrigin(30.f, 55.f);
		hasAnimation = true;
		animation = Animation(1, 1, sf::Vector2i(50, 119), 7, 0.05f);
		animation.setFrame(weapon, 1);
	}
	if (name == WandsTypes::shadow)
	{
		hasAnimation = true;
		animation = Animation(1, 1, sf::Vector2i(46, 114), 3, 0.1f);
		animation.setFrame(weapon, 1);
	}
}

Wand::~Wand()
{
}

void Wand::attack(std::vector<std::unique_ptr<PlayerProjectile>>& Projectile, const sf::Vector2f& mousePosition)
{
	if (timerOfShooting >= fireRate and ownerMana - manaCostOfShot >= 0)
	{
		sf::Vector2f distanceBetweenMouseAndArm = weapon.getPosition() + sf::Vector2f(22.f, 5) - weapon.getOrigin() - mousePosition;
		float distance = sqrt(pow(distanceBetweenMouseAndArm.x, 2) + pow(distanceBetweenMouseAndArm.y, 2));
		float angle = (asin(distanceBetweenMouseAndArm.y / distance) * 180.0) / M_PI;
		float rotation = -angle;
		int	multiplier = 1;

		if (distanceBetweenMouseAndArm.x > 0)
			multiplier = -1;
		else
			multiplier = 1;

		sf::Vector2f velocityOfProjectile = sf::Vector2f(800 * cos(rotation * M_PI / 180) * multiplier, 800 * sin(rotation * M_PI / 180));
		sf::Vector2f InitialPositionOfProjectile;
		if (weapon.getScale().x > 0)
			InitialPositionOfProjectile = weapon.getPosition() + sf::Vector2f(22.f, 5) - weapon.getOrigin();
		else
			InitialPositionOfProjectile = weapon.getPosition() - sf::Vector2f(22.f, -5) + sf::Vector2f(weapon.getOrigin().x, -weapon.getOrigin().y);
		
		switch (name)
		{
		case WandsTypes::basic:
			Projectile.emplace_back(std::make_unique<Electroball>(InitialPositionOfProjectile, velocityOfProjectile, 20, textureOfProjectile));
				break; 
		case WandsTypes::fire:
			Projectile.emplace_back(std::make_unique<Fireball>(InitialPositionOfProjectile, velocityOfProjectile, 20, textureOfProjectile, rotation * multiplier));
			break;
		case WandsTypes::ice:
			Projectile.emplace_back(std::make_unique<Icicle>(InitialPositionOfProjectile, velocityOfProjectile, 20, textureOfProjectile, rotation * multiplier));
			break;
		case WandsTypes::shadow:
			Projectile.emplace_back(std::make_unique<ShadowBall>(InitialPositionOfProjectile, velocityOfProjectile, 20, textureOfProjectile));
			break;
		}
		timerOfShooting = 0;

		ownerMana -= manaCostOfShot;
	}
}

int Wand::getManaCostOfShot() const
{
	return manaCostOfShot;
}

WandsTypes Wand::getType() const
{
	return name;
}
