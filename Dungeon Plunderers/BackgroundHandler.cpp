#include "pch.h"
#include "BackgroundHandler.h"

BackgroundHandler::BackgroundHandler(std::array<sf::Sprite, 2>& backgrounds, const Resources& resources)
	:backgrounds(backgrounds), resources(resources)
{
}

void BackgroundHandler::updatePositionsOfBackgrounds(float playerPositionX)
{
	for (auto& i : backgrounds)
	{
		if (playerPositionX - i.getPosition().x > 5000)
		{
			i.move(6600, 0);
		}
		if (playerPositionX - i.getPosition().x < -1900)
		{
			i.move(-6600, 0);
		}
	}
}

void BackgroundHandler::drawBackgrounds(sf::RenderTarget& target) const
{
	for (auto const& i : backgrounds)
		target.draw(i);
}

void BackgroundHandler::initBackgrounds(const sf::Vector2f& viewPosition)
{
	for (auto& i : backgrounds)
	{
		i.setTexture(resources[TextureID::BackgroundGame]);
		i.setTextureRect(sf::IntRect(0, 0, 3400, 1600));
	}
	backgrounds[0].setPosition(viewPosition.x - 1710.f, -250);
	backgrounds[1].setPosition(viewPosition.x + 1690.f, -250);
}
