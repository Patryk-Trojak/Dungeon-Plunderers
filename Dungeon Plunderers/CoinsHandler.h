#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Coin.h"


class CoinsHandler
{
public:
    CoinsHandler(std::vector<std::unique_ptr<Coin>>& coins);

    void animateCoins(const float deltaTime);
    void drawCoins(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const;
    void setBlocksWhichCoinsStandingOn(const std::vector<Block>& blocks);
    void moveCoinsWithBlocks(float deltaTime);
private:
    std::vector<std::unique_ptr<Coin>>& coins;
};

