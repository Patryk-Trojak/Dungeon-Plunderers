#include "pch.h"
#include "SlimeProjectile.h"

SlimeProjectile::SlimeProjectile(const sf::Vector2f& Position, const sf::Vector2f& Velocity, const int Damage, const sf::Texture& Texture)
	:EnemyProjectile(Position, Velocity, Damage, Texture,
		Animation(1, 1, sf::Vector2i(72, 27), 6, 0.06f), Hitbox(Position, sf::Vector2f(13.7166f, 63.1369f), sf::Vector2f(1.38216f, -0.182159f)), false)
{
	animation.setFrame(projectile, 1);
	accelerationOfFalling = 100.f;
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(33.f, 27.f), sf::Vector2f(18.f, 0.f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(39.f, 21.f), sf::Vector2f(15.f, 3.f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(45.f, 15.f), sf::Vector2f(12.f, 6.f)));
}

SlimeProjectile::~SlimeProjectile()
{
}

void SlimeProjectile::addEffects(std::vector<std::unique_ptr<Effect>>& effects, const Resources& resources)
{
}

void SlimeProjectile::matchHitboxesToAnimation()
{
	switch (animation.getNumberOfCurrentFrame())
	{
	case 1:
		hitboxComponent.setHitbox(0, sf::Vector2f(33.f, 27.f), sf::Vector2f(21.f, 0.f));
		hitboxComponent.setHitbox(1, sf::Vector2f(39.f, 21.f), sf::Vector2f(18.f, 3.f));
		hitboxComponent.setHitbox(2, sf::Vector2f(45.f, 15.f), sf::Vector2f(15.f, 6.f));
		hitboxComponent.setHitbox(3, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
		break;
	case 2:
	case 3:
		hitboxComponent.setHitbox(0, sf::Vector2f(36.f, 27.f), sf::Vector2f(18.f, 0.f));
		hitboxComponent.setHitbox(1, sf::Vector2f(42.f, 21.f), sf::Vector2f(15.f, 3.f));
		hitboxComponent.setHitbox(2, sf::Vector2f(48.f, 15.f), sf::Vector2f(12.f, 6.f));
		hitboxComponent.setHitbox(3, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f));
		break;	
	case 4:
		hitboxComponent.setHitbox(0, sf::Vector2f(36.f, 27.f), sf::Vector2f(21.f, 0.f));
		hitboxComponent.setHitbox(1, sf::Vector2f(45.f, 21.f), sf::Vector2f(15.f, 3.f));
		hitboxComponent.setHitbox(2, sf::Vector2f(54.f, 15.f), sf::Vector2f(9.f, 6.f));
		hitboxComponent.setHitbox(3, sf::Vector2f(48.f, 18.f), sf::Vector2f(12.f, 6.f));
		break;
	case 5:
		hitboxComponent.setHitbox(0, sf::Vector2f(36.f, 27.f), sf::Vector2f(24.f, 0.f));
		hitboxComponent.setHitbox(1, sf::Vector2f(45.f, 21.f), sf::Vector2f(18.f, 3.f));
		hitboxComponent.setHitbox(2, sf::Vector2f(54.f, 15.f), sf::Vector2f(12.f, 6.f));
		hitboxComponent.setHitbox(3, sf::Vector2f(60.f, 9.f), sf::Vector2f(6.f, 9.f));
		break;
	case 6:
		hitboxComponent.setHitbox(0, sf::Vector2f(45.f, 21.f), sf::Vector2f(21.f, 3.f));
		hitboxComponent.setHitbox(1, sf::Vector2f(57.f, 15.f), sf::Vector2f(12.f, 6.f));
		hitboxComponent.setHitbox(2, sf::Vector2f(69.f, 9.f), sf::Vector2f(3.f, 9.f));
		hitboxComponent.setHitbox(3, sf::Vector2f(72.f, 3.f), sf::Vector2f(0.f, 12.f));
		break;
	}
}