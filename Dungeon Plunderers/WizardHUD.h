#pragma once
#include "PlayerHUD.h"
#include "Resources.h"
#include "PotionBar.h"
#include "ManaBar.h"

class WizardHUD
    : public PlayerHUD
{
public:
    WizardHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
        const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData);
    void update() override;
protected:
    void updateManaBar();
    void updateManaPotionsBars();

    ManaBar manaBar;
    PotionBar manaPotionBar;


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
