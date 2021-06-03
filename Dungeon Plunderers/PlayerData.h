#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <array>
#include "Date.h"

enum class Projectiles
{
	HandgunBullet = 0,
	MachingunBullet,
	ShotgunBullet,
	BasicWandProjectile,
	FireWandProjectile,
	IceWandProjectile,
	PlaneBullet,
	ShadowWandProjectile
};

enum class Weapons
{
	Handgun = 0,
	Machingun,
	Shotgun,
	BasicWand,
	FireWand,
	IceWand,
	PlaneWeapon,
	ShadowWand
};

enum class UpgradeName {
	HandgunDamage,
	RifleDamage,
	ShotgunDamage,
	BasicWandDamage,
	FireWandDamage,
	IceWandDamage,
	HelicopterDamage,
	ShadowWandDamage,

	HandgunFireRate,
	RifleFireRate,
	ShotgunFireRate,
	BasicWandFireRate,
	FireWandFireRate,
	IceWandFireRate,
	HelicopterFireRate,
	ShadowWandFireRate,

	RifleInitialAmmo,
	ShotgunInitialAmmo,

	FireWandCostOfShot,
	IceWandCostOfShot,
};

struct PlayerData
{
	PlayerData();
	int money;
	int spentMoneyInShop;
	std::unordered_map<UpgradeName, int> numbersOfUpgradeBought;
	int levelOfPlayer;
	float experienceOfPlayer;
	int numberOfUnlockedLevels;
	bool isStormtrooperChosen;
	std::string dateOfLastRun;
	std::string dateOfCreation;

};