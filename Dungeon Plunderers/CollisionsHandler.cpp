#include "pch.h"
#include "CollisionsHandler.h"


CollisionsHandler::CollisionsHandler(const Resources& resources, Level& level, std::shared_ptr<Player>& player, PlayerData& playerData,
	std::vector<std::unique_ptr<PlayerProjectile>>& playerProjectiles, std::vector<std::unique_ptr<EnemyProjectile>>& enemyProjectiles,
	std::vector<Bonus>& bonuses, std::vector< std::unique_ptr<Effect> >& effects, BonusesHandler& bonusesHandler)
	:level(level),
	player(player),
	playerProjectiles(playerProjectiles),
	enemyProjectiles(enemyProjectiles),
	bonuses(bonuses),
	timeSinceLastDamageDealtToPlayer(0),
	playerData(playerData),
	effects(effects),
	resources(resources),
	bonusesHandler(bonusesHandler)
{
}

CollisionsHandler::~CollisionsHandler()
{
}

void CollisionsHandler::PlayerAndBlock(float deltaTime)
{
	if (player->getType() == PlayerType::stormtrooper or player->getType() == PlayerType::wizard)
	{
		player->isAbleToMoveLeft = true;
		player->isAbleToMoveRight = true;
		player->isAbleToFall = true;
		player->isAbleToMoveUp = true;

		for (auto const& block : level.blocks)
		{
			if (block.hitboxComponent.intersects(player->globalBoundsOfHitboxes))
			{
				sf::Vector2f minDistanceToEdge = minDistanceToEdgeOfBlock(player->globalBoundsOfHitboxes, block);
				player->move(minDistanceToEdge);
				if (minDistanceToEdge.x > 0)
				{
					player->move(sf::Vector2f(-0.1, 0));
					player->isAbleToMoveLeft = false;
				}
				else if (minDistanceToEdge.x < 0)
				{
					player->move(sf::Vector2f(0.1, 0));
					player->isAbleToMoveRight = false;
				}
				else if (minDistanceToEdge.y > 0)
				{
					if (block.getVelocity().y > 0)
						player->currentVelocity.y = block.getVelocity().y;
					else
						player->currentVelocity.y = 0;

					player->stopJump = true;
					player->isAbleToMoveUp = false;
				}
				else if (minDistanceToEdge.y < 0)
				{
					player->move(block.getVelocity() * deltaTime + sf::Vector2f(0, 0.1));
					player->isAbleToFall = false;
				}
			}
		}
	}
}

void CollisionsHandler::PlayerAndCoins()
{
	auto coin = level.coins.begin();
	while (!level.coins.empty())
	{
		bool isLastCoin = msl::isLastElement(level.coins, coin);
		if(intersect(*player, *(*coin)))
		{
			if(level.name != LevelName::playerLevel)
				player->collectedMoney += 50;
			msl::fastErase(level.coins, coin); 
		}
		else
			coin++;

		if (isLastCoin)
			break;
	}
}

void CollisionsHandler::PlayerAndTrampolines()
{
	for (auto & i : level.trampolines)
	{
		if (intersect(*player, i))
		{
			if (i.getNumberOfFrameAnimation() == 1)
			{
				i.onCollisionWithPlayer(*player);
				break;
			}		
		}
	}
}

void CollisionsHandler::PlayerAndEnemies(const float deltaTime)
{
	timeSinceLastDamageDealtToPlayer += deltaTime;

	for (auto& enemy : level.enemies)
	{
		enemy->setIsCollidingWithPlayer(false);
		enemy->setWasDamageDealtToPlayer(false);
	}
	for (auto const& enemy : level.enemies)
	{
		if (intersect(*player, *enemy))
		{
			enemy->setIsCollidingWithPlayer(true);
			if (timeSinceLastDamageDealtToPlayer > 1.3f)
			{
				player->addHp(-enemy->getPlayersDamageAfterCollision());
				enemy->setWasDamageDealtToPlayer(true);
				if (enemy->getType() == EnemyType::showingAfterDamageSpikes)
					enemy->playAnimation(0.f);
				timeSinceLastDamageDealtToPlayer = 0;
			}
			break;
		}
	}
}

void CollisionsHandler::PlayerAndEnemyProjectiles()
{
	if (player->getType() != PlayerType::wizardOnCloud)
	{
		NormalPlayerAndEnemyProjectilesCollision();
	}
	else
	{
		WizardAndEnemyProjectiles();
	}
}

void CollisionsHandler::PlayerAndBonuses()
{
	auto bonus = bonuses.begin();
	while (!bonuses.empty())
	{
		bool isLastBonus = msl::isLastElement(bonuses, bonus);
		if (intersect(*player, *bonus))
		{
			player->handleGettingBonus(bonus->getType());
			msl::fastErase(bonuses, bonus);
		}
		else
			bonus++;

		if (isLastBonus)
			break;
	}
}

void CollisionsHandler::AllProjectilesAndBlock()
{
	ProjectilesAndBlock(playerProjectiles);
	ProjectilesAndBlock(enemyProjectiles);
}


void CollisionsHandler::ProjectilesAndEnemies()
{
	auto enemy = level.enemies.begin();
	bool wasEnemyDeleted = false;
	while (!level.enemies.empty())
	{
		bool isLastEnemy = msl::isLastElement(level.enemies, enemy);
		wasEnemyDeleted = false;
		auto projectile = playerProjectiles.begin();
		while (!playerProjectiles.empty())
		{
			bool isLastProjectile = msl::isLastElement(playerProjectiles, projectile);
			if (intersect(*(*projectile), *(*enemy)))
			{
				if ( (*enemy)->getIsMortal())
				{
					(*projectile)->onCollisionWithEnemy(*(*enemy));

					if ((*enemy)->getHp() <= 0)
					{
						playerData.experienceOfPlayer += 100;
						bonusesHandler.tryAddBonus((*enemy)->getPosition(), player->getType());
						msl::fastErase(level.enemies, enemy);
						wasEnemyDeleted = true;
					} 
				}
				(*projectile)->addEffects(effects, resources);
				msl::fastErase(playerProjectiles, projectile);
				if (wasEnemyDeleted)
					break;
			}
			else 
			{
				projectile++;
			}
			if (isLastProjectile)
				break;
		}
		if(!wasEnemyDeleted)
			enemy++;	

		if (isLastEnemy)
			break;
	}
}

void CollisionsHandler::BonusesAndBlocks(const float deltaTime)
{
	bool isBonusColliding = false;

	for (auto& bonus : bonuses)
	{
		bonus.setIsAbleToFall(true);
		for (auto const& block : level.blocks)
		{
			if (block.hitboxComponent.intersects(bonus.hitboxComponent))
			{
				sf::Vector2f minDistanceToEdge = minDistanceToEdgeOfBlock(bonus.hitboxComponent[0], block);
				bonus.move(minDistanceToEdge);
				if (minDistanceToEdge.y < 0)
				{
					bonus.setIsAbleToFall(false);
					bonus.move(block.getVelocity() * deltaTime + sf::Vector2f(0, 0.1));
				}
			}
		}
	}
}

bool CollisionsHandler::intersect(Projectile& projectile, Enemy& enemy)
{
	if (intersects(projectile.getGlobalBoundsOfSprite(), enemy.getGlobalBoundsOfSprite()))
	{
		enemy.matchHitboxesToAnimation();
		enemy.updatePositionOfHitboxes();
		projectile.matchHitboxesToAnimation();
		projectile.setPositionOfHitboxes();

		if (enemy.isReiquireSATCollision or projectile.isReiquireSATCollision)
		{
			if (projectile.hitboxComponent.intersectsSAT(enemy.hitboxComponent))
				return true;
		}
		else
		{
			if (projectile.hitboxComponent.intersects(enemy.hitboxComponent))
				return true;
		}
	}
	return false;
}

bool CollisionsHandler::intersect(Projectile& projectile, const Block& block)
{
	if (block.hitboxComponent.intersects(projectile.getGlobalBoundsOfSprite()))
	{
		projectile.matchHitboxesToAnimation(); 
		projectile.setPositionOfHitboxes(); 

		if (projectile.isReiquireSATCollision)
		{
			if (projectile.hitboxComponent.intersectsSAT(block.hitboxComponent))
				return true;
		}
		else
		{
			if (projectile.hitboxComponent.intersects(block.hitboxComponent))
				return true;
		}
	}
	return false;
}

bool CollisionsHandler::intersect(Player& player, Bonus& bonus)
{
	if (bonus.hitboxComponent.intersects(player.getGlobalBoundsOfSprite()))
	{
		if (player.hitboxComponent.intersects(bonus.hitboxComponent))
		{
			return true;
		}
	}

	return false;
}

bool CollisionsHandler::intersect(const Player& player, const Coin& coin)
{
	if (coin.hitboxComponent.intersects(player.getGlobalBoundsOfSprite()))
	{
		if (player.hitboxComponent.intersects(coin.hitboxComponent))
		{
			return true;
		}
	}
	return false;
}

bool CollisionsHandler::intersect(const Player& player, Enemy& enemy)
{
	if (intersects(player.getGlobalBoundsOfSprite(), enemy.getGlobalBoundsOfSprite()))
	{
		enemy.matchHitboxesToAnimation();
		enemy.updatePositionOfHitboxes();
		if (enemy.isReiquireSATCollision)
		{
			if (player.hitboxComponent.intersectsSAT(enemy.hitboxComponent))
				return true;
		}
		else
		{
			if (player.hitboxComponent.intersects(enemy.hitboxComponent))
				return true;
		}
	}

	return false;
}

bool CollisionsHandler::intersect(const Player& player, Projectile& projectile)
{
	if (intersects(player.getGlobalBoundsOfSprite(), projectile.getGlobalBoundsOfSprite()))
	{
		projectile.matchHitboxesToAnimation();
		projectile.setPositionOfHitboxes();
		if (player.hitboxComponent.intersects(projectile.hitboxComponent))
		{
			return true;
		}
	}

	return false;
}

bool CollisionsHandler::intersect(const Player& player, const Trampoline& trampoline)
{
	return trampoline.hitboxComponent.intersects(player.globalBoundsOfHitboxes);
}

template<typename ProjectilesType>
void CollisionsHandler::ProjectilesAndBlock(std::vector<std::unique_ptr<ProjectilesType>>& projectiles)
{
	for (auto const& block : level.blocks)
	{
		auto projectile = projectiles.begin();
		while (!projectiles.empty())
		{
			bool isLastProjectile = msl::isLastElement(projectiles, projectile);
			if (intersect(*(*projectile), block))
			{
				msl::fastErase(projectiles, projectile);
			}
			else
			{
				projectile++;
			}
			if (isLastProjectile)
				break;
		}
	}
}





void CollisionsHandler::NormalPlayerAndEnemyProjectilesCollision()
{
	auto projectile = enemyProjectiles.begin();
	while (!enemyProjectiles.empty())
	{
		bool isLastProjectile = msl::isLastElement(enemyProjectiles, projectile);
		if(intersect(*player, *(*projectile)))
		{
			player->addHp(-projectile->get()->getDamage());
			msl::fastErase(enemyProjectiles, projectile);
		}
		else
		{
			projectile++;
		}
		if (isLastProjectile)
			break;
	}
}

void CollisionsHandler::WizardAndEnemyProjectiles()
{
	std::shared_ptr<WizardOnCloud> wizardOnCloud = std::static_pointer_cast<WizardOnCloud>(player);
	auto projectile = enemyProjectiles.begin();
	bool eraseProjectile = false;
	while (!enemyProjectiles.empty())
	{
		eraseProjectile = false;
		bool isLastProjectile = msl::isLastElement(enemyProjectiles, projectile);
		if ( (*projectile)->getGlobalBoundsOfSprite().intersects(wizardOnCloud->globalBoundsOfHitboxes.getGlobalBounds()))
		{
			projectile->get()->matchHitboxesToAnimation();
			projectile->get()->setPositionOfHitboxes();
			if (wizardOnCloud->shieldHitboxes.intersects(projectile->get()->hitboxComponent.getHitboxes()))
			{
				wizardOnCloud->addShieldHp(-projectile->get()->getDamage());
				eraseProjectile = true;
			}
			else if (wizardOnCloud->cloudHitboxes.intersects(projectile->get()->hitboxComponent.getHitboxes()))
			{
				wizardOnCloud->addCloudHp(-projectile->get()->getDamage());
				eraseProjectile = true;
			}
			else if (wizardOnCloud->hitboxComponent.intersects(projectile->get()->hitboxComponent.getHitboxes()))
			{
				wizardOnCloud->addHp(-(*projectile)->getDamage());
				eraseProjectile = true;
			}
		}
		if (eraseProjectile)
		{
			msl::fastErase(enemyProjectiles, projectile);
		}
		else
		{
			projectile++;
		}

		if (isLastProjectile)
			break;
	}

}

sf::Vector2f CollisionsHandler::minDistanceToEdgeOfBlock(const Hitbox& hitbox, const Block& block)
{
	sf::Vector2f minDistanceToTop(0, block.top() - hitbox.getBottom());
	sf::Vector2f minDistanceToBottom(0, block.bottom() - hitbox.getTop());
	sf::Vector2f minDistanceToLeft(block.left() - hitbox.getRight(), 0);
	sf::Vector2f minDistanceToRight(block.right() - hitbox.getLeft(), 0);

	return std::min({ minDistanceToTop, minDistanceToBottom, minDistanceToLeft, minDistanceToRight },
		[](const sf::Vector2f& distance1, const sf::Vector2f& distance2) {
			return abs(distance1.x) + abs(distance1.y) < abs(distance2.x) + abs(distance2.y);
		});
}

inline bool CollisionsHandler::intersects(const sf::FloatRect& f1, const sf::FloatRect& f2)
{
	if (f1.left + f1.width >= f2.left)
	{
		if (f1.left <= f2.left + f2.width)
		{
			if (f1.top + f1.height >= f2.top)
			{
				if (f1.top <= f2.top + f2.height)
				{
					return true;
				}
			}
		}
	}
	return false;
}
