#pragma once
#include "PlayerData.h"
#include "Date.h"
#include "SettingsData.h"
#include "PersistenceSaver.h"

class DefaultPersistenceCreator
{
public:
	static void createNewPlayerDataSave(const std::string& nameOfFile);
	static void createNewPlayerLevelSave(const std::string& nameOfFile);
	static void createNewSettingFile();
	static void createNewKeybindsFile();
};

