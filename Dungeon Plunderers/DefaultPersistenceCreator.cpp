#include "pch.h"
#include "DefaultPersistenceCreator.h"

void DefaultPersistenceCreator::createNewPlayerDataSave(const std::string& nameOfFile)
{
	std::ofstream file;
	file.open( PathsToPersistences::toPlayerDataFilesDirectory + nameOfFile + ".txt" );

	PlayerData defaultPlayerData;

	

	PersistenceSaver::save(defaultPlayerData, nameOfFile);

	file.close();
}

void DefaultPersistenceCreator::createNewPlayerLevelSave(const std::string& nameOfFile)
{
	std::ofstream file;
	file.open(PathsToPersistences::toPlayerLevelsFilesDirectory + nameOfFile + ".txt");
	file << "Nigdy" << std::endl;//48
	file << Date::getCurrentDate() << std::endl;//49
	file << "490" << std::endl;//48
	file << "490";//48
	file.close();
}

void DefaultPersistenceCreator::createNewSettingFile()
{
	std::ofstream file;
	file.open(PathsToPersistences::toSettings);

	SettingsData defaultSettings;
	PersistenceSaver::save(defaultSettings);

	file.close();
}

void DefaultPersistenceCreator::createNewKeybindsFile()
{
	std::ofstream file;
	file.open(PathsToPersistences::toKeybinds);

	Keybinds defaultKeybinds;
	PersistenceSaver::save(defaultKeybinds);

	file.close();
}
