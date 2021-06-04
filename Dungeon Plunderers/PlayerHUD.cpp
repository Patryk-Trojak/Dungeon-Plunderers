#include "pch.h"
#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    :    levelBar(HUDViewCenter + sf::Vector2f(-550.f, 445.f), resources, StatsPlayerCreator::getExpierienceToNextLevel(playerData.experienceOfPlayer), playerData.experienceOfPlayer, playerData.levelOfPlayer),
    moneyHUD(HUDViewCenter + sf::Vector2f(350.f, 445.f), resources, playerData.money + currentPlayer->collectedMoney),
    healthPotionsBar(HUDViewCenter + sf::Vector2f(-50, 445.f), resources[TextureID::PotionBar], resources[TextureID::HealthPotion], 3),
    currentPlayer(currentPlayer),
    playerBaseVersion(playerBaseVersion),
    playerData(playerData)
{
    healthBars.emplace_back(HUDViewCenter + sf::Vector2f(-300.f, 445.f), resources, currentPlayer->getInitialHp(), currentPlayer->getCurrentHp());
}

PlayerHUD::~PlayerHUD()
{
}

void PlayerHUD::update()
{
    updateHealthBars();
    updateLevelBar();
    updateMoneyHUD();
    updateHealthPotionsBar();
}

void PlayerHUD::updateHealthBars()
{
    healthBars[0].setMaxValue(currentPlayer->getInitialHp());
    healthBars[0].setValue(currentPlayer->getCurrentHp());
}

void PlayerHUD::updateMoneyHUD()
{
    moneyHUD.setMoney(playerData.money + currentPlayer->collectedMoney);
}

void PlayerHUD::updateLevelBar()
{
    levelBar.setCurrentLevel(playerData.levelOfPlayer);
    levelBar.setMaxValue(StatsPlayerCreator::getExpierienceToNextLevel(playerData.levelOfPlayer));
    levelBar.setValue(playerData.experienceOfPlayer);
}

void PlayerHUD::updateHealthPotionsBar()
{
    if (playerBaseVersion->getType() == PlayerType::stormtrooper)
    {
        const std::shared_ptr<Stormtrooper> stormtroper = std::static_pointer_cast<Stormtrooper>(playerBaseVersion);
        healthPotionsBar.setCurrentNumberOfPotion(stormtroper->getCurrentNumberOfHealthPotions());
    }
    else if (playerBaseVersion->getType() == PlayerType::wizard)
    {
        const std::shared_ptr<Wizard> wizard = std::static_pointer_cast<Wizard>(playerBaseVersion);
        healthPotionsBar.setCurrentNumberOfPotion(wizard->getCurrentNumberOfHealthPotions());
    }
}

void PlayerHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(healthPotionsBar);
    target.draw(levelBar);
    target.draw(moneyHUD);
    target.draw(healthPotionsBar);
    for(auto const& i : healthBars)
        target.draw(i);
}
