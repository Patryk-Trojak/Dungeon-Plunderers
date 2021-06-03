#pragma once
#include <iostream>
#include <algorithm>
#include <vector> 
#include <time.h>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <memory>
#include <fstream>
#include <cstdio>

#include "State.h"
#include "SaveButton.h"
#include "Feedback.h"
#include "ScrollBar.h"
#include "DropDownList.h"
#include "Messagebox.h"
#include "PersistenceSaver.h"
#include "DefaultPersistenceCreator.h"
#include "Date.h"

class FileSelection
	:public State
{
public:
	FileSelection(StateData& stateData, const std::string directoryPath);
	virtual ~FileSelection();
	virtual void update(const float deltaTime) override;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) override;
protected:
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	bool wasEnterPressed;
	bool wasDownPressed;
	bool wasUpPressed;
	bool wasEscapePressed;


	virtual void handleInfoAboutCurrentSave() = 0;
	std::unique_ptr<TextButton> infoAboutCurrentSave;
	std::vector < std::unique_ptr< SaveButton >> saveButtons;
	std::unique_ptr<Feedback> feedback;
	ScrollBar scrollbar;


	Textbox searchBox;
	Button searcherNext;
	Button searcherPrevious;
	Button searcherTheClosest;
	Button deleteSearching;
	std::vector<std::unique_ptr< SaveButton >>::iterator lastSearchedButton;
	std::vector<std::vector<std::unique_ptr< SaveButton >>::iterator> allFoundButtons;
	void searchNext(const std::string& searchedName);
	void searchPrevious(const std::string& searchedName);
	void searchTheClosest(const std::string& searchedName);
	void findAllButtons(const std::string& searchedName);

	void handleSearch(const float deltaTime);
	void handleSortOfButtons();

	sf::Text sort;
	DropDownList howSortButton;
	void sortSaveButtons();
	void setPositionOfSaveButtons();

	std::unique_ptr<game::MessageBox> areYouSureToDeleteSave;
	void createMessageBoxAreYouSureToDeleteSave();
	void handleMessageBoxAreYouSureToDeleteSave();
	std::vector<std::unique_ptr< SaveButton >>::iterator deletingSaveButton;

	Button saveCreator;
	void addSave();
	bool isAddingSave;
	virtual void createSaveFile(const std::string& fileName) = 0;
	virtual void loadFile(const std::string& fileName) = 0;

	virtual void moveToNextState(SaveButton& clicked) = 0;
	int PageHeight;
	void updatePageHeight();
	void drawSaveButtons(sf::RenderTarget& target, sf::RenderStates states) const;
	void updateButtons(const float deltaTime);
	bool isChangingSaveButtonName();
	int numberOfButtonWhichNameIsChanging;
	bool isNameOfSaveButtonAlreadyInUse();
	bool wasNameChangeCorrectly;
	bool isMouseOverSaveButtons;
	std::string makeFilePathByNameOfSaveButton(const std::string& nameOfSaveButton);
	const std::string directoryPath; 
	int numberOfAllBoughtUpgradesFrom(const PlayerData& playerData);
};

