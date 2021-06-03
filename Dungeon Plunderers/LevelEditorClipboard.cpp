#include "pch.h"
#include "LevelEditorClipboard.h"

LevelEditorClipboard::LevelEditorClipboard(std::vector<LevelEditorUnit>& units, int& numberOfSelectedUnits, const ResourceHolder<LevelEditorUnitsNames, sf::Texture>& unitsTextures)
	:units(units), numberOfSelectedUnits(numberOfSelectedUnits), unitsTextures(unitsTextures)
{
}

LevelEditorClipboard::~LevelEditorClipboard()
{
}

void LevelEditorClipboard::copySelectedUnits()
{
	clipboard.clear();
	for (auto i = units.rbegin(); i != units.rbegin() + numberOfSelectedUnits; ++i)
		clipboard.emplace_back(i->getType(), i->getPosition(), i->getMovingDistance(), i->getSize());
}

void LevelEditorClipboard::paste(const sf::Vector2f& centerPositionOfPastedUnits)
{
	if (!clipboard.empty())
	{
		std::vector<LevelEditorUnit> unitsFromClipboard = makeVectorOfUnitsFrom(clipboard);
		sf::Vector2f unitShift = centerPositionOfPastedUnits - centerOfUnits(unitsFromClipboard);

		for (auto& i : unitsFromClipboard)
			i.move(unitShift);

		std::move(unitsFromClipboard.begin(), unitsFromClipboard.end(), std::back_inserter(units));

		numberOfSelectedUnits = clipboard.size();
	}
}

sf::Vector2f LevelEditorClipboard::centerOfUnits(const std::vector<LevelEditorUnit>& units) const
{

	float maxLeftOfUnitsOnClipboard = std::max_element(units.begin(), units.end(), [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
		return a.maxLeftHitboxes() > b.maxLeftHitboxes();
		})->maxLeftHitboxes();
	float maxRightOfUnitsOnClipboard = std::max_element(units.begin(), units.end(), [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
		return a.maxRightHitboxes() < b.maxRightHitboxes();
		})->maxRightHitboxes();
	float maxTopOfUnitsOnClipboard = std::max_element(units.begin(), units.end(), [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
		return a.maxTopHitboxes() > b.maxTopHitboxes();
		})->maxTopHitboxes();	
	float maxBottomOfUnitsOnClipboard = std::max_element(units.begin(), units.end(), [](const LevelEditorUnit& a, const LevelEditorUnit& b) {
		return a.maxBottomHitboxes() < b.maxBottomHitboxes();
		})->maxBottomHitboxes();
	return sf::Vector2f(maxLeftOfUnitsOnClipboard + (maxRightOfUnitsOnClipboard - maxLeftOfUnitsOnClipboard) / 2, maxTopOfUnitsOnClipboard + (maxBottomOfUnitsOnClipboard - maxTopOfUnitsOnClipboard) / 2);

}

std::vector<LevelEditorUnit> LevelEditorClipboard::makeVectorOfUnitsFrom(const std::vector<LevelEditorUnitData>& unitsData)
{
	std::vector<LevelEditorUnit> units;
	units.reserve(unitsData.size());
	for (auto const& i : unitsData)
		units.emplace_back(i, unitsTextures);

	return units;
}