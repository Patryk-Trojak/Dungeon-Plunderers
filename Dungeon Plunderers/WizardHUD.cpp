#include "pch.h"
#include "WizardHUD.h"

WizardHUD::WizardHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources, 
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    : PlayerHUD(HUDViewCenter, resources,
        currentPlayer, playerBaseVersion, playerData),
    manaBar(HUDViewCenter + sf::Vector2f(-550.f, 400.f), resources, 0, 0),
    manaPotionBar(HUDViewCenter + sf::Vector2f(0.f, 436.f), resources[TextureID::PotionBar], resources[TextureID::ManaPotion], 0)
{
}

void WizardHUD::update()
{
    PlayerHUD::update();
    updateManaBar();
    updateManaPotionsBars();
}

void WizardHUD::updateManaBar()
{
    const std::shared_ptr<Wizard> wizard = std::static_pointer_cast<Wizard>(playerBaseVersion);
    manaBar.setMaxValue(wizard->getInitialMana());
    manaBar.setValue(wizard->getMana());
}

void WizardHUD::updateManaPotionsBars()
{
    const std::shared_ptr<Wizard> wizard = std::static_pointer_cast<Wizard>(playerBaseVersion);
    manaPotionBar.setCurrentNumberOfPotion(wizard->getCurrentNumberOfManaPotions());
}

void WizardHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    PlayerHUD::draw(target, states);
    target.draw(manaPotionBar);
    target.draw(manaBar);
}