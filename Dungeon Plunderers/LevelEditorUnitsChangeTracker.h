#pragma once
#include "LevelEditorUnit.h"

class LevelEditorUnitsChangeTracker
{
public:
	LevelEditorUnitsChangeTracker(std::vector<LevelEditorUnit>& units, int& numberOfSelectedUnits, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures);
	virtual ~LevelEditorUnitsChangeTracker();
	void addCurrentUnitsToHistory();
	void redoChangeOfUnits();
	void undoChangeOfUnits();
private:
	std::vector<LevelEditorUnit>& units;
	int& numberOfSelectedUnits;
	const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures;

	std::vector< std::vector<LevelEditorUnitData> > historyOfUnits;
	std::vector< std::vector<LevelEditorUnitData> >::iterator currentUnits;
	std::vector<LevelEditorUnit>  makeVectorOfUnitsFrom(const std::vector<LevelEditorUnitData>& unitsData);
	std::vector<LevelEditorUnitData> makeVectorOfUnitsDataFrom(const std::vector<LevelEditorUnit>& units);
};

