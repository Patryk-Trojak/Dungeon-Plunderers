#pragma once
#include"FileSelection.h"
#include"SecondMenuState.h"

class SaveSelectionState :
	public FileSelection
{
public:
	SaveSelectionState(StateData& stateData);
	virtual ~SaveSelectionState();

private:
	void handleInfoAboutCurrentSave();

	virtual void createSaveFile(const std::string& name) override; //After new button created
	virtual void loadFile(const std::string& filepath) override; //After button clicked
	virtual void moveToNextState(SaveButton& clicked) override; //After button clicked
};

