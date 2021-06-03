#pragma once
#include "PlayerData.h"
#include "PathsToPersistences.h"
#include "LevelEditorUnit.h"
#include "SettingsData.h"
#include "Keybinds.h"

class PersistenceSaver
{
public:
	static void save(const PlayerData& playerData, const std::string& fileName);
	static void saveLevelEditorPlayerData(const PlayerData& guineaPig);
	static void save(const SettingsData& settings);
	static void save(const Keybinds& keybinds);
	static void save(const std::vector<LevelEditorUnit>& units);
	static void saveDateOfLastRunToPlayerDataFile(const std::string& fileName, const std::string& newDateOfLastRun);
	static void saveDateOfLastRunToPlayerLevelFile(const std::string& fileName, const std::string& newDateOfLastRun);
private:
	static void savePlayerDataToFilepath(const PlayerData& playerData, const std::string& filepath);
	static void rewriteLineInFile(const std::string& filepath, int numberOfLineToChange, const std::string& newLine);
};

