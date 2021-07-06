#include "pch.h"
#include "WizardOnCloudHUD.h"

WizardOnCloudHUD::WizardOnCloudHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    :WizardHUD(HUDViewCenter, resources,
        currentPlayer, playerBaseVersion, playerData),
    shieldHealthBar(HUDViewCenter + sf::Vector2f(-425.f, 445.f - 30.f), resources[TextureID::ShieldHealthBarBackground], resources[TextureID::ShieldHealthBar], resources.font,
        std::static_pointer_cast<WizardOnCloud>(currentPlayer)->getInitialShieldHp(), std::static_pointer_cast<WizardOnCloud>(currentPlayer)->getShieldHp(), 
        sf::Vector2f(33.f, 3.f), 25)
{
}

void WizardOnCloudHUD::updateHealthBars()
{
    PlayerHUD::updateHealthBars();
    const std::shared_ptr<WizardOnCloud> wizard = std::static_pointer_cast<WizardOnCloud>(currentPlayer);
    shieldHealthBar.setValue(wizard->getShieldHp());
    shieldHealthBar.setMaxValue(wizard->getInitialShieldHp());
}

void WizardOnCloudHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    WizardHUD::draw(target, states);
    target.draw(shieldHealthBar);
}
