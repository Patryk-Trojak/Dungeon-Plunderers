#include "pch.h"
#include "ZombieBoss.h"

ZombieBoss::ZombieBoss(const sf::Vector2f& Position, const Resources& resources, bool isPlayerStormtrooper)
	: Zombie(Position, sf::Vector2f(0, 0), resources, sf::Vector2f(2.f, 2.f)),
	textureOfProjectile(resources[TextureID::ProjectileOfBoss]),
	textureOfWarning(resources[TextureID::Warning]),
	textureOfLaser(resources[TextureID::Laser]),
	createAttackWarning{true},
	isPlayerStormtrooper{ isPlayerStormtrooper }
{	
}

ZombieBoss::~ZombieBoss()
{
}


void ZombieBoss::attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime)
{
	timerOfShooting += deltaTime;
	timerOfWave += deltaTime;
	initialPositionOfProjectiles = enemy.getPosition();
	Projectiles.reserve(300);
	if (timerOfWave > 2.5)
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
			attack4(Projectiles, deltaTime);
			break;
		case 4:
			attack5(Projectiles, deltaTime);
			break;
		case 5:
			attack6(Projectiles, deltaTime);
			break;
		}
	}
}


void ZombieBoss::attack1(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (createAttackWarning && timerOfShooting > 2)
	{
		EnemyProjectiles.clear();
		float playerHeight = (isPlayerStormtrooper ? 150 : 300);
		float posY = rand(-385, 1465 - playerHeight - 100);
		float currentPosOfWarning = posY + playerHeight + 70;

		while (currentPosOfWarning + 150 < 1465)
		{
			EnemyProjectiles.emplace_back(std::make_unique<Warning>(sf::Vector2f(3300.f, currentPosOfWarning), sf::Vector2f(0, 0), damageOfProjectiles, textureOfWarning));
			currentPosOfWarning += rand(0, 140) + 150;
		}
		currentPosOfWarning = posY;
		while (currentPosOfWarning - 150 > -385)
		{
			currentPosOfWarning -= rand(0, 140) + 150;
			EnemyProjectiles.emplace_back(std::make_unique<Warning>(sf::Vector2f(3300.f, currentPosOfWarning), sf::Vector2f(0, 0), damageOfProjectiles, textureOfWarning));
		}
		createAttackWarning = false;

	}
	if (timerOfShooting > 4)
	{
		size_t sizeOfWarning = EnemyProjectiles.size();
		for (size_t i = 0; i < sizeOfWarning; i++)
		{
			EnemyProjectiles.emplace_back(std::make_unique<Laser>(sf::Vector2f(350.f, EnemyProjectiles[i]->getPosition().y), sf::Vector2f(0, 0), damageOfProjectiles, textureOfLaser));
		}
		
		for (auto warning = EnemyProjectiles.begin(); warning != EnemyProjectiles.begin() + sizeOfWarning; warning++)
		{
			*warning = std::move(EnemyProjectiles.back());
			EnemyProjectiles.pop_back();
		}

		numberOfAttacksInWave++;
		timerOfShooting = 0;
		createAttackWarning = true;
	}

	if (numberOfAttacksInWave == 6)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void ZombieBoss::attack2(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	if (SplitProjectile && timerOfShooting > 1.5)
	{
		for (int i = 0; i < EnemyProjectiles.size(); i++)
		{
			if (EnemyProjectiles[i]->split())
			{
				EnemyProjectiles[i]->setSplit(false);
				EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(EnemyProjectiles[i]->getPosition(), sf::Vector2f(rand(-400, 400), rand(-400, 400)), damageOfProjectiles, textureOfProjectile));
				EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(EnemyProjectiles[i]->getPosition(), sf::Vector2f(rand(-300, 300), rand(-300, 300)), damageOfProjectiles, textureOfProjectile));
				EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(EnemyProjectiles[i]->getPosition(), sf::Vector2f(rand(-400, 400), rand(-400, 400)), damageOfProjectiles, textureOfProjectile));
				EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(EnemyProjectiles[i]->getPosition(), sf::Vector2f(rand(-400, 400), rand(-400, 400)), damageOfProjectiles, textureOfProjectile));
				EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(EnemyProjectiles[i]->getPosition(), sf::Vector2f(rand(-300, 300), rand(-300, 300)), damageOfProjectiles, textureOfProjectile));
				EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(EnemyProjectiles[i]->getPosition(), sf::Vector2f(rand(-400, 400), rand(-400, 400)), damageOfProjectiles, textureOfProjectile));
			}
		}
		SplitProjectile = false;

	}
	if (timerOfShooting > 2)
	{
		if (numberOfAttacksInWave == 0)
		{
			EnemyProjectiles.clear();
		}
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-600, rand(-400, 400)), damageOfProjectiles, textureOfProjectile));
		EnemyProjectiles.back()->setSplit(true);
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-600, rand(-400, 400)), damageOfProjectiles, textureOfProjectile));
		EnemyProjectiles.back()->setSplit(true);
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-600, rand(-400, 400)), damageOfProjectiles, textureOfProjectile));
		EnemyProjectiles.back()->setSplit(true);


		numberOfAttacksInWave++;
		timerOfShooting = 0;
		SplitProjectile = true;
	}

	if (numberOfAttacksInWave == 10)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = -4;
	}
}

void ZombieBoss::attack3(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	bounceProjectiles(EnemyProjectiles);
	if (timerOfShooting > 0.5 and numberOfAttacksInWave < 40)
	{
		if (numberOfAttacksInWave == 0)
		{
			EnemyProjectiles.clear();
		}
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-600, rand(-250, 250)), damageOfProjectiles, textureOfProjectile, 10000));

		numberOfAttacksInWave++;
		timerOfShooting = 0;
		SplitProjectile = true;
	}

	if (timerOfShooting > 10)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void ZombieBoss::attack4(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime)
{
	if (numberOfAttacksInWave == 0)
	{
		velocity_YOfattack = -1000;
		addVelocityYOfProjectiles = false;
	}
	if (velocity_YOfattack <= -1600)
	{
		addVelocityYOfProjectiles = true;
	}
	if (velocity_YOfattack >= -800)
	{
		addVelocityYOfProjectiles = false;
	}

	if (addVelocityYOfProjectiles)
	{
		velocity_YOfattack += 150 * deltaTime;
	}
	else
	{
		velocity_YOfattack += -150 * deltaTime;
	}
	bounceProjectiles(EnemyProjectiles);
	if (timerOfShooting > 0.02 and numberOfAttacksInWave < 400)
	{
		if (numberOfAttacksInWave == 0)
		{
			EnemyProjectiles.clear();
		}
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-400, velocity_YOfattack), damageOfProjectiles, textureOfProjectile, 20000));

		numberOfAttacksInWave++;
		timerOfShooting = 0;
		SplitProjectile = true;
	}

	if (timerOfShooting > 4)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void ZombieBoss::attack5(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime)
{
	if (numberOfAttacksInWave == 0)
	{
		velocity_YOfattack = 1740;
		addVelocityYOfProjectiles = false;
	}
	if (velocity_YOfattack <= -1900)
	{
		addVelocityYOfProjectiles = true;
	}
	if (velocity_YOfattack >= 1900)
	{
		addVelocityYOfProjectiles = false;
	}

	if (addVelocityYOfProjectiles)
	{
		velocity_YOfattack += 1600 * deltaTime;
	}
	else
	{
		velocity_YOfattack += -1600 * deltaTime;
	}
	if (timerOfShooting > 0.05)
	{
		if (numberOfAttacksInWave == 0)
		{
			EnemyProjectiles.clear();
		}
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-2400, velocity_YOfattack), damageOfProjectiles, textureOfProjectile));

		numberOfAttacksInWave++;
		timerOfShooting = 0;
		SplitProjectile = true;
	}

	if (numberOfAttacksInWave == 90)
	{
		numberOfCurrentWave++;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
	}
}

void ZombieBoss::attack6(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime)
{
	if (numberOfAttacksInWave == 0)
	{
		velocity_YOfattack = 0;
		addVelocityYOfProjectiles = false;
	}
	if (velocity_YOfattack <= -400)
	{
		addVelocityYOfProjectiles = true;
	}
	if (velocity_YOfattack >= 300)
	{
		addVelocityYOfProjectiles = false;
	}

	if (addVelocityYOfProjectiles)
	{
		velocity_YOfattack += 800 * deltaTime;
	}
	else
	{
		velocity_YOfattack += -800 * deltaTime;
	}
	if (timerOfShooting > 0.03)
	{
		for (int i = 0; i < 7; i++)
		{
			EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-2700, (velocity_YOfattack - 3200) + i * 800), damageOfProjectiles, textureOfProjectile));

		}

		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-500, 1200 - velocity_YOfattack), damageOfProjectiles, textureOfProjectile));
		EnemyProjectiles.emplace_back(std::make_unique<ProjectileOfBoss>(initialPositionOfProjectiles, sf::Vector2f(-500, -1200 - velocity_YOfattack), damageOfProjectiles, textureOfProjectile));


		numberOfAttacksInWave++;
		timerOfShooting = 0;
		SplitProjectile = true;
	}
	eraseProjectileIfItOutOfScreen(EnemyProjectiles);
	
	if (numberOfAttacksInWave == 200)
	{
		numberOfCurrentWave = 0;
		numberOfAttacksInWave = 0;
		timerOfWave = 0;
		Move = true;
		distanceMoved = sf::Vector2f(0.f, 0.f);
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

void ZombieBoss::eraseProjectileIfItOutOfScreen(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	auto projectile = EnemyProjectiles.begin();
	while (projectile != EnemyProjectiles.end())
	{
		if (projectile->get()->getGlobalBoundsOfSprite().top + projectile->get()->getGlobalBoundsOfSprite().height < -400
			or projectile->get()->getGlobalBoundsOfSprite().top > 1500
			or projectile->get()->getGlobalBoundsOfSprite().left + projectile->get()->getGlobalBoundsOfSprite().width < 300)
		{
			*projectile = std::move(EnemyProjectiles.back());
			EnemyProjectiles.pop_back();
		}
		else
			projectile++;
	}
}

void ZombieBoss::bounceProjectiles(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles)
{
	for (auto& i : EnemyProjectiles)
	{
		if (i->getPosition().x <= 445.556)
		{
			i->setVelocity(sf::Vector2f(abs(i->getInitialVelocity().x) * 1, i->getVelocity().y));
		}
		if (i->getPosition().x >= 3550.44)
		{
			i->setVelocity(sf::Vector2f(abs(i->getInitialVelocity().x) * -1, i->getVelocity().y));
		}
		if (i->getPosition().y <= -290)
		{
			i->setVelocity(sf::Vector2f(i->getVelocity().x, abs(i->getInitialVelocity().y)));
		}
		if (i->getPosition().y >= 1370)
		{
			i->setVelocity(sf::Vector2f(i->getVelocity().x, -abs(i->getInitialVelocity().y)));
		}
	}
}

