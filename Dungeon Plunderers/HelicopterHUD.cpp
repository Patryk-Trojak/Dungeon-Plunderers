#include "pch.h"
#include "HelicopterHUD.h"

HelicopterHUD::HelicopterHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    :StormtrooperHUD(HUDViewCenter, resources, currentPlayer, playerBaseVersion, playerData),
    helicopterHealthBar(HUDViewCenter + sf::Vector2f(-300.f, 415.f), resources[TextureID::HelicopterHealthBarBackground], resources[TextureID::HelicopterHealthBar], resources.font,
        currentPlayer->getInitialHp(), currentPlayer->getCurrentHp(),
        sf::Vector2f(57.f, 3.f), 25)
{

}

void HelicopterHUD::update()
{
    PlayerHUD::update();
}

void HelicopterHUD::updateHealthBars()
{
    helicopterHealthBar.setMaxValue(currentPlayer->getInitialHp());
    helicopterHealthBar.setValue(currentPlayer->getCurrentHp());

    const std::shared_ptr<Stormtrooper> stormtrooper = std::static_pointer_cast<Stormtrooper>(playerBaseVersion);
    healthBar.setMaxValue(stormtrooper->getInitialHp());
    healthBar.setValue(stormtrooper->getCurrentHp());
}

void HelicopterHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    StormtrooperHUD::draw(target, states);
    target.draw(helicopterHealthBar);
}
