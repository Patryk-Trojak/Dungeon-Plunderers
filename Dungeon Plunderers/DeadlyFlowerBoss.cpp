#include "pch.h"
#include "DeadlyFlowerBoss.h"

DeadlyFlowerBoss::DeadlyFlowerBoss(const sf::Vector2f& Position, const Resources& resources)
	:DeadlyFlower(Position, resources, sf::Vector2f(2.f, 2.f)),
	textureOfProjectile1(resources[TextureID::ProjectileOfBoss])
{
}

DeadlyFlowerBoss::~DeadlyFlowerBoss()
{
}

void DeadlyFlowerBoss::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f & PlayerPosition, const float deltaTime)
{
	timerOfWave += deltaTime;
	timerOfShooting += deltaTime;
	initialPositionOfProjectiles = enemy.getPosition() + sf::Vector2f(-120, 25) * initialScale.x;

	if (timerOfWave > 2)
	{
		switch (numberOfCurrentWave)
		{
		case 0:
			attack1(Projectiles);
			break;
		case 1:
			attack2(Projectiles);
			break;
		case 2:
			attack3(Projectiles);
			break;
		case 3:
			attack4(Projectiles);
			break;
		case 4:
			attack5(Projectiles);
			break;
		case 5:
			attack6(Projectiles);
			break;
		case 6:
			attack7(Projectiles);
			break;
		case 7:
			attack8(Projectiles, deltaTime);
			break;
		}
	}
}



void DeadlyFlowerBoss::attack1(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting > 2)
	{
		int j = rand(0, 1000);
		for (int i = 0; i < 20; i++)
		{
			EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-1500, -3050 + i * 400 + j), 40, textureOfProjectile1));
		}
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 6)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
		/*this->move = true;
		distancethis->moved = 0;
		distancethis->movedFalling = 0;
		if (Shape.getPosition().y < -3200)
		{
			jump = false;
		}
		if (Shape.getPosition().y > -2800)
		{
			jump = true;
		}
		*/
	}
}

void DeadlyFlowerBoss::attack2(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting> 0.3)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(rand(-2000, -1000), rand(-3500, 3500)), 40, textureOfProjectile1));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 50)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void DeadlyFlowerBoss::attack3(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting > 0.1)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-2000, -4500 + numberOfAttacksInWave * 280), 40, textureOfProjectile1));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 20)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0.f;
	}
}

void DeadlyFlowerBoss::attack4(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting > 0.1)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-2000, 4500 - numberOfAttacksInWave * 280), 40, textureOfProjectile1));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 20)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0.f;
	}
}

void DeadlyFlowerBoss::attack5(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting> 0.1)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-4000, 0), 40, textureOfProjectile1));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 15)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0.f;
	}
}

void DeadlyFlowerBoss::attack6(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting> 0.1)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-1500, -4000 + numberOfAttacksInWave * 500), 40, textureOfProjectile1));

		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-1500, 4000 - numberOfAttacksInWave * 500), 40, textureOfProjectile1));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 15)
	{
		numberOfCurrentWave ++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0.f;
		this->Move = true;
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

void DeadlyFlowerBoss::attack7(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (timerOfShooting > 0.1)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-1500, numberOfAttacksInWave * 500), 40, textureOfProjectile1));

		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-1500, -numberOfAttacksInWave * 500), 40, textureOfProjectile1));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	if (numberOfAttacksInWave == 15)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0.f;
	}
}

void DeadlyFlowerBoss::attack8(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime)
{
	if (timerOfShooting > 0.2)
	{
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-2000, rand(-1700, -300)), 40, textureOfProjectile1));
		numberOfAttacksInWave++;
		timerOfShooting = 0;
	}
	for (auto& i : EnemyProjectiles)
	{		
		i->addVelocity(sf::Vector2f(0, 2500 * deltaTime));
	}
	if (numberOfAttacksInWave == 20)
	{
		numberOfCurrentWave = 0;
		numberOfAttacksInWave = 0;
		timerOfWave = 0.f;
	}
}
