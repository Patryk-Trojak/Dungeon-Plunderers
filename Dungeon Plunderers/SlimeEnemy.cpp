#include "pch.h"
#include "SlimeEnemy.h"

SlimeEnemy::SlimeEnemy(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale)
	:RangedEnemy(Position, resources[TextureID::Slime], resources[TextureID::SlimeProjectile], resources,
		Animation(1, 1, sf::Vector2i(96, 96), 8, 0.07f), sf::Vector2f(-63.f, -30.f),
		200, 20,
		1.f, 30,
		false),
	canShoot(true)
{
	movingEnemyComponent = std::make_unique<MovingEnemyComponent>(enemy, currentState, initialScale, sf::Vector2f(200.f, 200.f), ChangeDirectionDistance);
	name = EnemyType::slimeEnemy;
	enemy.setOrigin(63.f, 0.f);
	this->initialScale = initialScale;
	for (auto i = 0; i < 10; i++)
		hitboxComponent.addHitbox(Hitbox());

	base.addHitbox(Hitbox(Position, sf::Vector2f(41.f, 4.f), sf::Vector2f(-38.f, 96.f)));


	fire.setOrigin(sf::Vector2f(13.5f, 5.f));
	fire.setScale(sf::Vector2f(2.f, 2.f));
}

SlimeEnemy::~SlimeEnemy()
{
}

void SlimeEnemy::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime)
{
	timerOfShooting += deltaTime;
	if (animation.getNumberOfCurrentFrame() == 7 and canShoot)
	{
		if (enemy.getScale().x > 0)
		{
			Projectiles.emplace_back(std::make_unique<SlimeProjectile>(enemy.getPosition() + sf::Vector2f(12, 25), sf::Vector2f(900.f * enemy.getScale().x, 0.f), damageOfProjectile, textureOfProjectile));
		}
		else
		{
			Projectiles.emplace_back(std::make_unique<SlimeProjectile>(enemy.getPosition() + sf::Vector2f(-12, 25), sf::Vector2f(900.f * enemy.getScale().x, 0.f), damageOfProjectile, textureOfProjectile));
		}
		timerOfShooting = 0;
		canShoot = false;
	}
	if (animation.getNumberOfCurrentFrame() == 1)
		canShoot = true;
}

void SlimeEnemy::matchHitboxesToAnimation()
{
	if (animation.wasFrameChanged())
	{
		switch (animation.getNumberOfCurrentFrame())
		{
		case 1:
		case 8:
			hitboxComponent.setHitbox(0, sf::Vector2f(30.f, 90.f), sf::Vector2f(-18.f, 6.f));
			hitboxComponent.setHitbox(2, sf::Vector2f(39.f, 84.f), sf::Vector2f(-21.f, 12.f));
			hitboxComponent.setHitbox(3, sf::Vector2f(51.f, 72.f), sf::Vector2f(-24.f, 24.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(57.f, 54.f), sf::Vector2f(-30.f, 42.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(66.f, 30.f), sf::Vector2f(-39.f, 66.f));
			hitboxComponent.setHitbox(6, sf::Vector2f(72.f, 18.f), sf::Vector2f(-45.f, 78.f));
			hitboxComponent.setHitbox(7, sf::Vector2f(81.f, 12.f), sf::Vector2f(-54.f, 84.f));
			hitboxComponent.setHitbox(8, sf::Vector2f(87.f, 6.f), sf::Vector2f(-60.f, 90.f));
			hitboxComponent.setHitbox(9, sf::Vector2f(45.f, 81.f), sf::Vector2f(-21.f, 15.f));
			break;
		case 2:
		case 7:
			hitboxComponent.setHitbox(0, sf::Vector2f(30.f, 93.f), sf::Vector2f(-18.f, 3.f));
			hitboxComponent.setHitbox(1, sf::Vector2f(39.f, 88.f), sf::Vector2f(-21.f, 9.f));
			hitboxComponent.setHitbox(2, sf::Vector2f(51.f, 75.f), sf::Vector2f(-24.f, 21.f));
			hitboxComponent.setHitbox(3, sf::Vector2f(54.f, 57.f), sf::Vector2f(-30.f, 39.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(66.f, 33.f), sf::Vector2f(-39.f, 63.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(72.f, 21.f), sf::Vector2f(-45.f, 75.f));
			hitboxComponent.setHitbox(6, sf::Vector2f(81.f, 12.f), sf::Vector2f(-54.f, 84.f));
			hitboxComponent.setHitbox(7, sf::Vector2f(87.f, 6.f), sf::Vector2f(-60.f, 90.f));
			hitboxComponent.setHitbox(8, sf::Vector2f(6.f, 84.f), sf::Vector2f(18.f, 12.f));
			break;
		case 3:
			hitboxComponent.setHitbox(0, sf::Vector2f(33.f, 96.f), sf::Vector2f(-18.f, 0.f));
			hitboxComponent.setHitbox(1, sf::Vector2f(45.f, 90.f), sf::Vector2f(-21.f, 6.f));
			hitboxComponent.setHitbox(2, sf::Vector2f(51.f, 79.f), sf::Vector2f(-24.f, 18.f));
			hitboxComponent.setHitbox(3, sf::Vector2f(57.f, 64.f), sf::Vector2f(-30.f, 33.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(66.f, 36.f), sf::Vector2f(-39.f, 60.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(72.f, 25.f), sf::Vector2f(-45.f, 72.f));
			hitboxComponent.setHitbox(6, sf::Vector2f(81.f, 13.f), sf::Vector2f(-54.f, 84.f));
			hitboxComponent.setHitbox(7, sf::Vector2f(87.f, 7.f), sf::Vector2f(-60.f, 90.f));
			hitboxComponent.setHitbox(8, sf::Vector2f(60.f, 49.f), sf::Vector2f(-33.f, 48.f));
			break;
		case 4:
		case 6:
			hitboxComponent.setHitbox(0, sf::Vector2f(36.f, 96.f), sf::Vector2f(-15.f, 0.f));
			hitboxComponent.setHitbox(1, sf::Vector2f(42.f, 90.f), sf::Vector2f(-18.f, 6.f));
			hitboxComponent.setHitbox(2, sf::Vector2f(51.f, 66.f), sf::Vector2f(-21.f, 18.f));
			hitboxComponent.setHitbox(3, sf::Vector2f(51.f, 66.f), sf::Vector2f(-24.f, 27.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(54.f, 48.f), sf::Vector2f(-30.f, 48.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(63.f, 33.f), sf::Vector2f(-36.f, 60.f));
			hitboxComponent.setHitbox(6, sf::Vector2f(66.f, 24.f), sf::Vector2f(-42.f, 72.f));
			hitboxComponent.setHitbox(7, sf::Vector2f(78.f, 12.f), sf::Vector2f(-54.f, 84.f));
			hitboxComponent.setHitbox(8, sf::Vector2f(84.f, 6.f), sf::Vector2f(-60.f, 90.f));
			hitboxComponent.setHitbox(9, sf::Vector2f(54.f, 57.f), sf::Vector2f(-27.f, 36.f));
			break;
		case 5:
			hitboxComponent.setHitbox(0, sf::Vector2f(36.f, 96.f), sf::Vector2f(-12.f, 0.f));
			hitboxComponent.setHitbox(1, sf::Vector2f(42.f, 87.f), sf::Vector2f(-15.f, 6.f));
			hitboxComponent.setHitbox(2, sf::Vector2f(51.f, 66.f), sf::Vector2f(-18.f, 18.f));
			hitboxComponent.setHitbox(3, sf::Vector2f(51.f, 60.f), sf::Vector2f(-21.f, 27.f));
			hitboxComponent.setHitbox(4, sf::Vector2f(51.f, 48.f), sf::Vector2f(-27.f, 48.f));
			hitboxComponent.setHitbox(5, sf::Vector2f(66.f, 24.f), sf::Vector2f(-33.f, 60.f));
			hitboxComponent.setHitbox(6, sf::Vector2f(63.f, 24.f), sf::Vector2f(-39.f, 72.f));
			hitboxComponent.setHitbox(7, sf::Vector2f(78.f, 12.f), sf::Vector2f(-54.f, 84.f));
			hitboxComponent.setHitbox(8, sf::Vector2f(84.f, 6.f), sf::Vector2f(-60.f, 90.f));
			hitboxComponent.setHitbox(9, sf::Vector2f(48.f, 60.f), sf::Vector2f(-24.f, 36.f));

			break;
		}
		if (animation.getNumberOfCurrentFrame() == 7)
		{
			hitboxComponent.setHitbox(0, sf::Vector2f(6.f, 15.f), sf::Vector2f(27.f, 36.f));
		}
	}
}