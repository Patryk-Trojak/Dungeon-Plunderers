#include "pch.h"
#include "WizardOnCloudHUD.h"

WizardOnCloudHUD::WizardOnCloudHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    :WizardHUD(HUDViewCenter, resources,
        currentPlayer, playerBaseVersion, playerData)
{
    const std::shared_ptr<WizardOnCloud> wizard = std::static_pointer_cast<WizardOnCloud>(currentPlayer);
    healthBars.emplace_back(HUDViewCenter + sf::Vector2f(0.f, 400.f), resources, wizard->getInitialCloudHp(), wizard->getCloudHp());
    healthBars.emplace_back(HUDViewCenter + sf::Vector2f(350.f, 400.f), resources, wizard->getInitialShieldHp(), wizard->getShieldHp());
}

void WizardOnCloudHUD::updateHealthBars()
{
    PlayerHUD::updateHealthBars();
    const std::shared_ptr<WizardOnCloud> wizard = std::static_pointer_cast<WizardOnCloud>(currentPlayer);
    healthBars[1].setMaxValue(wizard->getInitialCloudHp());
    healthBars[1].setValue(wizard->getCloudHp());
    healthBars[2].setMaxValue(wizard->getInitialShieldHp());
    healthBars[2].setValue(wizard->getShieldHp());
}
