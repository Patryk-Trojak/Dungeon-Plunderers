#include "pch.h"
#include "BonusesHandler.h"



BonusesHandler::BonusesHandler(std::vector<Bonus>& bonuses, const Resources& resources)
	:bonuses(bonuses),
	resources(resources)
{
}

void BonusesHandler::tryAddBonus(const sf::Vector2f& positionOfBonus, const PlayerType& name)
{
	if (name == PlayerType::stormtrooper)
	{
		tryAddBonusForStormtrooper(positionOfBonus);
	}
	else if (name == PlayerType::wizard)
	{
		tryAddBonusForWizard(positionOfBonus);
	}
}

void BonusesHandler::moveBonuses(const float deltaTime)
{
	for (auto& i : bonuses)
		i.move(deltaTime);
}

void BonusesHandler::drawBonuses(sf::RenderTarget& target, float viewRightPos, float viewLeftPos) const
{
	for (auto const& i : bonuses)
	{
		if (i.getGlobalBoundsOfSprite().left < viewRightPos and i.getGlobalBoundsOfSprite().left + i.getGlobalBoundsOfSprite().width > viewLeftPos)
			target.draw(i);
	}
}

void BonusesHandler::tryAddBonusForStormtrooper(const sf::Vector2f& positionOfBonus)
{
	switch (RandomEngine::randInt(1, 15))
	{
	case 1:
		bonuses.emplace_back(positionOfBonus, resources[TextureID::RifleAmmoBox], BonusesTypes::rifleAmmoBox);
		break;
	case 2:
		bonuses.emplace_back(positionOfBonus, resources[TextureID::RifleAmmoBox], BonusesTypes::shotgunAmmoBox);
		break;
	case 3:
		bonuses.emplace_back(positionOfBonus, resources[TextureID::HealthPotion], BonusesTypes::healthPotion);
		break;
	}
}

void BonusesHandler::tryAddBonusForWizard(const sf::Vector2f& positionOfBonus)
{
	switch (RandomEngine::randInt(1, 15))
	{
	case 1:
		bonuses.emplace_back(positionOfBonus, resources[TextureID::HealthPotion], BonusesTypes::healthPotion);
		break;
	case 2:
		bonuses.emplace_back(positionOfBonus, resources[TextureID::ManaPotion], BonusesTypes::manaPotion);
		break;
	}
}
