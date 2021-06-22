#include "pch.h"
#include "ZombieInGround.h"


ZombieInGround::ZombieInGround(const sf::Vector2f& Position, const Resources& resources, const sf::Vector2f& initialScale)
	:RangedEnemy(Position, resources[TextureID::ZombieInGround], resources[TextureID::RockProjectile], resources,
		Animation(1, 1, sf::Vector2i(100, 108), 8, 0.1f), sf::Vector2f(-47.f, -30.f),
		200, 20,
		1.f, 30,
		false),
	canShoot(true)
{
	name = EnemyType::zombieInGround;
	enemy.setOrigin(40.f, 0.f);
	this->initialScale = initialScale;

	for (auto i = 0; i < 6; i++)
		hitboxComponent.addHitbox(Hitbox());

	hitboxComponent.setHitbox(0, sf::Vector2f(36.f, 108.f), sf::Vector2f(-16.f, 0.f));
	hitboxComponent.setHitbox(1, sf::Vector2f(4.f, 36.f), sf::Vector2f(20.f, 8.f));
	hitboxComponent.setHitbox(2, sf::Vector2f(4.f, 16.f), sf::Vector2f(24.f, 12.f));

	base.addHitbox(Hitbox(Position, sf::Vector2f(45.f, 4.f), sf::Vector2f(-18.f, 108.f)));

	matchHitboxesToAnimation();
}

ZombieInGround::~ZombieInGround()
{
}

void ZombieInGround::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime)
{
	timerOfShooting += deltaTime;
	if (animation.getNumberOfCurrentFrame() == 3 and canShoot)
	{
		if (enemy.getScale().x > 0)
		{
			Projectiles.emplace_back(std::make_unique<RockProjectile>(enemy.getPosition() + sf::Vector2f(50.f, 35.f), sf::Vector2f(900.f * enemy.getScale().x, 0.f), 20, textureOfProjectile));
		}
		else
		{
			Projectiles.emplace_back(std::make_unique<RockProjectile>(enemy.getPosition() + sf::Vector2f(-50.f, 35.f), sf::Vector2f(900.f * enemy.getScale().x, 0.f), 20, textureOfProjectile));
		}
		timerOfShooting = 0;
		canShoot = false;
	}
	if (animation.getNumberOfCurrentFrame() == 1)
		canShoot = true;
}

void ZombieInGround::matchHitboxesToAnimation()
{
	if (animation.wasFrameChanged())
	{
		switch (animation.getNumberOfCurrentFrame())
		{
		case 1:
			hitboxComponent.setHitbox(3, sf::Vector2f(48.f, 16.f), sf::Vector2f(-16.f, 52.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(16.f, 16.f), sf::Vector2f(28.f, 40.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(20.f, 16.f), sf::Vector2f(32.f, 32.f));
			break;
		case 2:
		case 8:
			hitboxComponent.setHitbox(3, sf::Vector2f(48.f, 16.f), sf::Vector2f(-16.f, 52.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(12.f, 16.f), sf::Vector2f(32.f, 44.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(16.f, 16.f), sf::Vector2f(40.f, 40.f));
			break;
		case 3:
		case 7:
			hitboxComponent.setHitbox(3, sf::Vector2f(32.f, 16.f), sf::Vector2f(28.f, 48.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(48.f, 16.f), sf::Vector2f(-16.f, 52.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(12.f, 20.f), sf::Vector2f(48.f, 48.f));
			break;
		case 4:
		case 6:
			hitboxComponent.setHitbox(3, sf::Vector2f(12.f, 20.f), sf::Vector2f(20.f, 56.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(12.f, 28.f), sf::Vector2f(32.f, 60.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(8.f, 16.f), sf::Vector2f(44.f, 68.f));
			break;
		case 5:
			hitboxComponent.setHitbox(3, sf::Vector2f(16.f, 24.f), sf::Vector2f(8.f, 60.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(12.f, 32.f), sf::Vector2f(24.f, 68.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(4.f, 16.f), sf::Vector2f(36.f, 80.f));
			break;
		}
	}
}

