 #include "pch.h"
#include "SaveSelectionState.h"

namespace fs = std::filesystem;

SaveSelectionState::SaveSelectionState(StateData& stateData)
	:FileSelection(stateData, "\\Saves")
{
	for (auto& i : saveButtons)
	{
		stateData.savedPlayerData = PersistenceLoader::loadPlayerData(i->getName());
		i->setDateOfLastRun(stateData.savedPlayerData.dateOfLastRun);
		i->setDateOfCreation(stateData.savedPlayerData.dateOfCreation);
	}
	infoAboutCurrentSave = std::make_unique<TextButton>(sf::Vector2f(0, 0), sf::Vector2f(340, 241),
		stateData.resources[TextureID::InformationAboutSaveBackground], stateData.resources.font,
		L"", 37);
}


SaveSelectionState::~SaveSelectionState()
{
}


void SaveSelectionState::handleInfoAboutCurrentSave()
{
	for (auto const& i : saveButtons)
	{
		if (i->isMouseOverButton(mousePositionView))
		{
			if (!isMouseOverSaveButtons)
			{	
				if (infoAboutCurrentSave)
				{
					stateData.savedPlayerData = PersistenceLoader::loadPlayerData(i->getName());

					infoAboutCurrentSave->setPosition(sf::Vector2f(i->getPosition().x + 820, i->getPosition().y));
					infoAboutCurrentSave->setText("Level: " + std::to_string(stateData.savedPlayerData.levelOfPlayer) +
						"\nMonety: " + std::to_string(stateData.savedPlayerData.money) +
						"\nOdblokowane poziomy: " + std::to_string(stateData.savedPlayerData.numberOfUnlockedLevels) +
						"\nIlosc kupionych ulepszen: " + std::to_string(numberOfAllBoughtUpgradesFrom(stateData.savedPlayerData)), ContentAlignment::left);
					isMouseOverSaveButtons = true;
				}					
			}
		}
	}
}


void SaveSelectionState::createSaveFile(const std::string& name)
{
	DefaultPersistenceCreator::createNewPlayerDataSave(name);
}

void SaveSelectionState::loadFile(const std::string& filepath)
{
	std::string name = filepath;
	auto n = name.find(".\\Saves\\");

	if (n != std::string::npos)
	{
		name.erase(n, 8);
	}
	name.pop_back();
	name.pop_back();
	name.pop_back();
	name.pop_back();
	stateData.nameOfCurrentlyLoadedPlayerSave = name;
	stateData.savedPlayerData = PersistenceLoader::loadPlayerData(name);
}

void SaveSelectionState::moveToNextState(SaveButton& clicked)
{
	wasMousePressed = false;
	PersistenceSaver::saveDateOfLastRunToPlayerDataFile(clicked.getName(), Date::getCurrentDate());
	clicked.setDateOfLastRun(Date::getCurrentDate());
	stateData.states.push(std::make_unique<SecondMenuState>(stateData));
}




