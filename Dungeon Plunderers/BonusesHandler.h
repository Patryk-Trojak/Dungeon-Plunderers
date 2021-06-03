#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Bonus.h"
#include "Player.h"
#include "RandomEngine.h"
#include"Resources.h"

class BonusesHandler
{
public:
	BonusesHandler(std::vector<Bonus>& bonuses, const Resources& resources);
	void tryAddBonus(const sf::Vector2f& positionOfBonus, const PlayerType& name);
	void moveBonuses(const float deltaTime);
	void drawBonuses(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const;
private:
	void tryAddBonusForStormtrooper(const sf::Vector2f& positionOfBonus);
	void tryAddBonusForWizard(const sf::Vector2f& positionOfBonus);
	std::vector<Bonus>& bonuses;
	const Resources& resources;
};

