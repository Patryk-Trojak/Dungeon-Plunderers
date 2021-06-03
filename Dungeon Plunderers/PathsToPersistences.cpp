#include "pch.h"
#include "PathsToPersistences.h"

const std::string PathsToPersistences::toPlayerDataFilesDirectory = ".\\Saves\\";
const std::string PathsToPersistences::toPlayerLevelsFilesDirectory = ".\\Levels\\";
const std::string PathsToPersistences::toLevelEditorPlayerData = ".\\LevelEditor\\guinea-pig.txt";
const std::string PathsToPersistences::toSettings = ".\\Settings\\config.txt";
const std::string PathsToPersistences::toKeybinds = ".\\Settings\\controls.txt";

std::string PathsToPersistences::createFilePathToPlayerDataFile(const std::string& filename)
{
	return toPlayerDataFilesDirectory + filename + ".txt";
}

std::string PathsToPersistences::createFilePathToPlayerLevelFile(const std::string& filename)
{
	return toPlayerLevelsFilesDirectory + filename + ".txt";
}
