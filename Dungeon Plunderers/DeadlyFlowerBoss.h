#pragma once
#include "DeadlyFlower.h"
#include "Boss.h"
#include "ProjectileOfBoss.h"

class DeadlyFlowerBoss
	: public DeadlyFlower,
	public Boss
{
public:
	DeadlyFlowerBoss(const sf::Vector2f& Position, const Resources& resources);
	virtual ~DeadlyFlowerBoss();
	virtual void attack(std::vector<std::unique_ptr<EnemyProjectile>>& Projectiles, const sf::Vector2f& PlayerPosition, const float deltaTime);

private:
	void attack1(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack2(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack3(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack4(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack5(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack6(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack7(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles);
	void attack8(std::vector<std::unique_ptr<EnemyProjectile>>& EnemyProjectiles, float deltaTime);

	const sf::Texture& textureOfProjectile1;
};

