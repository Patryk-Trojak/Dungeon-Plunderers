#pragma once
#include "LevelEditorUnit.h"

class LevelEditorClipboard
{
public:
	LevelEditorClipboard(std::vector<LevelEditorUnit>& units, int& numberOfSelectedUnits, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures);
	virtual ~LevelEditorClipboard();

	void copySelectedUnits();
	void paste(const sf::Vector2f& centerPositionOfPastedUnits);
private:
	std::vector<LevelEditorUnit>& units;
	int& numberOfSelectedUnits;
	const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures;
	std::vector< LevelEditorUnitData > clipboard;
	std::vector<LevelEditorUnit> makeVectorOfUnitsFrom(const std::vector<LevelEditorUnitData>& unitsData);

	sf::Vector2f centerOfUnits(const std::vector<LevelEditorUnit>& units) const;

};

