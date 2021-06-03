#pragma once
#include "PlayerData.h"
#include "SettingsData.h"
#include "Keybinds.h"
#include "PathsToPersistences.h"
#include "DefaultPersistenceCreator.h"

class PersistenceLoader
{
public:
	static PlayerData loadPlayerData(const std::string& fileName);
	static SettingsData loadSettingsData();
	static Keybinds loadKeybinds();
	static PlayerData loadLevelEditorPlayerData();

private:
	static PlayerData loadPlayerDataFromFilepath(const std::string& filepath);
};

