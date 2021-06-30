#pragma once
#include <array>
#include "LevelEditorUnitsNames.h"

enum class UnitsTypes {
	block,
	enemy,
	coin,
	moving,
	flying,
	ground
};


class UnitTypeChecker
{
public:
	static bool isGround(LevelEditorUnitsNames name);
	static bool isMovingEnemy(LevelEditorUnitsNames name);
	static bool isMovable(LevelEditorUnitsNames name);
	static bool isBlock(LevelEditorUnitsNames name);
	static bool isEnemy(LevelEditorUnitsNames name);
	static bool isCoin(LevelEditorUnitsNames name);
	static bool isMovingBlock(LevelEditorUnitsNames name);
	static bool isUndeletable(LevelEditorUnitsNames name);
private:
	static const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> blocks;
	static const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> enemies;
	static const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> coins;
	static const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> moving;
	static const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> ground;
	static const std::array<bool, static_cast<int>(LevelEditorUnitsNames::counter)> undeletable;
};


