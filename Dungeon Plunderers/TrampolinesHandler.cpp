#include "pch.h"
#include "TrampolinesHandler.h"

TrampolinesHandler::TrampolinesHandler(std::vector<Trampoline>& trampolines)
    :trampolines(trampolines)
{
}

void TrampolinesHandler::animateTrampolines(const float deltaTime)
{
    for (auto& trampoline : trampolines)
    {
        trampoline.tryPlayAnimation(deltaTime);
    }
}

void TrampolinesHandler::drawTrampolines(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const
{
    for (auto const& trampoline : trampolines)
    {
        if (trampoline.getGlobalBoundsOfSprite().left < viewRightPos and trampoline.getGlobalBoundsOfSprite().left + trampoline.getGlobalBoundsOfSprite().width > viewLeftPos)
            target.draw(trampoline);
    }
}

void TrampolinesHandler::setBlocksWhichTrampolinesStandingOn(const std::vector<Block>& blocks)
{
    for (auto& trampoline : trampolines)
    {
        for (auto block = blocks.begin(); block != blocks.end(); block++)
        {
            if (trampoline.base.allHitboxesIntersectWith(block->hitboxComponent))
            {
                trampoline.setBlockWhichItsStandingOn(block);
            }
        }
    }
}

void TrampolinesHandler::moveTrampolinesWithBlocks(float deltaTime)
{
    for (auto& trampoline : trampolines)
        trampoline.moveWithBlock(deltaTime);
}
