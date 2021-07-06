#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "PlayerHealthBar.h"
#include "MoneyHUD.h"
#include "LevelBar.h"
#include "PotionBar.h"
#include "Player.h"
#include "StatsPlayerCreator.h"
#include "Stormtrooper.h"
#include "Wizard.h"


class PlayerHUD 
    : public sf::Drawable
{
public:
    PlayerHUD(const sf::Vector2f& HUDViewCenter, const Resources& resources,
        const std::shared_ptr<Player>& currentPlayer, const std::shared_ptr<Player>& playerBaseVersion, const PlayerData& playerData);

    virtual ~PlayerHUD();
    virtual void update();
protected:
    virtual void updateHealthBars();
    void updateMoneyHUD();
    void updateLevelBar();
    void updateHealthPotionsBar();

    PlayerHealthBar healthBar;
    MoneyHUD moneyHUD;
    LevelBar levelBar;
    PotionBar healthPotionsBar;

    const std::shared_ptr<Player>& currentPlayer;
    const std::shared_ptr<Player>& playerBaseVersion;
    const PlayerData& playerData;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
