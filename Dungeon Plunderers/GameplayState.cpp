#include "pch.h"
#include "GameplayState.h"

GameplayState::GameplayState(StateData& stateData, const std::function<Level(const Resources& resources)>& createCurrentLevel)
    :State(stateData),
    portal(level.endOfLevelPosition, stateData.resources[TextureID::Portal]),
    blocksDrawer(stateData.resources[TextureID::Blocks]),
    blocksHandler(level.blocks, movingBlocks, level.decorationBlocks),
    playerProjectilesHandler(projectiles),
    enemyProjectilesHandler(projectilesOfEnemies),
    bonusesHandler(bonuses, stateData.resources),
    effectsHandler(effects),
    enemiesHandler(level.enemies, projectilesOfEnemies),
    coinsHandler(level.coins),
    createCurrentLevel(createCurrentLevel),
    backgroundsHandler(backgrounds, stateData.resources),
    pause(stateData.resources),
    collisionsHandler(stateData.resources, level, currentPlayer, stateData.savedPlayerData, projectiles, projectilesOfEnemies, bonuses, effects, bonusesHandler),
    trampolinesHandler(level.trampolines)
{
    level = createCurrentLevel(stateData.resources);
    numberOfLevel = static_cast<int>(level.name);
    initPlayer(level.initialPositionOfPlayer);
    portal.setPosition(level.endOfLevelPosition);
    createHUD(currentPlayer->getType());
    backgroundsHandler.initBackgrounds(view.getCenter());
    initView();
    viewLeftPos = view.getCenter().x - view.getSize().x / 2.f;
    viewRightPos = view.getCenter().x + view.getSize().x / 2.f;
    enemiesHandler.setBlocksWhichEnemiesStandingOn(level.blocks, level.decorationBlocks);
    coinsHandler.setBlocksWhichCoinsStandingOn(level.blocks);
    trampolinesHandler.setBlocksWhichTrampolinesStandingOn(level.blocks);

    blocksDrawer.addBlocksToVertexArray(level.blocks, false);
    blocksDrawer.addBlocksToVertexArray(level.decorationBlocks, true);
    blocksHandler.initIteratorsToMovingBlocks();

    initCrosshair();

    exitGameplay =  [&numberOfStatesPop = numberOfStatesPop, &level = level, &movingBlocks = movingBlocks]()
    {
        numberOfStatesPop = 1;
        level.clear();
        movingBlocks.clear();
    };
}

GameplayState::~GameplayState()
{

}

void GameplayState::setNumberOfUpdatesWhileOneFrame(float deltaTime)
{
    if (deltaTime > 0.003f)
    {
        numberOfUpdates = deltaTime / 0.003f + 1;
    }
    else
    {
        numberOfUpdates = 1;
    }
}
void GameplayState::setNewDeltaTime(float deltaTime)
{
    newDeltaTime = deltaTime / numberOfUpdates;
}

void GameplayState::animateAllStuff(float deltaTime)
{
    currentPlayer->animate(deltaTime);
    currentPlayer->animateWeapon(deltaTime);
    playerProjectilesHandler.animateProjectiles(deltaTime);
    enemyProjectilesHandler.animateProjectiles(deltaTime);
    coinsHandler.animateCoins(deltaTime);
    trampolinesHandler.animateTrampolines(deltaTime);
    effectsHandler.animateEffects(deltaTime);
    enemiesHandler.animateEnemies(deltaTime);
    if (playerFormChanger)
    {
        playerFormChanger->animate(deltaTime);
    }
}


void GameplayState::update(const float deltaTime)
{
    crosshair.setPosition(mousePositionHUD);

    if (!pause.isActive())
    {
        setNumberOfUpdatesWhileOneFrame(deltaTime);
        setNewDeltaTime(deltaTime);
        enemiesHandler.setShouldUpdate(viewLeftPos, viewRightPos);
        currentPlayer->update(mousePositionView);
        animateAllStuff(deltaTime);
        handleChangingPlayerForm(deltaTime);
        if (playerFormChanger)
        {
            playerFormChanger->backToInitPosition(deltaTime);
        }

        for (int i = 0; i < numberOfUpdates; i++)
        {
            if (!infoAboutEnd)
            {
                currentPlayer->updateMove(newDeltaTime);
                currentPlayer->updateCurrentWeaponShootTimer(newDeltaTime);
                currentPlayer->attack(projectiles, mousePositionView);
                currentPlayer->calculateGlobalBoundsOfSprite();
            }
            tryTeleportToBoss();
            playerProjectilesHandler.eraseProjectilesDependingOnTheirDistanceMoved();
            playerProjectilesHandler.moveProjectiles(newDeltaTime);
            enemyProjectilesHandler.eraseProjectilesDependingOnTheirDistanceMoved();
            enemyProjectilesHandler.moveProjectiles(newDeltaTime);
            bonusesHandler.moveBonuses(newDeltaTime);
            collisionsHandler.PlayerAndBlock(newDeltaTime);

            currentPlayer->calculateGlobalBoundsOfSprite();
            blocksHandler.moveAllBlocks(newDeltaTime);
            enemiesHandler.updateEnemies(newDeltaTime, currentPlayer->getPosition());
            coinsHandler.moveCoinsWithBlocks(newDeltaTime);
            trampolinesHandler.moveTrampolinesWithBlocks(newDeltaTime);

            if (!isPlayerInBossArea)
                collisionsHandler.AllProjectilesAndBlock();

            collisionsHandler.PlayerAndEnemyProjectiles();

            collisionsHandler.PlayerAndEnemies(newDeltaTime);
            collisionsHandler.PlayerAndBonuses();
            collisionsHandler.PlayerAndTrampolines();
            collisionsHandler.ProjectilesAndEnemies();
            collisionsHandler.PlayerAndCoins();
            collisionsHandler.BonusesAndBlocks(newDeltaTime);
            updatePlayerLevel();
        }
        updatePositionOfView();
        backgroundsHandler.updatePositionsOfBackgrounds(currentPlayer->getPosition().x);
        playerHUD->update();

        viewLeftPos = view.getCenter().x - view.getSize().x / 2.f;
        viewRightPos = view.getCenter().x + view.getSize().x / 2.f;
        effectsHandler.deleteEffectIfIsOver();

 
        enemiesHandler.updateHealthBarEnemies();

        if (infoAboutEnd)
        {
            infoAboutEnd->update(mousePositionHUD);
            handleWithInfoAboutEndOfLevel();
        }
        else
        {
            endLevelIfPlayerHasWon();
            endLevelIfPlayerHasLost();
        }
        blocksDrawer.updatePositionsOfMovingBlocksVertex(movingBlocks);
    }

    pause.updatePauseMessagebox(mousePositionHUD);
    pause.handleButtonsOfMessagebox(mousePositionHUD, wasMousePressed, exitGameplay);

}

void GameplayState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    
    backgroundsHandler.drawBackgrounds(target);
    bonusesHandler.drawBonuses(target, viewRightPos, viewLeftPos);


    if (!isPlayerInBossArea)
        target.draw(portal);
    coinsHandler.drawCoins(target, viewRightPos, viewLeftPos);
    trampolinesHandler.drawTrampolines(target, viewRightPos, viewLeftPos);
    target.draw(blocksDrawer);
    playerProjectilesHandler.drawProjectiles(target, viewRightPos, viewLeftPos);
    enemyProjectilesHandler.drawProjectiles(target, viewRightPos, viewLeftPos);
    if (!infoAboutEnd)
        target.draw(*currentPlayer);
    enemiesHandler.drawEnemies(target, viewRightPos, viewLeftPos);
    if (playerFormChanger)
        target.draw(*playerFormChanger);
    effectsHandler.drawEffects(target);

    target.setView(HUDView);
    target.draw(*playerHUD);
    if (infoAboutEnd)
        target.draw(*infoAboutEnd);

    target.draw(pause);

    target.draw(crosshair);
    target.setView(view);
}

void GameplayState::initView()
{
    view.setSize(2666.666, 1500);
    view.setCenter(currentPlayer->getPosition().x, view.getCenter().y);
}


void GameplayState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
    wasMousePressed = false;
    wasEscapePressed = false;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        resizeWindowProportionally(window, event);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                wasMousePressed = true;
            }

        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                wasEscapePressed = true;
                if (pause.isActive())
                {
                    pause.resume();
                }
                else if (!infoAboutEnd)
                    pause.create(HUDView.getCenter());
            }
        }
    }
}

void GameplayState::updateInput(const float deltaTime)
{
}


void GameplayState::handleChangingPlayerForm(const float deltaTime)
{
    timeSinceChangePlayerForm += deltaTime;
    handleChanginFormFromNormalToBossVersion();
    handleChanginFormFromBossToNormalVersion();
}

void GameplayState::clearAllGameStuff()
{
    level.clear();
    movingBlocks.clear();
    blocksDrawer.clearBlocks();
    projectiles.clear();
    projectilesOfEnemies.clear();
    effects.clear();
    playerFormChanger.reset();
}

void GameplayState::tryTeleportToBoss()
{
    if (!isPlayerInBossArea and currentPlayer->hitboxComponent.intersects(portal.hitboxes))
    {
        if (level.name != LevelName::playerLevel)
        {
            clearAllGameStuff();
            level.blocks = DefaultLevelMaker::makeBossArea();
            level.enemies.emplace_back(DefaultLevelMaker::createBoss(level.name, currentPlayer->getType(), stateData.resources));
            blocksDrawer.addBlocksToVertexArray(level.blocks, false);
            blocksDrawer.addBlocksToVertexArray(level.decorationBlocks, true);
            currentPlayer->setPositionRelativeToHitbox(sf::Vector2f(1000.f, -260.f));
            makePlayerFormChanger();
            isPlayerInBossArea = true;
            addaptViewToBossFight();
            addaptBackgroundToBossFight();     
        }
    }
}

void GameplayState::updatePlayerLevel()
{
    if (stateData.savedPlayerData.experienceOfPlayer >= stateData.savedPlayerData.levelOfPlayer * 1500)
    {
        stateData.savedPlayerData.levelOfPlayer +=  1;
        stateData.savedPlayerData.experienceOfPlayer = 0;
    }
}

void GameplayState::handleWithInfoAboutEndOfLevel()
{
    if (infoAboutEnd)
    {
        if (infoAboutEnd->FirstOptionWasPressed(mousePositionHUD, wasMousePressed))
        {
            clearAllGameStuff();
            if (isBossKilled)
            {
                createCurrentLevel = DefaultLevelMaker::makeFunctionCreatingNextDefaultLevel(level.name);
                level = createCurrentLevel(stateData.resources);
            }
            else
            {
                resetCurrentLevel();
            }
            isBossKilled = false;
            isPlayerInBossArea = false;
            initPlayer(level.initialPositionOfPlayer);
            createHUD(currentPlayer->getType());
            backgroundsHandler.initBackgrounds(currentPlayer->getPosition());
            enemiesHandler.setBlocksWhichEnemiesStandingOn(level.blocks, level.decorationBlocks);
            coinsHandler.setBlocksWhichCoinsStandingOn(level.blocks);
            trampolinesHandler.setBlocksWhichTrampolinesStandingOn(level.blocks);
            initView();

            blocksHandler.initIteratorsToMovingBlocks();
            blocksDrawer.addBlocksToVertexArray(level.blocks, false);
            blocksDrawer.addBlocksToVertexArray(level.decorationBlocks, true);
            infoAboutEnd.reset();
            //reset player hp etc
        }
        else if (infoAboutEnd->SecondOptionWasPressed(mousePositionHUD, wasMousePressed))
        {
            exitState();
        }
    }
}


void GameplayState::initPlayer(const sf::Vector2f& positionOfPlayer)
{

    if (stateData.savedPlayerData.isStormtrooperChosen)
    {
        playerNormalVersion = std::make_shared<Stormtrooper>(positionOfPlayer,
            stateData.keybinds, stateData.resources, stateData.savedPlayerData);

       playerBossVersion = std::make_shared<Helicopter>(positionOfPlayer,
            stateData.keybinds, stateData.resources, stateData.savedPlayerData);

    }
    else
    {
        playerNormalVersion = std::make_shared<Wizard>(positionOfPlayer,
            stateData.keybinds, stateData.resources, stateData.savedPlayerData);
        playerBossVersion = std::make_shared<WizardOnCloud>(positionOfPlayer,
            stateData.keybinds, stateData.resources, stateData.savedPlayerData);
    }
    currentPlayer = playerNormalVersion;
    currentPlayer->setPositionRelativeToHitbox(positionOfPlayer);
}

void GameplayState::createHUD(PlayerType playerType)
{
    switch (playerType)
    {
    case PlayerType::stormtrooper:
        playerHUD = std::make_unique<StormtrooperHUD>(HUDView.getCenter(), stateData.resources, currentPlayer, playerNormalVersion, stateData.savedPlayerData);
            break;
    case PlayerType::wizard:
        playerHUD = std::make_unique<WizardHUD>(HUDView.getCenter(), stateData.resources, currentPlayer, playerNormalVersion, stateData.savedPlayerData);
        break;
    case PlayerType::helicopter:
        playerHUD = std::make_unique<HelicopterHUD>(HUDView.getCenter(), stateData.resources, currentPlayer, playerNormalVersion, stateData.savedPlayerData);
        break;
    case PlayerType::wizardOnCloud:
        playerHUD = std::make_unique<WizardOnCloudHUD>(HUDView.getCenter(), stateData.resources, currentPlayer, playerNormalVersion, stateData.savedPlayerData);
        break;
    }
}

std::wstring GameplayState::makeStringAboutWin()
{
    return L"Gratulacje! Uda³o ci siê przejœæ poziom " + std::to_wstring(static_cast<int>(level.name))
            + L"!\nZyska³eœ " + std::to_wstring(collectedMoneyOnLevel) + L" pieniêdzy"
             L"\nObecnie masz" + std::to_wstring(stateData.savedPlayerData.money) + L" pieniêdzy";
}

void GameplayState::exitState()
{
    numberOfStatesPop = 1;
    level.clear(); 
    movingBlocks.clear();
}

void GameplayState::initCrosshair()
{
    crosshair.setTexture(stateData.resources[TextureID::Crosshair]);
    crosshair.setOrigin(23.f / 2.f, 23.f / 2.f);
}


void GameplayState::resetCurrentLevel()
{
    clearAllGameStuff();
    level = createCurrentLevel(stateData.resources);
}

bool GameplayState::hasPlayerLost()
{
    if (isPlayerCrushedByBlocks())
        return true;

    if (hasPlayer0Hp())
        return true;

    if (isPlayerUnderMap())
        return true;

    return false;
}
bool GameplayState::isPlayerCrushedByBlocks()
{
    if ((!currentPlayer->isAbleToFall and !currentPlayer->isAbleToMoveUp)
        or (!currentPlayer->isAbleToMoveRight and !currentPlayer->isAbleToMoveLeft))
        return true;

    return false;
}

bool GameplayState::hasPlayer0Hp()
{
    if (currentPlayer->getType() != PlayerType::helicopter)
    {
        if (currentPlayer->getCurrentHp() == 0)
        {
            return true;
        }
    }

    return false;
}
bool GameplayState::isPlayerUnderMap()
{
    if (currentPlayer->getPosition().y > 2700)
    {
        return true;
    }

    return false;
}

void GameplayState::endLevelIfPlayerHasLost()
{
    if (hasPlayerLost())
    {
        makeMessageBoxAboutLose();
        collectedMoneyOnLevel = 0;
    }
}

void GameplayState::endLevelIfPlayerHasWon()
{
    if (hasPlayerWon())
    {
        stateData.savedPlayerData.money += currentPlayer->collectedMoney;
        if (static_cast<int>(level.name) == stateData.savedPlayerData.numberOfUnlockedLevels)
        {
            stateData.savedPlayerData.numberOfUnlockedLevels++;
        }
        isBossKilled = true;
        makeMessageBoxAboutWin();
        collectedMoneyOnLevel = 0;
        PersistenceSaver::save(stateData.savedPlayerData, stateData.nameOfCurrentlyLoadedPlayerSave);
    }
}

std::wstring GameplayState::makeWstringAboutWin()
{
    std::wstring message = L"Gratulacje! Uda³o ci siê ukoñczyæ poziom";
    if (level.name != LevelName::playerLevel)
    {
        message += L" " + std::to_wstring(numberOfLevel) + L"!\nZyska³eœ " + std::to_wstring(collectedMoneyOnLevel) + L" pieniêdzy"
            L"\nObecnie masz " + std::to_wstring(stateData.savedPlayerData.money) + L" pieniêdzy";
    }
    return message;
}

void GameplayState::makeMessageBoxAboutWin()
{
    infoAboutEnd = std::make_unique<game::MessageBox>(HUDView.getCenter(), sf::Vector2f(885, 300), sf::Vector2f(100, 55),
        stateData.resources[TextureID::MessageboxBackground], stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
        makeWstringAboutWin(),
        L"PrzejdŸ do nastêpnego poziomu", L"Wróæ do menu");
}

void GameplayState::makeMessageBoxAboutLose()
{
    infoAboutEnd = std::make_unique<game::MessageBox>(HUDView.getCenter(), sf::Vector2f(685, 200), sf::Vector2f(100, 55),
        stateData.resources[TextureID::MessageboxBackground], stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
        L"Umar³eœ!", L"Od nowa", L"Wróæ do menu");
}


bool GameplayState::hasPlayerWon()
{
    if (isPlayerInBossArea and level.enemies.empty())
    {
        return true;
    }

    
    if (level.name == LevelName::playerLevel)
    {
        if (currentPlayer->hitboxComponent.intersects(portal.hitboxes))
            return true;
    }

    return false;
}

void GameplayState::updatePositionOfView()
{
    if (!isPlayerInBossArea)
    {
        view.setCenter(currentPlayer->getPosition().x, view.getCenter().y);
    }
}


void GameplayState::addaptViewToBossFight()
{
    view.setSize(sf::Vector2f(3288.88888888888f, 1850.f));
    view.setCenter(2000.f, view.getCenter().y);
}
void GameplayState::addaptBackgroundToBossFight()
{
    backgrounds[0].setTextureRect(sf::IntRect(0, 0, 3500, 2000));
    backgrounds[0].setPosition(200, -500);
    backgrounds[1].setPosition(-5000, -400);
}

void GameplayState::makePlayerFormChanger()
{
    if (currentPlayer->getType() == PlayerType::stormtrooper)
        playerFormChanger = std::make_unique<PlayerFormChanger>(sf::Vector2f(400.f, 1273.f), sf::Vector2f(400.f, 1273.f), stateData.resources, WaysToChangePlayerForm::StormtrooperToHelicopter);
    else
        playerFormChanger = std::make_unique<PlayerFormChanger>(sf::Vector2f(400.f, 1273.f), sf::Vector2f(400.f, 1273.f), stateData.resources, WaysToChangePlayerForm::WizardToWizardOnCloud);
}

void GameplayState::handleChanginFormFromNormalToBossVersion()
{
    if (playerFormChanger and timeSinceChangePlayerForm > 1.f)
    {
        if (currentPlayer->getGlobalBoundsOfSprite().intersects(playerFormChanger->getGlobalBoundsOfSprite()))
        {
            if (currentPlayer->hitboxComponent.intersects(playerFormChanger->hitboxes))
            {
                currentPlayer = playerBossVersion;
                if (currentPlayer->getType() == PlayerType::helicopter)
                {
                    currentPlayer->setPosition(playerFormChanger->getPosition());
                }
                else
                {
                    currentPlayer->setPosition(playerFormChanger->getPosition() - sf::Vector2f(-70.f, 175.f));
                    currentPlayer->setValue(playerNormalVersion->getCurrentHp());
                    currentPlayer->setInitialHp(playerNormalVersion->getInitialHp());
                }
                createHUD(currentPlayer->getType());
                playerFormChanger.reset();
                timeSinceChangePlayerForm = 0.f;
            } 
        }
    }
}
void GameplayState::handleChanginFormFromBossToNormalVersion()
{
    if (currentPlayer == playerBossVersion)
    {
        if (stateData.keybinds.isPressed(KeybindID::GetOffPlaneOrCloud))
        {
            changeFormFromBossToNormalVersion(true);
        }
        else
        {
            if (currentPlayer->getType() == PlayerType::wizardOnCloud)
            {
                if (std::static_pointer_cast<WizardOnCloud>(currentPlayer)->getCloudHp() <= 0)
                    changeFormFromBossToNormalVersion(false);
            }
            else
            {
                if (currentPlayer->getCurrentHp() <= 0)
                    changeFormFromBossToNormalVersion(false);
            }
        }
    }
}

void GameplayState::changeFormFromBossToNormalVersion(bool createFormChanger)
{
    currentPlayer = playerNormalVersion;

    if (currentPlayer->getType() == PlayerType::stormtrooper)
    {
        currentPlayer->setPosition(currentPlayer->getPosition() + sf::Vector2f(320.f, 0.f));
    }
    else
    {
        currentPlayer->setPosition(currentPlayer->getPosition());
        currentPlayer->setValue(playerBossVersion->getCurrentHp());
        currentPlayer->setInitialHp(playerBossVersion->getInitialHp());
    }
    createHUD(currentPlayer->getType());
    if(createFormChanger)
        makePlayerFormChanger();
    timeSinceChangePlayerForm = 0.f;
}