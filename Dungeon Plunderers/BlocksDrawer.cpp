#include "pch.h"
#include "BlocksDrawer.h"

BlocksDrawer::BlocksDrawer(const sf::Texture& texture)
	: blocksTexture(texture),
	blocksVertaxArray(sf::Quads),
	movingBlocksVertaxArray(sf::Quads)
{

}

void BlocksDrawer::addBlocksToVertexArray(const std::vector<Block>& blocks, bool areDecorationBlocks)
{
	sf::VertexArray* currentVertex;
	float textureCoordsY = 0;
	if (areDecorationBlocks)
		textureCoordsY = 50;
	for (auto const& i : blocks)
	{
		sf::Vector2f size = i.getSize();
		sf::Vector2f initPosition(static_cast<int>(i.getPosition().x - i.getSize().x / 2.f), static_cast<int>(i.getPosition().y - i.getSize().y / 2.f));

		int name = static_cast<int>(i.getType());
		if (i.getVelocity() == sf::Vector2f(0.f, 0.f))
			currentVertex = &blocksVertaxArray;
		else
			currentVertex = &movingBlocksVertaxArray;

		for (int x = 0; x < i.getSize().x / 50.f; x++)
		{
			for (int y = 0; y < i.getSize().y / 50.f; y++)
			{
				sf::Vector2f position = initPosition + sf::Vector2f(x * 50.f, y * 50.f);

				currentVertex->append(sf::Vertex(position, sf::Vector2f((name == 0 ? 0 : 1) + name * 50.f, textureCoordsY)));
				currentVertex->append(sf::Vertex(position + sf::Vector2f(50.f, 0.f), sf::Vector2f(50.f + name * 50.f, textureCoordsY)));
				currentVertex->append(sf::Vertex(position + sf::Vector2f(50.f, 50.f), sf::Vector2f(50.f + name * 50.f, textureCoordsY + 50.f - (name == 0 ? 0 : 1))));
				currentVertex->append(sf::Vertex(position + sf::Vector2f(0.f, 50.f), sf::Vector2f((name == 0 ? 0 : 1) + name * 50.f, textureCoordsY + 50.f - (name == 0 ? 0 : 1))));
			}
		}
	}
}

void BlocksDrawer::updatePositionsOfMovingBlocksVertex(const std::vector<std::vector<Block>::const_iterator> movingBlocks)
{
	size_t currentVertex = 0;
	for (auto const& i : movingBlocks)
	{
		sf::Vector2f initPosition = i->getPosition() - i->getSize() / 2.f;
		for (int x = 0; x < static_cast<int>(i->getSize().x); x += 50)
		{
			for (int y = 0; y < static_cast<int>(i->getSize().y); y += 50)
			{
				sf::Vector2f position = initPosition + sf::Vector2f(x, y);

				movingBlocksVertaxArray[currentVertex].position = position;
				movingBlocksVertaxArray[currentVertex + 1].position = position + sf::Vector2f(50.f, 0.f);
				movingBlocksVertaxArray[currentVertex + 2].position = position + sf::Vector2f(50.f, 50.f);
				movingBlocksVertaxArray[currentVertex + 3].position = position + sf::Vector2f(0.f, 50.f);
				currentVertex += 4;
			}
		}
	}
}

void BlocksDrawer::clearBlocks()
{
	blocksVertaxArray.clear();
	movingBlocksVertaxArray.clear();
}

void BlocksDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(movingBlocksVertaxArray, &blocksTexture);
	target.draw(blocksVertaxArray, &blocksTexture);
}
