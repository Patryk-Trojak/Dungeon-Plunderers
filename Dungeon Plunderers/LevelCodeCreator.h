#pragma once
#include <vector>
#include "LevelEditorUnit.h"

class LevelCodeCreator
{
public:
	static void createCodeFrom(const std::vector<LevelEditorUnit>& units);

private:
	static void addEnemyToFile(LevelEditorUnitsNames unitsType);

};

