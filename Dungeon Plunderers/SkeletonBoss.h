#pragma once
#include "Skeleton.h"
#include "Boss.h"
#include "ElectroBall.h"
#include "ProjectileOfBoss.h"
#include "ProjectileOfBoss2.h"

class SkeletonBoss :
	public Skeleton,
	public Boss
{
public:
	SkeletonBoss(const sf::Vector2f& Position, const Resources& resources);
	virtual ~SkeletonBoss();
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);

private:
	void attack1(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, const sf::Vector2f& playerPostion);
	void attack2(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack3(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, const sf::Vector2f& playerPostion);
	void attack4(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	float velocity_YOfAttack{ 0 };
	void attack5(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime);
	void attack6(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack7(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime);
	float timerOfShooting{ 0 };
	const sf::Texture& textureOfProjectile;
};

