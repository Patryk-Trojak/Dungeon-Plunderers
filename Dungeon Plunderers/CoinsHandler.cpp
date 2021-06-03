#include "pch.h"
#include "CoinsHandler.h"


CoinsHandler::CoinsHandler(std::vector<std::unique_ptr<Coin>>& coins)
    :coins(coins)
{

}


void CoinsHandler::setBlocksWhichCoinsStandingOn(const std::vector<Block>& blocks)
{
    for (auto& coin : coins)
    {
        for (auto block = blocks.begin(); block != blocks.end(); block++)
        {
            if (block->hitboxComponent.intersects(coin->base[0]) and
                block->hitboxComponent.intersects(coin->base[1]) and
                block->hitboxComponent.intersects(coin->base[2]))
            {
                coin->setBlockWhichItsStandingOn(block);
            }
        }
    }
}

void CoinsHandler::moveCoinsWithBlocks(float deltaTime)
{
    for (auto& i : coins)
        i->moveWithBlock(deltaTime);
}


void CoinsHandler::animateCoins(const float deltaTime)
{
    for (auto& i : coins)
    {
        i->animate(deltaTime);
    }
}

void CoinsHandler::drawCoins(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const
{
    for (auto const& i : coins)
    {
        if (i->getGlobalBoundsOfSprite().left < viewRightPos and i->getGlobalBoundsOfSprite().left + i->getGlobalBoundsOfSprite().width > viewLeftPos)
            target.draw(*i);
    }
}