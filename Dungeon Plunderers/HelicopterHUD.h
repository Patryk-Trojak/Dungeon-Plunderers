#pragma once
#include "StormtrooperHUD.h"
#include "Resources.h"
#include "PotionBar.h"

class HelicopterHUD
    : public StormtrooperHUD
{
public:
    HelicopterHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
        const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData);

    void update() override;

private:
    Bar helicopterHealthBar;
    void updateHealthBars();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};





