#include "pch.h"
#include "BlocksHandler.h"

BlocksHandler::BlocksHandler(std::vector<Block>& blocks,
	std::vector<std::vector<Block>::const_iterator>& movingBlocks,
	std::vector<Block>& decorationBlocks)
	:blocks(blocks),
	movingBlocks(movingBlocks),
	decorationBlocks(decorationBlocks)
{
	initIteratorsToMovingBlocks();
}

void BlocksHandler::moveAllBlocks(float deltaTime)
{
	moveBlocks(blocks, deltaTime);
	moveBlocks(decorationBlocks, deltaTime);
}

void BlocksHandler::initIteratorsToMovingBlocks()
{
	initIteratorsToMovingBlocksFrom(blocks);
	initIteratorsToMovingBlocksFrom(decorationBlocks);
}

void BlocksHandler::moveBlocks(std::vector<Block>& blocks, float deltaTime)
{
	for (auto& i : blocks)
	{
		i.move(deltaTime);
	}
}

void BlocksHandler::initIteratorsToMovingBlocksFrom(const std::vector<Block>& blocks)
{
	for (auto i = blocks.begin(); i < blocks.end(); i++)
	{
		if (i->getVelocity() != sf::Vector2f(0.f, 0.f))
		{
			movingBlocks.emplace_back(i);
		}
	}
}
