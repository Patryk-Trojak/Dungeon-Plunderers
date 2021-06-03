#pragma once
#include "Button.h"

class IconButton :
	public Button
{
public:
	IconButton(const sf::Vector2f& Position, const sf::Vector2f& Size,
		const sf::Texture& Texture, const sf::Texture& TextureOfSprite,
		const sf::Vector2f& SizeOfIcon, ContentAlignment howAlignIcon = ContentAlignment::center, const float LeftMargin = 10,
		const sf::Color IdleColor = sf::Color::White, const sf::Color HoverColor = sf::Color::Red);

	virtual ~IconButton();
	void setPosition(const sf::Vector2f& Position);
	void setTextureOfIcon(const sf::Texture& Texture);
private:
	sf::RectangleShape icon;
	ContentAlignment currentAlignment;
	void alignContent(ContentAlignment howAlignIcon);
	float leftMargin;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

