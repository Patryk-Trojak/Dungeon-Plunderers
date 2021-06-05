#pragma once
#include <memory>
#include <random>
#include <thread>
#include <future>
#include <list>
#include "State.h"
#include "Player.h"
#include "Wizard.h"
#include "Stormtrooper.h"
#include "Coin.h"
#include "Enemy.h"
#include "AmmoHUD.h"
#include "MoneyHUD.h"
#include "PotionBar.h"
#include "Helicopter.h"
#include "Bonus.h"
#include "LevelBar.h"
#include "ManaBar.h"
#include "WizardOnCloud.h"
#include "PlayerFormChanger.h"
#include "GunEnemy.h"
#include "DeadlyFlowerBoss.h"
#include "Portal.h"
#include "MessageBox.h"
#include "SkeletonBoss.h"
#include "ZombieBoss.h"
#include "PlayerHealthBar.h"
#include "RandomEngine.h"
#include "CollisionsHandler.h"
#include "BlocksDrawer.h"
#include "BlocksHandler.h"
#include "ProjectilesHandler.h"
#include "BonusesHandler.h"
#include "BackgroundHandler.h"
#include "EnemiesHandler.h"
#include "CoinsHandler.h"
#include "EffectsHandler.h"
#include "PlayerHUD.h"
#include "StormtrooperHUD.h"
#include "WizardHUD.h"
#include "WizardOnCloudHUD.h"
#include "HelicopterHUD.h"
#include "EffectsHandler.h"
#include "Pause.h"
#include "DefaultLevelMaker.h"
#include "LevelName.h"


class Player;



class GameplayState
    :public State
{
public:
    GameplayState(StateData& stateData, const std::function<Level(const Resources & resources)>& createCurrentLevel);
    virtual ~GameplayState();
    virtual void update(const float deltaTime) override;
    virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;

private:
    std::shared_ptr<Player> currentPlayer;
    std::shared_ptr<Player> playerNormalVersion; 
    std::shared_ptr<Player> playerBossVersion;   

    Level level;
    int numberOfLevel;
    BlocksHandler blocksHandler;
    EnemiesHandler enemiesHandler;
    CoinsHandler coinsHandler;
    std::vector<std::vector<Block>::const_iterator> movingBlocks;
    BlocksDrawer blocksDrawer;

    std::vector< std::unique_ptr< PlayerProjectile > > projectiles;
    std::vector< std::unique_ptr< EnemyProjectile > > projectilesOfEnemies;
    ProjectilesHandler<PlayerProjectile> playerProjectilesHandler;
    ProjectilesHandler<EnemyProjectile> enemyProjectilesHandler;

    std::array<sf::Sprite, 2> backgrounds;
    BackgroundHandler backgroundsHandler;
    std::vector<Bonus> bonuses;
    BonusesHandler bonusesHandler;
    std::vector<std::unique_ptr< Effect > > effects;
    EffectsHandler effectsHandler;

    CollisionsHandler collisionsHandler;

    void initView();
    void updatePositionOfView();
    std::unique_ptr<PlayerHUD> playerHUD;
    void createHUD(PlayerType playerType);


    virtual void updateInput(const float deltaTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    int collectedMoneyOnLevel;
    bool wasEscapePressed{ false };

    void animateAllStuff(float deltaTime);

    float newDeltaTime;
    int numberOfUpdates;
    void setNumberOfUpdatesWhileOneFrame(float deltaTime);
    void setNewDeltaTime(float deltaTime);

    std::unique_ptr<PlayerFormChanger> playerFormChanger;
    void handleChangingPlayerForm(const float deltaTime);
    float timeSinceChangePlayerForm{ 0 };

    void updatePlayerLevel();
    float viewLeftPos;
    float viewRightPos;

    Portal portal;
    void tryTeleportToBoss();
    bool isPlayerInBossArea{ false };
    bool isBossKilled{ false };
    std::unique_ptr<game::MessageBox> infoAboutEnd;
    void handleWithInfoAboutEndOfLevel();

    void initPlayer(const sf::Vector2f& positionOfPlayer);

    Pause pause;
    std::wstring makeStringAboutWin();
    
    void exitState();
    std::function<void()> exitGameplay;

    sf::Sprite crosshair;
    void initCrosshair();

    void clearAllGameStuff();
    std::function<Level(const Resources& resources)> createCurrentLevel;
    void resetCurrentLevel();
   

    void endLevelIfPlayerHasLost();
    void endLevelIfPlayerHasWon();
    std::wstring makeWstringAboutWin();
    void makeMessageBoxAboutWin();
    void makeMessageBoxAboutLose();
    bool hasPlayerLost();
    bool hasPlayerWon();

    bool isPlayerCrushedByBlocks();
    bool hasPlayer0Hp();
    bool isPlayerUnderMap();



    void addaptViewToBossFight();
    void addaptBackgroundToBossFight();
    void makePlayerFormChanger();

    void handleChanginFormFromNormalToBossVersion();
    void handleChanginFormFromBossToNormalVersion();
};
