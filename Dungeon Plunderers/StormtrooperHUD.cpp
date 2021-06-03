#include "pch.h"
#include "StormtrooperHUD.h"


StormtrooperHUD::StormtrooperHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources, 
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    :PlayerHUD(HUDViewCenter, resources,
        currentPlayer, playerBaseVersion, playerData),
    ammo(HUDViewCenter + sf::Vector2f(400.f, 445.f), resources, "Nieskonczonosc")
{

}

void StormtrooperHUD::update()
{
    PlayerHUD::update();
    updateAmmo();
}

void StormtrooperHUD::updateAmmo()
{
    const std::shared_ptr<Stormtrooper> stormtroper = std::static_pointer_cast<Stormtrooper>(playerBaseVersion);
    ammo.setCurrentAmmo(stormtroper->getAmmo());
}

void StormtrooperHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    PlayerHUD::draw(target, states);
    target.draw(ammo);
}
