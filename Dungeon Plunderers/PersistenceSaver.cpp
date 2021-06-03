#include "pch.h"
#include "PersistenceSaver.h"

void PersistenceSaver::save(const PlayerData& playerData, const std::string& fileName)
{
	std::string filepath = PathsToPersistences::createFilePathToPlayerDataFile(fileName);
	savePlayerDataToFilepath(playerData, filepath);
}

void PersistenceSaver::saveLevelEditorPlayerData(const PlayerData& guineaPig)
{
	std::string filepath = PathsToPersistences::toLevelEditorPlayerData;
	savePlayerDataToFilepath(guineaPig, filepath);
}

void PersistenceSaver::save(const SettingsData& settings)
{
	std::ofstream file;
	file.open(PathsToPersistences::toSettings);

	file << settings.fullscreen << std::endl;
	file << settings.windowSize.x << std::endl;
	file << settings.windowSize.y << std::endl;
	file << settings.windowPosition.x << std::endl;
	file << settings.windowPosition.y << std::endl;
	file << settings.resizeProportionally << std::endl;
	file << settings.isVerticalSyncEnabled << std::endl;
	file << settings.isLimitFPSEnabled << std::endl;
	file << settings.maxFPS << std::endl;
	file << settings.showFPS << std::endl;
	file << settings.FPSOnTop << std::endl;
	file << settings.FPSOnLeft << std::endl;
	file << settings.characterSizeOfFPS << std::endl;
	file << static_cast<int>(settings.colorOfFPS.r) << std::endl;
	file << static_cast<int>(settings.colorOfFPS.g) << std::endl;
	file << static_cast<int>(settings.colorOfFPS.b) << std::endl;
	file << static_cast<int>(settings.colorOfFPS.a) << std::endl;
	file << settings.showOutlineFPS << std::endl;
	file << settings.outlineThickness << std::endl;
	file << static_cast<int>(settings.colorOfOutlineFPS.r) << std::endl;
	file << static_cast<int>(settings.colorOfOutlineFPS.g) << std::endl;
	file << static_cast<int>(settings.colorOfOutlineFPS.b) << std::endl;
	file << static_cast<int>(settings.colorOfOutlineFPS.a);

	file.close();
}

void PersistenceSaver::save(const Keybinds& keybinds)
{
	std::fstream file;
	file.open(PathsToPersistences::toKeybinds);
	file << keybinds[KeybindID::MoveRight] << std::endl;
	file << keybinds[KeybindID::MoveLeft] << std::endl;
	file << keybinds[KeybindID::Jump] << std::endl;
	file << keybinds[KeybindID::FirstWeapon] << std::endl;
	file << keybinds[KeybindID::SecondWeapon] << std::endl;
	file << keybinds[KeybindID::ThirdWeapon] << std::endl;
	file << keybinds[KeybindID::MoveRightPlaneOrCloud] << std::endl;
	file << keybinds[KeybindID::MoveLeftPlaneOrCloud] << std::endl;
	file << keybinds[KeybindID::MoveUpPlaneOrCloud] << std::endl;
	file << keybinds[KeybindID::MoveDownPlaneOrCloud] << std::endl;
	file << keybinds[KeybindID::GetOffPlaneOrCloud] << std::endl;
	file << keybinds[KeybindID::Attack] << std::endl;
	file << keybinds[KeybindID::DrinkHealthPotion] << std::endl;
	file << keybinds[KeybindID::DrinkManaPotion] << std::endl;
	file.close();
}

void PersistenceSaver::saveDateOfLastRunToPlayerDataFile(const std::string& fileName, const std::string& newDateOfLastRun)
{
	rewriteLineInFile(PathsToPersistences::createFilePathToPlayerDataFile(fileName), 27, newDateOfLastRun);
}

void PersistenceSaver::saveDateOfLastRunToPlayerLevelFile(const std::string& fileName, const std::string& newDateOfLastRun)
{
	rewriteLineInFile(PathsToPersistences::createFilePathToPlayerLevelFile(fileName), 1, newDateOfLastRun);
}

void PersistenceSaver::savePlayerDataToFilepath(const PlayerData& playerData, const std::string& filepath)
{
	std::ofstream file;
	file.open(filepath);

	file << playerData.money << '\n' ;//1
	file << playerData.spentMoneyInShop << '\n';//2
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::HandgunDamage) << '\n';//3
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::RifleDamage) << '\n';//4
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::ShotgunDamage) << '\n';//5
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::BasicWandDamage) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::FireWandDamage) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::IceWandDamage) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::HelicopterDamage) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::ShadowWandDamage) << '\n';

	file << playerData.numbersOfUpgradeBought.at(UpgradeName::HandgunFireRate) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::RifleFireRate) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::ShotgunFireRate) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::BasicWandFireRate) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::FireWandFireRate) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::IceWandFireRate) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::HelicopterFireRate) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::ShadowWandFireRate) << '\n';

	file << playerData.numbersOfUpgradeBought.at(UpgradeName::RifleInitialAmmo) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::ShotgunInitialAmmo) << '\n';

	file << playerData.numbersOfUpgradeBought.at(UpgradeName::FireWandCostOfShot) << '\n';
	file << playerData.numbersOfUpgradeBought.at(UpgradeName::IceWandCostOfShot) << '\n';


	file << playerData.levelOfPlayer << '\n';
	file << playerData.experienceOfPlayer << '\n';
	file << playerData.numberOfUnlockedLevels << '\n';
	file << playerData.isStormtrooperChosen << '\n';
	file << playerData.dateOfLastRun << '\n';
	file << playerData.dateOfCreation;
	file.close();
}

void PersistenceSaver::rewriteLineInFile(const std::string& filepath, int numberOfLineToChange, const std::string& newLine)
{
	std::ifstream file;
	file.open(filepath);
	std::vector<std::string> newLinesOfFile;
	int numberOfLine = 1;
	while (!file.eof())
	{
		if (numberOfLine == numberOfLineToChange)
		{
			std::string lineToChange;
			file >> lineToChange;
			newLinesOfFile.emplace_back(newLine);
		}
		else
		{
			newLinesOfFile.emplace_back();
			file >> newLinesOfFile.back();
		}
		numberOfLine++;
	}

	file.close();
	std::ofstream newFile;
	newFile.open(filepath);

	for (auto i = newLinesOfFile.begin(); i < newLinesOfFile.end(); i++)
	{
		newFile << *i;
		if (i != (newLinesOfFile.end() - 1))
			newFile << std::endl;
	}

	newFile.close();
}
