#include "pch.h"
#include "WizardOnCloudHUD.h"

WizardOnCloudHUD::WizardOnCloudHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    :WizardHUD(HUDViewCenter, resources,
        currentPlayer, playerBaseVersion, playerData)
{
    const std::shared_ptr<WizardOnCloud> wizard = std::static_pointer_cast<WizardOnCloud>(currentPlayer);

}

void WizardOnCloudHUD::updateHealthBars()
{
    PlayerHUD::updateHealthBars();
    const std::shared_ptr<WizardOnCloud> wizard = std::static_pointer_cast<WizardOnCloud>(currentPlayer);
}
