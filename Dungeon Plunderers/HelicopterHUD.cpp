#include "pch.h"
#include "HelicopterHUD.h"

HelicopterHUD::HelicopterHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
    const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData)
    :StormtrooperHUD(HUDViewCenter, resources, currentPlayer, playerBaseVersion, playerData)
{

}

void HelicopterHUD::update()
{
    PlayerHUD::update();
}
