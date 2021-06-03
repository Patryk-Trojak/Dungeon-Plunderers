#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"


class BlocksDrawer
	: public sf::Drawable
{
public:
	BlocksDrawer(const sf::Texture& texture);
	void addBlocksToVertexArray(const std::vector<Block>& blocks, bool areDecorationBlocks);
	void updatePositionsOfMovingBlocksVertex(const std::vector<std::vector<Block>::const_iterator> movingBlocks);
	void clearBlocks();
private:
	sf::VertexArray movingBlocksVertaxArray;
	sf::VertexArray blocksVertaxArray;
	sf::Texture blocksTexture;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

