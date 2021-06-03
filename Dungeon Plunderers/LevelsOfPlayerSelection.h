#pragma once
#include"FileSelection.h"
#include"LevelEditorUnit.h"
#include"LevelEditorState.h"
#include"UnitTypeChecker.h"
#include"GameplayState.h"

class Coin;
class Enemy;
class Block;

class LevelsOfPlayerSelection
	: public FileSelection
{
public:
	LevelsOfPlayerSelection(StateData& stateData, const bool moveToCreatorAfterSelected = true);
	virtual ~LevelsOfPlayerSelection();

private:
	void handleInfoAboutCurrentSave();

	virtual void createSaveFile(const std::string& filename) override; //After new button created
	virtual void loadFile(const std::string& filepath) override; //After button clicked
	virtual void moveToNextState(SaveButton& clicked) override; //After button clicked

	bool moveToCreatorAfterSelected;
	std::string currentFilepath;
	void initFunctionConvertUnitsToLevel();
	std::function<Level(const Resources & resources)> convertUnitsToLevel;
	void loadUnitsFromFile(const std::string& filepath);
	std::vector<LevelEditorUnit> units;
	sf::Vector2f positionOfPlayer;

};

