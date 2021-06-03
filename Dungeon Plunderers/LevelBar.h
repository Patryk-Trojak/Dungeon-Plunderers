#pragma once
#include <SFML/Graphics.hpp>
#include "Bar.h"
#include "Resources.h"

class LevelBar
	:public Bar
{
public:
	LevelBar(const sf::Vector2f& position, const Resources& resources,
		const int experienceToNextLevel, const int currentExperience, const int currentLevel);
	virtual ~LevelBar();
	void setCurrentLevel(const int Level);
private:
	sf::Text currentLevel;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

