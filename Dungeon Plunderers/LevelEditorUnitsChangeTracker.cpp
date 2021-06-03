#include "pch.h"
#include "LevelEditorUnitsChangeTracker.h"

LevelEditorUnitsChangeTracker::LevelEditorUnitsChangeTracker(std::vector<LevelEditorUnit>& units, int& numberOfSelectedUnits, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures)
	:units(units), numberOfSelectedUnits(numberOfSelectedUnits), unitsTextures(unitsTextures)
{
}

LevelEditorUnitsChangeTracker::~LevelEditorUnitsChangeTracker()
{
}

void LevelEditorUnitsChangeTracker::addCurrentUnitsToHistory()
{
	if (!historyOfUnits.empty() and currentUnits != historyOfUnits.end() - 1)
		historyOfUnits.erase(currentUnits + 1, historyOfUnits.end());

	if (historyOfUnits.size() > 100)
		historyOfUnits.erase(historyOfUnits.begin());
	historyOfUnits.emplace_back(std::move(makeVectorOfUnitsDataFrom(units)));
	currentUnits = historyOfUnits.end() - 1;
}

void LevelEditorUnitsChangeTracker::redoChangeOfUnits()
{
	if (currentUnits != historyOfUnits.end() - 1)
	{
		currentUnits++;
		units = std::move(makeVectorOfUnitsFrom(*currentUnits));
		numberOfSelectedUnits = 0;
	}
}

void LevelEditorUnitsChangeTracker::undoChangeOfUnits()
{
	if (currentUnits != historyOfUnits.begin())
	{
		currentUnits--;
		units = std::move(makeVectorOfUnitsFrom(*currentUnits));
		numberOfSelectedUnits = 0;
	}
}

std::vector<LevelEditorUnit> LevelEditorUnitsChangeTracker::makeVectorOfUnitsFrom(const std::vector<LevelEditorUnitData>& unitsData)
{
	std::vector<LevelEditorUnit> units;
	units.reserve(unitsData.size());
	for (auto const& i : unitsData)
		units.emplace_back(i, unitsTextures);

	return units;
}

std::vector<LevelEditorUnitData> LevelEditorUnitsChangeTracker::makeVectorOfUnitsDataFrom(const std::vector<LevelEditorUnit>& units)
{
	std::vector<LevelEditorUnitData> unitsData;
	unitsData.reserve(units.size());
	for (auto const& i : units)
		unitsData.emplace_back(i.getType(), i.getPosition(), i.getMovingDistance(), i.getSize());

	return unitsData;
}
