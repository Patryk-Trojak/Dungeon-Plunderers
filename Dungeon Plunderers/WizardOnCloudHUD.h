#pragma once
#include "WizardHUD.h"
#include "Resources.h"
#include "PotionBar.h"
#include "ManaBar.h"
#include "WizardOnCloud.h"

class WizardOnCloudHUD
    :public WizardHUD
{
public:
    WizardOnCloudHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
        const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData);
private:
    void updateHealthBars();
    Bar shieldHealthBar;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

