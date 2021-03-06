#include "pch.h"
#include "EnemiesHandler.h"

EnemiesHandler::EnemiesHandler(std::vector<std::unique_ptr<Enemy>>& enemies, 
    std::vector< std::unique_ptr<EnemyProjectile> >& projectilesEnemy)
    :enemies(enemies), enemyProjectiles(projectilesEnemy)
{

}


void EnemiesHandler::setBlocksWhichEnemiesStandingOn(const std::vector<Block>& blocks, const std::vector<Block>& decorationBlocks)
{
    for (auto& enemy : enemies)
    {
        for (auto block = blocks.begin(); block != blocks.end(); block++)
        {
            if (enemy->base.allHitboxesIntersectWith(block->hitboxComponent))
            {
                enemy->setBlockWhichItsStandingOn(block);
            }
        }
        if (enemy->getType() == EnemyType::gunEnemy)
        {
            for (auto block = decorationBlocks.begin(); block != decorationBlocks.end(); block++)
            {
                if (enemy->base.allHitboxesIntersectWith(block->hitboxComponent))
                {
                    enemy->setBlockWhichItsStandingOn(block);
                }
            }
        }
    }
}

void EnemiesHandler::setShouldUpdate(float viewLeftPos, float viewRightPos)
{
    for (auto& i : enemies)
    {
        if (i->getGlobalBoundsOfSprite().left < viewRightPos + 600 and i->getGlobalBoundsOfSprite().left + i->getGlobalBoundsOfSprite().width > viewLeftPos - 600)
            i->shouldUpdate = true;
        else
            i->shouldUpdate = false;
    }
}

void EnemiesHandler::deleteEnemiesIfDead(Player& player, PlayerData& currentPlayerData, BonusesHandler& bonusesHandler)
{
    auto enemy = enemies.begin();
    bool wasEnemyDeleted = false;

    while (!enemies.empty())
    {
        bool isLastEnemy = msl::isLastElement(enemies, enemy);
        wasEnemyDeleted = false;
        
        if ((*enemy)->getHp() <= 0)
        {
            currentPlayerData.experienceOfPlayer += 100;
            bonusesHandler.tryAddBonus((*enemy)->getPosition(), player.getType());
            msl::fastErase(enemies, enemy);
            wasEnemyDeleted = true;
        }
        if (!wasEnemyDeleted)
            enemy++;

        if (isLastEnemy)
            break;
    }
}

void EnemiesHandler::updateEnemies(float deltaTime, const sf::Vector2f& playerPosition)
{
    for (auto& i : enemies)
    {
        i->moveWithBlock(deltaTime);
        i->updateCurrentState(deltaTime);
        if (i->movingEnemyComponent)
            i->movingEnemyComponent->move(deltaTime);
        if (i->shouldUpdate)
        {
            i->updateRotation(playerPosition);
            i->updateScale(playerPosition.x);
            i->attack(enemyProjectiles, playerPosition, deltaTime);
        }
        i->calculeteGlobalBoundsOfSprite();
    }
}

void EnemiesHandler::updateHealthBarEnemies()
{
    for (auto& i : enemies)
    {
        if (i->shouldUpdate)
        {
            i->updateHealthBar();
        }
    }
}

void EnemiesHandler::animateEnemies(float deltaTime)
{
    for (auto& i : enemies)
    {
        if (i->shouldUpdate)
            i->playAnimation(deltaTime);
    }
}

void EnemiesHandler::drawEnemies(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const
{
    for (auto const& i : enemies)
    {
        if (i->getGlobalBoundsOfSprite().left < viewRightPos and i->getGlobalBoundsOfSprite().left + i->getGlobalBoundsOfSprite().width > viewLeftPos)
            target.draw(*i);
    }
}
