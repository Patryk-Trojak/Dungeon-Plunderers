#include "pch.h"
#include "PersistenceLoader.h"

PlayerData PersistenceLoader::loadPlayerData(const std::string& fileName)
{
	std::string filepath = PathsToPersistences::toPlayerDataFilesDirectory + fileName + ".txt";
	return loadPlayerDataFromFilepath(filepath);
}

SettingsData PersistenceLoader::loadSettingsData()
{
	std::ifstream file;
	file.open(PathsToPersistences::toSettings);
	SettingsData settings;
	if (!file.good())
	{
		DefaultPersistenceCreator::createNewSettingFile();	
	}
	else
	{
		if (!file.eof())
		{
			int colorOfFPSR, colorOfFPSG, colorOfFPSB, colorOfFPSA, colorOfOutlineFPSR, colorOfOutlineFPSG, colorOfOutlineFPSB, colorOfOutlineFPSA;
			file >> settings.fullscreen;
			file >> settings.windowSize.x;
			file >> settings.windowSize.y;
			file >> settings.windowPosition.x;
			file >> settings.windowPosition.y;
			file >> settings.resizeProportionally;
			file >> settings.isVerticalSyncEnabled;
			file >> settings.isLimitFPSEnabled;
			file >> settings.maxFPS;
			file >> settings.showFPS;
			file >> settings.FPSOnTop;
			file >> settings.FPSOnLeft;
			file >> settings.characterSizeOfFPS;
			file >> colorOfFPSR;
			file >> colorOfFPSG;
			file >> colorOfFPSB;
			file >> colorOfFPSA;
			file >> settings.showOutlineFPS;
			file >> settings.outlineThickness;
			file >> colorOfOutlineFPSR;
			file >> colorOfOutlineFPSG;
			file >> colorOfOutlineFPSB;
			file >> colorOfOutlineFPSA;

			settings.colorOfFPS = sf::Color(colorOfFPSR, colorOfFPSG, colorOfFPSB, colorOfFPSA);
			settings.colorOfOutlineFPS = sf::Color(colorOfOutlineFPSR, colorOfOutlineFPSG, colorOfOutlineFPSB, colorOfOutlineFPSA);

		}
	}
	file.close();

	return settings;
}

Keybinds PersistenceLoader::loadKeybinds()
{
	Keybinds keybinds;
	std::string line;
	int lineCounter = 1;
	std::ifstream file;
	file.open(PathsToPersistences::toKeybinds);

	while (getline(file, line))
	{
		switch (lineCounter)
		{
		case 1:
			keybinds.add(KeybindID::MoveRight, std::stoi(line));
			break;
		case 2:
			keybinds.add(KeybindID::MoveLeft, std::stoi(line));
			break;
		case 3:
			keybinds.add(KeybindID::Jump, std::stoi(line));
			break;
		case 4:
			keybinds.add(KeybindID::FirstWeapon, std::stoi(line));
			break;
		case 5:
			keybinds.add(KeybindID::SecondWeapon, std::stoi(line));
			break;
		case 6:
			keybinds.add(KeybindID::ThirdWeapon, std::stoi(line));
			break;
		case 7:
			keybinds.add(KeybindID::MoveRightPlaneOrCloud, std::stoi(line));
			break;
		case 8:
			keybinds.add(KeybindID::MoveLeftPlaneOrCloud, std::stoi(line));
			break;
		case 9:
			keybinds.add(KeybindID::MoveUpPlaneOrCloud, std::stoi(line));
			break;
		case 10:
			keybinds.add(KeybindID::MoveDownPlaneOrCloud, std::stoi(line));
			break;
		case 11:
			keybinds.add(KeybindID::GetOffPlaneOrCloud, std::stoi(line));
			break;
		case 12:
			keybinds.add(KeybindID::Attack, std::stoi(line));
			break;
		case 13:
			keybinds.add(KeybindID::DrinkHealthPotion, std::stoi(line));
			break;
		case 14:
			keybinds.add(KeybindID::DrinkManaPotion, std::stoi(line));
			break;
		}
		lineCounter++;
	}
	file.close();
	return keybinds;
}

PlayerData PersistenceLoader::loadLevelEditorPlayerData()
{
	std::string filepath = PathsToPersistences::toLevelEditorPlayerData;
	return loadPlayerDataFromFilepath(filepath);
}


PlayerData PersistenceLoader::loadPlayerDataFromFilepath(const std::string& filepath)
{
	PlayerData playerData;
	std::ifstream file;
	file.open(filepath);
	if (!file.good())
	{
		std::cout << "Niestety nie udalo sie otworzyc zapisu" << std::endl;
	}
	if (!file.eof())
	{
		file >> playerData.money;//1
		file >> playerData.spentMoneyInShop;//2
		file >> playerData.numbersOfUpgradeBought[UpgradeName::HandgunDamage];//3
		file >> playerData.numbersOfUpgradeBought[UpgradeName::RifleDamage];//4
		file >> playerData.numbersOfUpgradeBought[UpgradeName::ShotgunDamage];//5
		file >> playerData.numbersOfUpgradeBought[UpgradeName::BasicWandDamage];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::FireWandDamage];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::IceWandDamage];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::HelicopterDamage];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::ShadowWandDamage];

		file >> playerData.numbersOfUpgradeBought[UpgradeName::HandgunFireRate];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::RifleFireRate];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::ShotgunFireRate];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::BasicWandFireRate];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::FireWandFireRate];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::IceWandFireRate];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::HelicopterFireRate];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::ShadowWandFireRate];

		file >> playerData.numbersOfUpgradeBought[UpgradeName::RifleInitialAmmo];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::ShotgunInitialAmmo];

		file >> playerData.numbersOfUpgradeBought[UpgradeName::FireWandCostOfShot];
		file >> playerData.numbersOfUpgradeBought[UpgradeName::IceWandCostOfShot];


		file >> playerData.levelOfPlayer;
		file >> playerData.experienceOfPlayer;
		file >> playerData.numberOfUnlockedLevels;
		file >> playerData.isStormtrooperChosen;
		file >> playerData.dateOfLastRun;
		file >> playerData.dateOfCreation;
	}
	file.close();
	return playerData;
}
