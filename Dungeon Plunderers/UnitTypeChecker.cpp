#include "pch.h"
#include "UnitTypeChecker.h"

const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> UnitTypeChecker::blocks = [] {
    std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> blocks;
    blocks.fill(false);
    
    blocks[static_cast<int>(LevelEditorUnitsNames::brick)] = true;
    blocks[static_cast<int>(LevelEditorUnitsNames::dirt)] = true;
    blocks[static_cast<int>(LevelEditorUnitsNames::concrete)] = true;
    blocks[static_cast<int>(LevelEditorUnitsNames::granite)] = true;

    blocks[static_cast<int>(LevelEditorUnitsNames::movingBrick)] = true;
    blocks[static_cast<int>(LevelEditorUnitsNames::movingDirt)] = true;
    blocks[static_cast<int>(LevelEditorUnitsNames::movingConcrete)] = true;
    blocks[static_cast<int>(LevelEditorUnitsNames::movingGranite)] = true;

    return blocks;
}();

const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> UnitTypeChecker::enemies = [] {
    std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> enemies;
    enemies.fill(false);

    enemies[static_cast<int>(LevelEditorUnitsNames::deadlyFlower)] = true;
    enemies[static_cast<int>(LevelEditorUnitsNames::spikes)] = true;
    enemies[static_cast<int>(LevelEditorUnitsNames::hidingSpikes)] = true;
    enemies[static_cast<int>(LevelEditorUnitsNames::showingAfterDamageSpikes)] = true;

    enemies[static_cast<int>(LevelEditorUnitsNames::gunEnemy)] = true;
    enemies[static_cast<int>(LevelEditorUnitsNames::zombie)] = true;
    enemies[static_cast<int>(LevelEditorUnitsNames::skeleton)] = true;
    enemies[static_cast<int>(LevelEditorUnitsNames::gunEnemyOnFakeBlock)] = true;

    enemies[static_cast<int>(LevelEditorUnitsNames::fly)] = true;
    enemies[static_cast<int>(LevelEditorUnitsNames::movingGunEnemyOnFakeBlock)] = true;

    return enemies;
}();

const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> UnitTypeChecker::moving = [] {
    std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> moving;
    moving.fill(false);

    moving[static_cast<int>(LevelEditorUnitsNames::movingBrick)] = true;
    moving[static_cast<int>(LevelEditorUnitsNames::movingDirt)] = true;
    moving[static_cast<int>(LevelEditorUnitsNames::movingConcrete)] = true;
    moving[static_cast<int>(LevelEditorUnitsNames::movingGranite)] = true;

    moving[static_cast<int>(LevelEditorUnitsNames::zombie)] = true;
    moving[static_cast<int>(LevelEditorUnitsNames::skeleton)] = true;
    moving[static_cast<int>(LevelEditorUnitsNames::fly)] = true;
    moving[static_cast<int>(LevelEditorUnitsNames::movingGunEnemyOnFakeBlock)] = true;



    return moving;
}();

const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> UnitTypeChecker::ground = [] {
    std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> ground;
    ground.fill(false);

    ground[static_cast<int>(LevelEditorUnitsNames::deadlyFlower)] = true;
    ground[static_cast<int>(LevelEditorUnitsNames::spikes)] = true;
    ground[static_cast<int>(LevelEditorUnitsNames::hidingSpikes)] = true;
    ground[static_cast<int>(LevelEditorUnitsNames::showingAfterDamageSpikes)] = true;

    ground[static_cast<int>(LevelEditorUnitsNames::gunEnemy)] = true;
    ground[static_cast<int>(LevelEditorUnitsNames::zombie)] = true;
    ground[static_cast<int>(LevelEditorUnitsNames::skeleton)] = true;

    return ground;
}();

const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> UnitTypeChecker::coins = [] {
    std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> blocks;
    blocks.fill(false);

    blocks[static_cast<int>(LevelEditorUnitsNames::coin)] = true;

    return blocks;
}();


bool UnitTypeChecker::isGround(LevelEditorUnitsNames name)
{
    return ground[static_cast<int>(name)];
}

bool UnitTypeChecker::isMovingEnemy(LevelEditorUnitsNames name)
{
    if (enemies[static_cast<int>(name)] and moving[static_cast<int>(name)])
        return true;

    return false;
}

bool UnitTypeChecker::isMovable(LevelEditorUnitsNames name)
{
    return moving[static_cast<int>(name)];
}

bool UnitTypeChecker::isBlock(LevelEditorUnitsNames name)
{
    return blocks[static_cast<int>(name)];
}

bool UnitTypeChecker::isEnemy(LevelEditorUnitsNames name)
{
    return enemies[static_cast<int>(name)];
}

bool UnitTypeChecker::isCoin(LevelEditorUnitsNames name)
{
    return coins[static_cast<int>(name)];
}

bool UnitTypeChecker::isMovingBlock(LevelEditorUnitsNames name)
{
    if (blocks[static_cast<int>(name)] and moving[static_cast<int>(name)])
        return true;

    return false;
}
