#include "pch.h"
#include "StatsPlayerCreator.h"

StormtrooperStats StatsPlayerCreator::stormtrooperStats(const PlayerData& playerSave)
{
	StormtrooperStats stats;
	stats.health = 100 + (playerSave.levelOfPlayer - 1) * 10;

	stats.handgunDamage = 10.f + playerSave.numbersOfUpgradeBought.at(UpgradeName::HandgunDamage) * 5.f;
	stats.handgunFireRate = 0.4f - playerSave.numbersOfUpgradeBought.at(UpgradeName::HandgunFireRate) * 0.05f;

	stats.rifleFireRate = 0.1f - playerSave.numbersOfUpgradeBought.at(UpgradeName::RifleFireRate) * 0.01f;
	stats.rifleInitialAmmo = 120 + playerSave.numbersOfUpgradeBought.at(UpgradeName::RifleInitialAmmo) * 30 + playerSave.levelOfPlayer * 15;
	stats.rifleDamage = 15.f + playerSave.numbersOfUpgradeBought.at(UpgradeName::RifleDamage) * 1.f;

	stats.shotgunFireRate = 1.f - playerSave.numbersOfUpgradeBought.at(UpgradeName::ShotgunFireRate) * 0.1f;
	stats.shotgunDamage = 15.f + playerSave.numbersOfUpgradeBought.at(UpgradeName::ShotgunDamage) * 5.f;
	stats.shotgunInitialAmmo = 20 + playerSave.numbersOfUpgradeBought.at(UpgradeName::ShotgunDamage) * 10 + playerSave.levelOfPlayer * 5;

	playerSave.numbersOfUpgradeBought.at(UpgradeName::ShotgunInitialAmmo);
	
	return stats;
}

WizardStats StatsPlayerCreator::wizardStats(const PlayerData& playerSave)
{
	WizardStats stats;

	stats.basicWandDamage = 6.f + playerSave.numbersOfUpgradeBought.at(UpgradeName::BasicWandDamage) * 3.f;
	stats.basicWandFireRate = 0.2f - playerSave.numbersOfUpgradeBought.at(UpgradeName::BasicWandFireRate) * 0.02f;

	stats.fireWandDamage = 50.f + playerSave.numbersOfUpgradeBought.at(UpgradeName::FireWandDamage) * 30.f;
	stats.fireWandFireRate = 0.8 - playerSave.numbersOfUpgradeBought.at(UpgradeName::FireWandFireRate) * 0.05f;
	stats.fireWandCostOfShot = 10.f - playerSave.numbersOfUpgradeBought.at(UpgradeName::FireWandCostOfShot) * 1.f;

	stats.iceWandDamage = 80.f + playerSave.numbersOfUpgradeBought.at(UpgradeName::IceWandDamage) * 44.f;
	stats.iceWandFireRate = 1.1 - playerSave.numbersOfUpgradeBought.at(UpgradeName::IceWandFireRate) * 0.07f;
	stats.iceWandCostOfShot = 10.f - playerSave.numbersOfUpgradeBought.at(UpgradeName::IceWandCostOfShot) * 1.f;

	return stats;
}

HelicopterStats StatsPlayerCreator::helicopterStats(const PlayerData& playerSave)
{
	return HelicopterStats();
}

WizardOnCloudStats StatsPlayerCreator::wizardOnCloudStats(const PlayerData& playerSave)
{
	return WizardOnCloudStats();
}

int StatsPlayerCreator::getExpierienceToNextLevel(int numberOfOPlayerLevel)
{
	return numberOfOPlayerLevel * 1500;
}
