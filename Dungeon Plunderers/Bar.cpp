#include "pch.h"
#include "Bar.h"


Bar::Bar(const sf::Vector2f& Position, const sf::Texture& textureOfBackground, const sf::Texture& textureOfBar, const sf::Font& font,
	const int maxValue, const int currentValue,
	const sf::Vector2f& offsetOfBar, unsigned int characterSize, const sf::Vector2f& offset)
	:maxValue(maxValue),
	offset(offset),
	initialSizeOfBarTexture(textureOfBar.getSize()),
	offsetOfBar(offsetOfBar)
{
	background.setTexture(textureOfBackground);
	background.setPosition(Position + offset);
	bar.setTexture(textureOfBar);
	bar.setPosition(Position + offset + offsetOfBar);

	value.setFont(font);
	value.setOutlineColor(sf::Color::Black);
	value.setOutlineThickness(2);
	value.setCharacterSize(characterSize);
	setValue(currentValue);
	value.setOrigin(sf::Vector2f(value.getGlobalBounds().left, value.getGlobalBounds().top) - value.getPosition());
}

Bar::~Bar()
{
}

void Bar::setValue(const int newValue)
{
	bar.setTextureRect(sf::IntRect(0, 0, static_cast<float>(newValue) / static_cast<float>(maxValue)* static_cast<float>(initialSizeOfBarTexture.x), initialSizeOfBarTexture.y));
	value.setString(std::to_wstring(newValue) + L"/" + std::to_wstring(maxValue));
	value.setPosition(bar.getPosition() + sf::Vector2f((bar.getTexture()->getSize().x - value.getGlobalBounds().width) / 2, (bar.getTexture()->getSize().y - value.getGlobalBounds().height) / 2));
}

void Bar::setMaxValue(const int newMaxValue)
{
	maxValue = newMaxValue;
}

void Bar::setPosition(const sf::Vector2f& Position)
{
	background.setPosition(Position);
	bar.setPosition(Position + offsetOfBar);
	value.setPosition(bar.getPosition() + sf::Vector2f((bar.getTexture()->getSize().x - value.getGlobalBounds().width) / 2, (bar.getTexture()->getSize().y - value.getGlobalBounds().height) / 2));
}

sf::Vector2f Bar::getOffset() const
{
	return offset;
}
sf::Vector2f Bar::getSize() const
{
	return sf::Vector2f(background.getTexture()->getSize().x, background.getTexture()->getSize().y);
}


void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(bar, states);
	target.draw(value, states);
}
