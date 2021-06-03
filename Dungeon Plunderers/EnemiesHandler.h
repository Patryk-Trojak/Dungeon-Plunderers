#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemy.h"


class EnemiesHandler
{
public:
    EnemiesHandler(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector< std::unique_ptr<EnemyProjectile> >& enemyProjectiles);
    void setBlocksWhichEnemiesStandingOn(const std::vector<Block>& blocks, const std::vector<Block>& decorationBlocks);
    void updateEnemies(float deltaTime, const sf::Vector2f& playerPosition);
    void animateEnemies(float deltaTime);
    void updateHealthBarEnemies();
    void drawEnemies(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const;
    void setShouldUpdate(float viewLeftPos, float viewRightPos);
private:
    std::vector< std::unique_ptr<Enemy> >& enemies;
    std::vector< std::unique_ptr<EnemyProjectile> >& enemyProjectiles;
};
