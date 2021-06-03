#pragma once
#include "PlayerHUD.h"
#include "Resources.h"
#include "AmmoHUD.h"
#include "PotionBar.h"

class StormtrooperHUD
    : public PlayerHUD
{
public:
    StormtrooperHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
        const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData);

    void update() override;

protected:
    void updateAmmo();
    AmmoHUD ammo;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

