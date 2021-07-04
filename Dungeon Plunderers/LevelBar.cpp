#include "pch.h"
#include "LevelBar.h"


LevelBar::LevelBar(const sf::Vector2f& position, const Resources& resources,
	const int experienceToNextLevel, const int currentExperience, const int currentLevel)
	:Bar(position, 
		resources[TextureID::LevelBarBackground], 
		resources[TextureID::LevelBarLevel], resources.font,
		experienceToNextLevel, currentExperience,
		sf::Vector2f(54.f, 3.f))
{
	value.setOrigin(0.f, 9.f);
	this->currentLevel.setFont(resources.font);
	this->currentLevel.setCharacterSize(50);
	this->currentLevel.setString(std::to_string(currentLevel));
	this->currentLevel.setPosition(position + sf::Vector2f(50 / 2 - this->currentLevel.getGlobalBounds().width / 2.f, -7.f));
	this->currentLevel.setOutlineColor(sf::Color::Black);
	this->currentLevel.setOutlineThickness(2);
}

LevelBar::~LevelBar()
{
}

void LevelBar::setCurrentLevel(const int Level)
{
	currentLevel.setString(std::to_string(Level));
}

void LevelBar::setPosition(const sf::Vector2f& Position)
{
	Bar::setPosition(Position);
	this->currentLevel.setPosition(Position + sf::Vector2f(50 / 2 - this->currentLevel.getGlobalBounds().width / 2.f, -7.f));
}

void LevelBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(bar, states);
	target.draw(value, states);
	target.draw(currentLevel, states);
}
