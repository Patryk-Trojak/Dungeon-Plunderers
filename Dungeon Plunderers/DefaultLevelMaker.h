#pragma once
#include<SFML/Graphics.hpp>
#include<functional>
#include "LevelName.h"
#include "LevelData.h"
#include"Coin.h"
#include"Spikes.h"
#include"Zombie.h"
#include"Fly.h"
#include"Player.h"
#include"ZombieBoss.h"
#include"SkeletonBoss.h"
#include"DeadlyFlower.h"
#include"GunEnemy.h"
#include "DeadlyFlowerBoss.h"

class DefaultLevelMaker
{
public: 
	static Level makeBossArea();
	static std::function<Level(const Resources & resources)> makeFunctionCreatingNextDefaultLevel(LevelName levelName);
	static std::function<Level(const Resources & resources)> makeFunctionCreatingDefaultLevel(LevelName levelName);
	static std::unique_ptr<Enemy> createBoss(LevelName levelName, PlayerType playerType, const Resources& resources);
private:
	static std::function<Level(const Resources & resources)> makeFunctionCreatingLevel1();
	static std::function<Level(const Resources & resources)> makeFunctionCreatingLevel2();
	static std::function<Level(const Resources & resources)> makeFunctionCreatingLevel3();
};

