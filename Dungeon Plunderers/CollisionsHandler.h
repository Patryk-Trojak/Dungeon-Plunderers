#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "Wizard.h"
#include "WizardOnCloud.h"
#include "Stormtrooper.h"
#include "Projectile.h"
#include "Block.h"
#include "Enemy.h"
#include "Bonus.h"
#include "Coin.h"
#include "LevelData.h"
#include "BonusesHandler.h"
#include "MySimpleLibrary.hpp"

class CollisionsHandler
{
public:
	CollisionsHandler(const Resources& resources, Level& level, std::shared_ptr<Player>& player, PlayerData& playerData,
		std::vector< std::unique_ptr<PlayerProjectile> >& playerProjectiles, std::vector< std::unique_ptr<EnemyProjectile> >& enemyProjectiles,
		std::vector<Bonus>& bonuses, std::vector< std::unique_ptr<Effect> >& effects, BonusesHandler& bonusesHandler);
	~CollisionsHandler();
	void PlayerAndBlock(float deltaTime);
	void PlayerAndCoins();
	void PlayerAndTrampolines();
	void PlayerAndEnemies(const float deltaTime);
	void PlayerAndEnemyProjectiles();
	void PlayerAndBonuses();
	void AllProjectilesAndBlock();
	void ProjectilesAndEnemies();
	void BonusesAndBlocks(const float deltaTime);
	

private:
	bool intersect(Projectile& projectile, Enemy& enemy);
	bool intersect(Projectile& projectile, const Block& block);
	bool intersect(Player& player, Bonus& bonus);
	bool intersect(const Player& player, const Coin& coin);
	bool intersect(const Player& player, Enemy& enemy);
	bool intersect(const Player& player, Projectile& projectile);
	bool intersect(const Player& player, const Trampoline& trampoline);

	template<typename ProjectilesType>
	void ProjectilesAndBlock(std::vector< std::unique_ptr<ProjectilesType> >& projectiles);

	void NormalPlayerAndEnemyProjectilesCollision();
	void WizardAndEnemyProjectiles();
	sf::Vector2f minDistanceToEdgeOfBlock(const Hitbox& hitbox, const Block& block);
	float timeSinceLastDamageDealtToPlayer;
	inline bool intersects(const sf::FloatRect& f1, const sf::FloatRect& f2);
private:
	Level& level;
	std::shared_ptr<Player>& player;
	std::vector< std::unique_ptr<PlayerProjectile> >& playerProjectiles;
	std::vector< std::unique_ptr<EnemyProjectile> >& enemyProjectiles;
	std::vector<Bonus>& bonuses;
	const Resources& resources;
	std::vector< std::unique_ptr<Effect> >& effects;
	PlayerData& playerData;
	BonusesHandler& bonusesHandler;
};


