#include "pch.h"
#include "StatsPlayerCreator.h"

StormtrooperStats StatsPlayerCreator::stormtrooperStats(const PlayerData& playerSave)
{
	return StormtrooperStats();
}

WizardStats StatsPlayerCreator::wizardStats(const PlayerData& playerSave)
{
	WizardStats stats;

	stats.basicWandDamage = 20 + playerSave.numbersOfUpgradeBought.at(UpgradeName::BasicWandDamage) * 20;

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
