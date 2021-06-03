#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include"Resources.h"

class BackgroundHandler
{
public:
	BackgroundHandler(std::array<sf::Sprite, 2>& backgrounds, const Resources& resources);
	void updatePositionsOfBackgrounds(float playerPositionX);
	void drawBackgrounds(sf::RenderTarget& target) const;
	void initBackgrounds(const sf::Vector2f& viewPosition);
private:
	std::array<sf::Sprite, 2>& backgrounds;
	const Resources& resources;
};

