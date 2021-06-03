#include "pch.h"
#include "IconButton.h"

IconButton::IconButton(const sf::Vector2f& Position, const sf::Vector2f& Size, 
	const sf::Texture& Texture, const sf::Texture& TextureOfSprite, 
	const sf::Vector2f& SizeOfIcon, ContentAlignment howAlignIcon, const float LeftMargin, 
	const sf::Color IdleColor, const sf::Color HoverColor)
	:Button(Position, Size, Texture, sf::Vector2f(1.f, 1.f), IdleColor, HoverColor),
	leftMargin(LeftMargin)
{
	state = ButtonState::idle;
	icon.setTexture(&TextureOfSprite);
	icon.setSize(SizeOfIcon);
	currentAlignment = howAlignIcon;
	alignContent(howAlignIcon);
}

IconButton::~IconButton()
{
}

void IconButton::setPosition(const sf::Vector2f& Position)
{
	shape.setPosition(Position);
	alignContent(currentAlignment);
}

void IconButton::setTextureOfIcon(const sf::Texture& Texture)
{
	icon.setTexture(&Texture);
	icon.setTextureRect(sf::IntRect(0, 0, Texture.getSize().x, Texture.getSize().y));
	alignContent(currentAlignment);
}

void IconButton::alignContent(ContentAlignment howAlignText)
{
	switch (howAlignText)
	{
	case ContentAlignment::center:
		icon.setPosition(shape.getPosition().x + shape.getSize().x / 2 - icon.getGlobalBounds().width / 2, shape.getPosition().y + (shape.getSize().y / 2) - (icon.getSize().y / 2));
		break;
	case ContentAlignment::left:
		icon.setPosition(shape.getPosition().x + leftMargin, shape.getPosition().y + shape.getSize().y / 2 - icon.getSize().y / 2);
		break;
	case ContentAlignment::right:
		icon.setPosition(shape.getPosition().x + shape.getSize().x - icon.getGlobalBounds().width - 10, shape.getPosition().y + shape.getSize().y / 2 - icon.getSize().y / 2);
		break;
	}
}


void IconButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(icon, states);

}
