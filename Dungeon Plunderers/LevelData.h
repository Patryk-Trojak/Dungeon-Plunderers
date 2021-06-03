#pragma once
#include<SFML/Graphics.hpp>
#include"Block.h"
#include"Coin.h"
#include"Enemy.h"
#include"LevelName.h"

struct Level
{
	std::vector<Block> blocks;
	std::vector<Block> decorationBlocks;
	std::vector<std::unique_ptr<Coin>> coins;
	std::vector<std::unique_ptr<Enemy>> enemies;
	sf::Vector2f initialPositionOfPlayer;
	sf::Vector2f endOfLevelPosition;
	LevelName name;

	void clear()
	{
		blocks.clear();
		decorationBlocks.clear();
		coins.clear();
		enemies.clear();
	}
};
