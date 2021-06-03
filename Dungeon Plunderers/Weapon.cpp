#include "pch.h"
#include "Weapon.h"

Weapon::Weapon(const sf::Vector2f& Position, const sf::Vector2f& offset,
			const sf::Texture& TextureOfWeapon, const sf::Texture& TextureOfProjectile,
			const float fireRateOfWeapon, const float damageOfWeaponProjectile)
	:weapon(TextureOfWeapon),
	offset(offset),
	textureOfProjectile(TextureOfProjectile),
	fireRate(fireRateOfWeapon),
	damageOfProjectile(damageOfWeaponProjectile),
	timerOfShooting(0)
{
	weapon.setPosition(Position);
	initialScale = sf::Vector2f(1.f, 1.f);
}

Weapon::~Weapon()
{
}

void Weapon::animate(const float deltaTime)
{
	if (hasAnimation)
		animation.play(weapon, deltaTime);
}

void Weapon::updateTimerOfShooting(const float deltaTime)
{
	timerOfShooting += deltaTime;
}

void Weapon::setPosition(const sf::Vector2f& Position)
{
	weapon.setPosition(Position);
}

void Weapon::setRotation(const float angle)
{
	weapon.setRotation(angle);
}

void Weapon::setScale(const sf::Vector2f& factors)
{
	weapon.setScale(factors);
}

sf::Vector2f Weapon::getInitialScale() const
{
	return initialScale;
}


sf::Vector2f Weapon::getOffset()
{
	return offset;
}

sf::Vector2f Weapon::getPosition() const
{
	return weapon.getPosition();
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(weapon, states);
}
