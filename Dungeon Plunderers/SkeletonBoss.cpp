#include "pch.h"
#include "SkeletonBoss.h"


SkeletonBoss::SkeletonBoss(const sf::Vector2f& Position, const Resources& resources)
	:Skeleton(Position, sf::Vector2f(0, 0), resources, sf::Vector2f(2.f, 2.f)),
	textureOfProjectile(resources[TextureID::ProjectileOfBoss2])

{
	damageOfProjectiles = 20;
}

SkeletonBoss::~SkeletonBoss()
{

}

void SkeletonBoss::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime)
{
	timerOfShooting += deltaTime;
	timerOfWave += deltaTime;
	initialPositionOfProjectiles = enemy.getPosition() + sf::Vector2f(-120, 25) * initialScale.x;

	if (timerOfWave > 2.5)
	{
		switch (numberOfCurrentWave)
		{
		case 0:
			attack1(Projectiles, PlayerPosition);
			break;
		case 1:
			attack2(Projectiles);
			break;
		case 2:
			attack3(Projectiles, PlayerPosition);
			break;
		case 3:
			attack4(Projectiles);
			break;
		case 4:
			attack5(Projectiles, deltaTime);
			break;
		case 5:
			attack6(Projectiles);
			break;
		case 6:
			attack7(Projectiles, deltaTime);
			break;
		}
	}
}

void SkeletonBoss::attack1(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, const sf::Vector2f& playerPostion)
{
	if (timerOfShooting > 0.5)
	{
		sf::Vector2f distancePlayerAndBoss = playerPostion - initialPositionOfProjectiles + sf::Vector2f(150.f, 30.f);
		float distance = sqrt(pow(distancePlayerAndBoss.x, 2) + pow(distancePlayerAndBoss.y, 2));
		float angle = (asin(distancePlayerAndBoss.y / distance) * 180.0) / M_PI;

		sf::Vector2f velocityOfProjectile = sf::Vector2f(-5000 * cos(angle * M_PI / 180), 5000 * sin(angle * M_PI / 180));
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, velocityOfProjectile, damageOfProjectiles, textureOfProjectile));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 15)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void SkeletonBoss::attack2(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting > 0.2)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, -sf::Vector2f(3000, 0 + numberOfAttacksInWave * 300), damageOfProjectiles, textureOfProjectile));
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, -sf::Vector2f(3000, 0 + numberOfAttacksInWave * -300), damageOfProjectiles, textureOfProjectile));

		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 15)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void SkeletonBoss::attack3(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, const sf::Vector2f& playerPostion)
{
	if (timerOfShooting > 0.1)
	{
		sf::Vector2f distancePlayerAndBoss = playerPostion - initialPositionOfProjectiles + sf::Vector2f(150.f, 30.f);
		float distance = sqrt(pow(distancePlayerAndBoss.x, 2) + pow(distancePlayerAndBoss.y, 2));
		float angle = (asin(distancePlayerAndBoss.y / distance) * 180.0) / M_PI;

		sf::Vector2f velocityOfProjectile = sf::Vector2f(-3000 * cos(angle * M_PI / 180), 3000 * sin(angle * M_PI / 180));
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, velocityOfProjectile, damageOfProjectiles, textureOfProjectile));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 30)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}


void SkeletonBoss::attack4(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (numberOfAttacksInWave % 5 == 0)
	{
		velocity_YOfAttack = rand(0, 4000);
	}
	if (timerOfShooting > 0.05)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, sf::Vector2f(-3200, velocity_YOfAttack), damageOfProjectiles, textureOfProjectile));
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, sf::Vector2f(-3200, -velocity_YOfAttack), damageOfProjectiles, textureOfProjectile));
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, sf::Vector2f(-3200, 0), damageOfProjectiles, textureOfProjectile));

		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}

	if (numberOfAttacksInWave == 80)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void SkeletonBoss::attack5(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime)
{
	if (timerOfShooting > 0.03)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, sf::Vector2f(-3000, rand(-5000, 5000)), damageOfProjectiles, textureOfProjectile));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}

	for (auto& i : EnemyProjectiles)
	{
		i->addVelocity(sf::Vector2f(300 * deltaTime, 0));
	}


	if (numberOfAttacksInWave == 200)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}


void SkeletonBoss::attack6(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting > 0.11)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(sf::Vector2f(enemy.getPosition().x - rand(0, 3200), -1900), sf::Vector2f(0, 1500), damageOfProjectiles, textureOfProjectile));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}


	if (numberOfAttacksInWave == 250)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void SkeletonBoss::attack7(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime)
{
	if (timerOfShooting > 0.1)
	{
		if (numberOfAttacksInWave < 30)
		{
			velocity_YOfAttack = rand(-600, 600);
			EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, sf::Vector2f(-3000, velocity_YOfAttack), damageOfProjectiles, textureOfProjectile, 10000));
			EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, sf::Vector2f(-3000, -velocity_YOfAttack), damageOfProjectiles, textureOfProjectile, 10000));
			EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss2>(initialPositionOfProjectiles, sf::Vector2f(-3000, 0), damageOfProjectiles, textureOfProjectile, 10000));
		}
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}

	for (auto& i : EnemyProjectiles)
	{
		if (i->getInitialVelocity().y > 0)
		{
			i->addVelocity(sf::Vector2f(1560 * deltaTime, -160 * deltaTime));
		}
		else if (i->getInitialVelocity().y < 0)
		{
			i->addVelocity(sf::Vector2f(1560 * deltaTime, 160 * deltaTime));
		}

	}

	if (numberOfAttacksInWave == 100)
	{
		numberOfCurrentWave = 0;
		numberOfAttacksInWave = 0;
		timerOfWave = 1;
		Move = true;
		distanceMovedFalling = 0;
		if (enemy.getPosition().y < -3200)
		{
			jump = false;
		}
		if (enemy.getPosition().y > -2800)
		{
			jump = true;
		}
	}
}

