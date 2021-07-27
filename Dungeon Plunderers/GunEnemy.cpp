#include "pch.h"
#include "GunEnemy.h"

GunEnemy::GunEnemy(const sf::Vector2f& Position, const Resources& resources, const sf::Vector2f& initialScale)
	:RangedEnemy(Position, resources[TextureID::GunEnemy], resources[TextureID::EnemyBullet], resources,
		Animation(1, 1, sf::Vector2i(166, 72), 1, 0.5f), sf::Vector2f(-55.f, -70.f),
		200, 20,
		1.f, 30, 
		false),
	laser(sf::Lines, 2)
{
	name = EnemyType::gunEnemy;
	enemy.setOrigin(35.5f, 35.5f);
	this->initialScale = initialScale;
	base.addHitbox(Hitbox(Position + sf::Vector2f(-25.f, -25.f), sf::Vector2f(50.f, 50.f), sf::Vector2f(-25.f, -25.f)));
	isGunEnemy = true;

	laser[0].color = sf::Color::Red;
	laser[1].color = sf::Color::Red;

	animation.setFrame(enemy, 1);

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(129.185f, 24.327f), sf::Vector2f(0.f, 0.f), sf::Vector2f(35.6494f, 11.5546)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(56.2037f, 55.8681f), sf::Vector2f(0.f, 0.f), sf::Vector2f(27.5986f, 27.4306)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(24.0033f, 72.097f), sf::Vector2f(0.f, 0.f), sf::Vector2f(11.5315f, 35.5314)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(134.987f, 7.98015f), sf::Vector2f(0.f, 0.f), sf::Vector2f(35.4911f, 3.49023)));

	isResistantToGivenState[EnemyState::fire] = true;
	isResistantToGivenState[EnemyState::frost] = true;
}


GunEnemy::~GunEnemy()
{
}

void GunEnemy::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime)
{
	timerOfShooting += deltaTime;
	if (timerOfShooting > 1.5f)
	{
		sf::Vector2f velocityOfProjectile = sf::Vector2f(800 * cos(enemy.getRotation() * M_PI / 180), 800 * sin(enemy.getRotation() * M_PI / 180));
		sf::Vector2f InitialPositionOfProjectile = enemy.getPosition() + sf::Vector2f(cos(enemy.getRotation() * M_PI / 180) * 65, sin(enemy.getRotation() * M_PI / 180) * 65);

		Projectiles.emplace_back(std::make_unique<EnemyBullet>(InitialPositionOfProjectile, velocityOfProjectile, damageOfProjectile, textureOfProjectile));
		timerOfShooting = 0;
	}
}

void GunEnemy::matchHitboxesToAnimation()
{
}

void GunEnemy::updateRotation(const sf::Vector2f& PlayerPosition)
{
	laser[0].position = enemy.getPosition();
	laser[1].position = PlayerPosition + sf::Vector2f(0.f, 80.f);
	sf::Vector2f distanceBetweenEnemyAndPlayer = enemy.getPosition() - (PlayerPosition + sf::Vector2f(0.f, 80.f));
	float distance = sqrt(pow(distanceBetweenEnemyAndPlayer.x, 2) + pow(distanceBetweenEnemyAndPlayer.y, 2));
	float angle = (asin(distanceBetweenEnemyAndPlayer.y / distance) * 180.0) / M_PI;
	if (PlayerPosition.x > enemy.getPosition().x)
	{
		enemy.setRotation(-angle);
		hitboxComponent.setRotationOfAllHitboxes(-angle);
	}
	else
	{
		enemy.setRotation(-180 + angle);
		hitboxComponent.setRotationOfAllHitboxes(-180 + angle);
	}
}

void GunEnemy::updateScale(const float PositionXOfPlayer)
{
}

void GunEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(laser);
	target.draw(enemy);
	target.draw(healthBar);
}

