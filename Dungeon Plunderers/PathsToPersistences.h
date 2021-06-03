#pragma once
#include <string>

class PathsToPersistences
{
protected:
	static const std::string toPlayerDataFilesDirectory;
	static const std::string toPlayerLevelsFilesDirectory;
	static const std::string toLevelEditorPlayerData;
	static const std::string toSettings;
	static const std::string toKeybinds;

	static std::string createFilePathToPlayerDataFile(const std::string& filename);
	static std::string createFilePathToPlayerLevelFile(const std::string& filename);

	friend class PersistenceSaver;
	friend class PersistenceLoader;
	friend class DefaultPersistenceCreator;
};

