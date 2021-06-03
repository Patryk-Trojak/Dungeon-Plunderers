#pragma once
#include "Zombie.h"
#include "ProjectileOfBoss.h"
#include "Warning.h"
#include "Laser.h"
#include "Boss.h"

class ZombieBoss :
	public Zombie,
	public Boss
{
public:
	ZombieBoss(const sf::Vector2f& Position, const Resources& resources, bool isPlayerStormtrooper);
	virtual ~ZombieBoss();
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);

private:
	void attack1(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack2(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack3(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack4(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime);
	float velocity_YOfattack{ 0 };
	void attack5(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime);
	void attack6(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime);
	//void attack7(std::vector<std::unique_ptr<Projectile>>& EnemyProjectiles, float deltaTime);
	bool createAttackWarning;
	float timerOfShooting{ 0 };

	bool SplitProjectile;
	bool addVelocityYOfProjectiles;
	const sf::Texture& textureOfProjectile;
	const sf::Texture& textureOfWarning;
	const sf::Texture& textureOfLaser;

	bool isPlayerStormtrooper;


	void eraseProjectileIfItOutOfScreen(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);

	void bounceProjectiles(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
};

