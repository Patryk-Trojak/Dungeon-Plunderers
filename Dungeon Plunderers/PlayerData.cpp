#include "pch.h"
#include "PlayerData.h"

PlayerData::PlayerData()
	:money(150000),
	spentMoneyInShop(0),
	levelOfPlayer(1),
	experienceOfPlayer(0),
	numberOfUnlockedLevels(1),
	isStormtrooperChosen(true),
	dateOfCreation(Date::getCurrentDate()),
	dateOfLastRun("Nigdy")
{
	numbersOfUpgradeBought[UpgradeName::HandgunDamage] = 0;
	numbersOfUpgradeBought[UpgradeName::RifleDamage] = 0;
	numbersOfUpgradeBought[UpgradeName::ShotgunDamage] = 0;
	numbersOfUpgradeBought[UpgradeName::BasicWandDamage] = 0;
	numbersOfUpgradeBought[UpgradeName::FireWandDamage] = 0;
	numbersOfUpgradeBought[UpgradeName::IceWandDamage] = 0;
	numbersOfUpgradeBought[UpgradeName::HelicopterDamage] = 0;
	numbersOfUpgradeBought[UpgradeName::ShadowWandDamage] = 0;

	numbersOfUpgradeBought[UpgradeName::HandgunFireRate] = 0;
	numbersOfUpgradeBought[UpgradeName::RifleFireRate] = 0;
	numbersOfUpgradeBought[UpgradeName::ShotgunFireRate] = 0;
	numbersOfUpgradeBought[UpgradeName::BasicWandFireRate] = 0;
	numbersOfUpgradeBought[UpgradeName::FireWandFireRate] = 0;
	numbersOfUpgradeBought[UpgradeName::IceWandFireRate] = 0;
	numbersOfUpgradeBought[UpgradeName::HelicopterFireRate] = 0;
	numbersOfUpgradeBought[UpgradeName::ShadowWandFireRate] = 0;

	numbersOfUpgradeBought[UpgradeName::RifleInitialAmmo] = 0;
	numbersOfUpgradeBought[UpgradeName::ShotgunInitialAmmo] = 0;
	numbersOfUpgradeBought[UpgradeName::FireWandCostOfShot] = 0;
	numbersOfUpgradeBought[UpgradeName::IceWandCostOfShot] = 0;

}
