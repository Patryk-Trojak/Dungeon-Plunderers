#pragma once
#include<vector>
#include<SFML/Graphics.hpp>
#include"Block.h"

class BlocksHandler
{
public:
	BlocksHandler(std::vector<Block>& blocks,
	std::vector<std::vector<Block>::const_iterator>& movingBlocks,
	std::vector<Block>& decorationBlocks);
	void moveAllBlocks(float deltaTime);
	void initIteratorsToMovingBlocks();
private:
	std::vector<Block>& blocks;
	std::vector<std::vector<Block>::const_iterator>& movingBlocks;
	std::vector<Block>& decorationBlocks;
	void moveBlocks(std::vector<Block>& blocks, float deltaTime);
	void initIteratorsToMovingBlocksFrom(const std::vector<Block>& blocks);
};

