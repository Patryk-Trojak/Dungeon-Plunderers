#include "pch.h"
#include "FileSelection.h"

namespace fs = std::filesystem;

FileSelection::FileSelection(StateData& stateData, const std::string directoryPath)
	: State(stateData),
	wasNameChangeCorrectly{ false },
	numberOfButtonWhichNameIsChanging{ 0 },
	scrollbar(sf::Vector2f(1780, 65), sf::Vector2f(25, 950.f), 1080, 3000, stateData.resources[TextureID::ScrollerButton]),
	PageHeight(1000),
	searchBox(sf::Vector2f(1410.f, 50.f), sf::Vector2f(300.f, 50.f), stateData.resources[TextureID::SearchBox], stateData.resources.font, "", 30, std::vector<sf::Uint32>(), ContentAlignment::left),
	searcherNext(sf::Vector2f(1565.f, 102.f), sf::Vector2f(50.f, 50.f), stateData.resources[TextureID::Searcher]),
	searcherPrevious(sf::Vector2f(1555.f, 102.f), sf::Vector2f(50.f, 50.f), stateData.resources[TextureID::Searcher], sf::Vector2f(-1.f, 1.f)),
	searcherTheClosest(sf::Vector2f(1710.f, 50.f), sf::Vector2f(50.f, 50.f), stateData.resources[TextureID::Loupe]),
	deleteSearching(sf::Vector2f(1675.f, 60.f), sf::Vector2f(30.f, 30.f), stateData.resources[TextureID::Delete]),
	howSortButton(sf::Vector2f(110.f, 100.f), sf::Vector2f(400.f, 40.f), L"nazwy rosn¹co", stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, 30),
	saveCreator(sf::Vector2f(425.f, 925.f), sf::Vector2f(80.f, 80.f), stateData.resources[TextureID::Plus]),
	isAddingSave(false),
	sort(L"Sortuj wg:", stateData.resources.font),
	directoryPath(directoryPath)
{
	howSortButton.addOption(L"nazwy malej¹co");
	howSortButton.addOption(L"daty ostatniego uruchomienia rosnaca");
	howSortButton.addOption(L"daty ostatniego uruchomienia malejaco");
	howSortButton.addOption(L"daty utworzenia rosnaca");
	howSortButton.addOption(L"daty utworzenia malejaco");

	background.setTextureRect(sf::IntRect(0, 0, 1920, 100000));
	fs::path path = fs::current_path().string() += directoryPath;
	int numberOfButton = 0;
	for (auto const& i : fs::directory_iterator(path)) {
		if (i.is_regular_file() and i.path().extension() == ".txt")
		{
			saveButtons.emplace_back(std::make_unique<SaveButton>(sf::Vector2f(547.5, 100 + numberOfButton * 300),
				stateData.resources[TextureID::SaveButton], stateData.resources[TextureID::TextboxBackground],
				stateData.resources[TextureID::GreyButton100x50], stateData.resources[TextureID::AcceptButton], stateData.resources[TextureID::DeleteButton], stateData.resources[TextureID::DeleteSaveButton],
				stateData.resources.font));
			saveButtons.back()->setName(i.path().filename().string().substr(0, i.path().filename().string().length() - 4));
			numberOfButton++;
		}
	}
	PageHeight = 0;
	updatePageHeight();
	lastSearchedButton = saveButtons.end();

	sort.setPosition(10.f, 99.f);
	sort.setOutlineColor(sf::Color::Black);
	sort.setOutlineThickness(2);

	sortSaveButtons();
}


FileSelection::~FileSelection()
{
}

void FileSelection::update(const float deltaTime)
{
	if (!areYouSureToDeleteSave)
	{
		for (auto& i : saveButtons)
			i->setIdleColor(sf::Color::White);

		if (!isChangingSaveButtonName())
		{
			saveCreator.update(mousePositionHUD);
			isMouseOverSaveButtons = false;
			wasNameChangeCorrectly = false;

			if (lastSearchedButton != saveButtons.end() and wasEnterPressed)
			{
				loadFile(makeFilePathByNameOfSaveButton(lastSearchedButton->get()->getName()));
				moveToNextState(*lastSearchedButton->get());
			}
			handleSearch(deltaTime);

			handleInfoAboutCurrentSave();
			handleSortOfButtons();
		}

		updateInput(deltaTime);
		updateButtons(deltaTime);
		addSave();

		if (feedback)
			feedback->update(deltaTime);

		view.setCenter(sf::Vector2f(view.getCenter().x, PageHeight * scrollbar.getPercentValue() / 100 + view.getSize().y / 2));
		scrollbar.update(mousePositionHUD, wasMousePressed, PageHeight, deltaTime);
		updateBackToPreviousState();
	}
	handleMessageBoxAreYouSureToDeleteSave();
}

void FileSelection::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
	wasMousePressed = false;
	wasEnterPressed = false;
	wasDownPressed = false;
	wasUpPressed = false;
	wasEscapePressed = false;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		resizeWindowProportionally(window, event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
				wasMousePressed = true;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
				wasEnterPressed = true;

			if (event.key.code == sf::Keyboard::Escape)
			{
				wasEscapePressed = true;
				if (areYouSureToDeleteSave)
					areYouSureToDeleteSave.reset();
				else if (isChangingSaveButtonName())
				{
					if (!isAddingSave)
						saveButtons[numberOfButtonWhichNameIsChanging]->deleteChangeOfName();
					else
					{
						isAddingSave = false;
						saveButtons.erase(saveButtons.begin());
						lastSearchedButton = saveButtons.end();
						updatePageHeight();
						setPositionOfSaveButtons();
						wasMousePressed = false;
					}
				}
				else if (!searchBox.isActive())
				{
					numberOfStatesPop = 1;
				}

			}
			if (event.key.code == sf::Keyboard::Up)
				wasUpPressed = true;

			if (event.key.code == sf::Keyboard::Down)
				wasDownPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) or sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
			{
				if (event.key.code == sf::Keyboard::F)
				{
					searchBox.setActive(true);
					if (searchBox.getText() != "")
						findAllButtons(searchBox.getText());
				}
			}

		}

		if (event.type == sf::Event::TextEntered)
		{
			if (isChangingSaveButtonName())
			{
				if (event.text.unicode < 128)
					saveButtons[numberOfButtonWhichNameIsChanging]->handleEnteredTextWhenIsChangingName(event.text.unicode);
			}
			if (searchBox.isActive())
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) and !sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
				{
					if (event.text.unicode < 128)
					{
						searchBox.handleTextEntered(event.text.unicode);
						if (event.text.unicode != 13 and event.text.unicode != 27) //ENTER AND ESCAPE
						{
							findAllButtons(searchBox.getText());
							if (lastSearchedButton != saveButtons.end())
							{
								if (lastSearchedButton->get()->getName().find(searchBox.getText()) == std::string::npos or searchBox.getText() == "")
									lastSearchedButton = saveButtons.end();
							}
						}
					}
				}
			}
		}

		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0)
				scrollbar.moveViewY(-100);
			else if (event.mouseWheelScroll.delta < 0)
				scrollbar.moveViewY(100);
		}
	}

}

void FileSelection::updateInput(const float deltaTime)
{
	if (isChangingSaveButtonName())
	{
		if (wasMousePressed || wasEnterPressed)
		{
			if (!saveButtons[numberOfButtonWhichNameIsChanging]->wasDeleteChangeOfNamePressed(mousePositionView, wasMousePressed))
			{
				if (!isNameOfSaveButtonAlreadyInUse())
				{
					if (saveButtons[numberOfButtonWhichNameIsChanging]->getName() != "")
					{
						if (!isAddingSave)
						{
							std::string oldFilePath = makeFilePathByNameOfSaveButton(saveButtons[numberOfButtonWhichNameIsChanging]->getNameBeforeAttemptingToChange());
							std::string newFilePath = makeFilePathByNameOfSaveButton(saveButtons[numberOfButtonWhichNameIsChanging]->getName());
							if (rename(oldFilePath.c_str(), newFilePath.c_str()) == 0)
							{
								wasNameChangeCorrectly = true;
								feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Poprawnie zmieniono nazwê zapisu", 60, stateData.resources.font);
								std::string nameOfNewSave = saveButtons[numberOfButtonWhichNameIsChanging]->getName();
								sortSaveButtons();
								for (auto const& i : saveButtons)
									if (i->getName() == nameOfNewSave)
										scrollbar.moveViewToPositionY(i->getPosition().y + i->getSize().y / 2);
								searchBox.setText("");
								searchBox.setActive(false);
								allFoundButtons.clear();
								lastSearchedButton = saveButtons.end();
							}
							else
							{
								feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Niestety, nie uda³o sie zmieniæ nazwy", 60, stateData.resources.font);
								wasNameChangeCorrectly = false;
							}
						}
						else
						{
							wasNameChangeCorrectly = true;
							isAddingSave = false;
							std::string nameOfNewSave = saveButtons[numberOfButtonWhichNameIsChanging]->getName();
							createSaveFile(saveButtons[numberOfButtonWhichNameIsChanging]->getName());
							saveButtons[numberOfButtonWhichNameIsChanging].get()->setDateOfCreation(Date::getCurrentDate());
							sortSaveButtons();
							for (auto const& i : saveButtons)
								if (i->getName() == nameOfNewSave)
									scrollbar.moveViewToPositionY(i->getPosition().y + i->getSize().y / 2);
							searchBox.setText("");
							searchBox.setActive(false);
							allFoundButtons.clear();
							lastSearchedButton = saveButtons.end();
						}
					}
					else
					{
						wasNameChangeCorrectly = false;
						feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Nazwa zapisu nie mo¿e byæ pusta", 60, stateData.resources.font);
					}
				}
				else
				{
					wasNameChangeCorrectly = false;
					feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Wpisana nazwa jest ju¿ zajêta", 60, stateData.resources.font);
				}
			}
			else
			{
				if (isAddingSave)
				{
					isAddingSave = false;
					saveButtons.erase(saveButtons.begin());
					lastSearchedButton = saveButtons.end();
					updatePageHeight();
					setPositionOfSaveButtons();
					wasMousePressed = false;
				}
			}

		}
	}
	else
	{
		for (auto& i : saveButtons)
		{
			if (i->wasPressed(mousePositionView, wasMousePressed) and !i->wasNameChangerPressed(mousePositionView, wasMousePressed) and !i->wasDeleteSavePressed(mousePositionView, wasMousePressed))
			{
				wasMousePressed = false;
				loadFile(makeFilePathByNameOfSaveButton(i->getName()));
				moveToNextState(*i);
			}
		}
	}
}

void FileSelection::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(view);
	target.draw(background, states);
	drawSaveButtons(target, states);

	if (isMouseOverSaveButtons)
	{
		if (infoAboutCurrentSave)
			target.draw(*infoAboutCurrentSave, states);
	}
	target.setView(HUDView);
	target.draw(scrollbar);
	target.draw(searchBox);
	target.draw(searcherNext);
	target.draw(searcherPrevious);
	target.draw(deleteSearching);
	target.draw(searcherTheClosest);
	target.draw(howSortButton);
	target.draw(saveCreator);
	target.draw(sort);
	target.draw(backToPreviousState);

	if (areYouSureToDeleteSave)
		target.draw(*areYouSureToDeleteSave);
	if (feedback)
		target.draw(*feedback, states);

	target.setView(view);
}


void FileSelection::findAllButtons(const std::string& searchedName)
{
	allFoundButtons.clear();
	if (searchBox.getText() != "")
	{
		for (auto i = saveButtons.begin(); i != saveButtons.end(); i++)
		{
			if (i->get()->getName().find(searchBox.getText()) != std::string::npos)
				allFoundButtons.emplace_back(i);
		}
	}

}

void FileSelection::searchNext(const std::string& searchedName)
{
	int indexOfStartButton = 0;
	bool wasFound = false;

	if (lastSearchedButton == saveButtons.end())
		indexOfStartButton = ((view.getCenter().y - view.getSize().y / 2 + 615) / 300.f);
	else
		indexOfStartButton = lastSearchedButton - saveButtons.begin() + 1;

	for (auto i = saveButtons.begin() + indexOfStartButton; i != saveButtons.end(); i++)
	{
		if (i->get()->getName().find(searchBox.getText()) != std::string::npos)
		{
			scrollbar.moveViewToPositionY(i->get()->getPosition().y + i->get()->getSize().y / 2);
			lastSearchedButton = i;
			wasFound = true;
			break;
		}
	}
	if (!wasFound)
	{
		for (auto i = saveButtons.begin(); i != saveButtons.begin() + indexOfStartButton; i++)
		{
			if (i->get()->getName().find(searchBox.getText()) != std::string::npos)
			{
				scrollbar.moveViewToPositionY(i->get()->getPosition().y + i->get()->getSize().y / 2);
				lastSearchedButton = i;
				wasFound = true;
				break;
			}
		}
	}
	if (!wasFound)
	{
		feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Nie uda³o siê znaleŸæ ¿adnego zapisu :/", 60, stateData.resources.font);
		lastSearchedButton = saveButtons.end();
	}

}

void FileSelection::searchPrevious(const std::string& searchedName)
{
	int indexOfStartButton = 0;
	bool wasFound = false;
	if (lastSearchedButton == saveButtons.end())
	{
		indexOfStartButton = ((view.getCenter().y - view.getSize().y / 2 + 325) / 300.f);
	}
	else
		indexOfStartButton = lastSearchedButton - saveButtons.begin() - 1;

	for (auto i = saveButtons.begin() + indexOfStartButton; i != saveButtons.begin() - 1; i--)
	{
		if (i->get()->getName().find(searchBox.getText()) != std::string::npos)
		{
			scrollbar.moveViewToPositionY(i->get()->getPosition().y + i->get()->getSize().y / 2);
			lastSearchedButton = i;
			wasFound = true;
			break;
		}
	}

	if (!wasFound)
	{
		for (auto i = saveButtons.end() - 1; i != saveButtons.begin() + indexOfStartButton; i--)
		{
			if (i->get()->getName().find(searchBox.getText()) != std::string::npos)
			{
				scrollbar.moveViewToPositionY(i->get()->getPosition().y + i->get()->getSize().y / 2);
				lastSearchedButton = i;
				wasFound = true;
				break;
			}
		}
	}

	if (!wasFound)
	{
		feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Nie uda³o siê znaleŸæ ¿adnego zapisu :/", 60, stateData.resources.font);
		lastSearchedButton = saveButtons.end();
	}

}

void FileSelection::searchTheClosest(const std::string& searchedName)
{
	int indexOfStartButton = 0;
	bool wasFound = false;

	indexOfStartButton = ((view.getCenter().y - view.getSize().y / 2 + 470) / 300.f);

	std::vector<std::unique_ptr< SaveButton >>::iterator found;

	for (auto i = saveButtons.begin() + indexOfStartButton; i != saveButtons.end(); i++)
	{
		if (i->get()->getName().find(searchBox.getText()) != std::string::npos)
		{
			found = i;
			wasFound = true;
			break;
		}
	}
	bool wasFoundPrevious = false;
	for (auto i = saveButtons.begin() + indexOfStartButton; i != saveButtons.begin() - 1; i--)
	{
		if (i->get()->getName().find(searchBox.getText()) != std::string::npos)
		{
			wasFoundPrevious = true;
			if (wasFound)
			{
				if (abs(i->get()->getPosition().y - (view.getCenter().y - view.getSize().y / 2)) < abs(found->get()->getPosition().y - (view.getCenter().y - view.getSize().y / 2)))
				{
					scrollbar.moveViewToPositionY(i->get()->getPosition().y + i->get()->getSize().y / 2);
					lastSearchedButton = i;
				}
				else
				{
					scrollbar.moveViewToPositionY(i->get()->getPosition().y + i->get()->getSize().y / 2);
					lastSearchedButton = found;
				}
			}
			else
			{
				scrollbar.moveViewToPositionY(i->get()->getPosition().y + i->get()->getSize().y / 2);
				lastSearchedButton = i;
			}

			wasFound = true;
			break;
		}
	}
	if (!wasFoundPrevious and wasFound)
	{
		scrollbar.moveViewToPositionY(found->get()->getPosition().y + found->get()->getSize().y / 2);
		lastSearchedButton = found;
	}
	else if (!wasFound)
	{
		feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Nie uda³o siê znaleŸæ ¿adnego zapisu :/", 60, stateData.resources.font);
		lastSearchedButton = saveButtons.end();
	}
}

void FileSelection::handleSearch(const float deltaTime)
{
	searchBox.update(mousePositionHUD, wasMousePressed, deltaTime);
	if (searchBox.getText() != "")
	{
		searcherNext.update(mousePositionHUD);
		searcherPrevious.update(mousePositionHUD);
		searcherTheClosest.update(mousePositionHUD);
		deleteSearching.update(mousePositionHUD);
	}
	else
	{
		searcherNext.setCurrentColor(sf::Color(150, 150, 150));
		searcherPrevious.setCurrentColor(sf::Color(150, 150, 150));
		searcherTheClosest.setCurrentColor(sf::Color(150, 150, 150));
		deleteSearching.setCurrentColor(sf::Color(150, 150, 150));
		if (searcherNext.wasPressed(mousePositionHUD, wasMousePressed) or searcherPrevious.wasPressed(mousePositionHUD, wasMousePressed) or searcherTheClosest.wasPressed(mousePositionHUD, wasMousePressed))
			feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Nie mo¿na szukaæ pustej frazy!", 60, stateData.resources.font);
		if (deleteSearching.wasPressed(mousePositionHUD, wasMousePressed))
			feedback = std::make_unique<Feedback>(sf::Vector2f(0, 850), L"Nie mo¿na usun¹æ pustej frazy!", 60, stateData.resources.font);
	}
	if (searcherNext.wasPressed(mousePositionHUD, wasMousePressed) or searcherPrevious.wasPressed(mousePositionHUD, wasMousePressed) or searcherTheClosest.wasPressed(mousePositionHUD, wasMousePressed))
		searchBox.setActive(true);
	if (searcherNext.wasPressed(mousePositionHUD, wasMousePressed) and searchBox.getText() != "")
		searchNext(searchBox.getText());
	if (searcherPrevious.wasPressed(mousePositionHUD, wasMousePressed) and searchBox.getText() != "")
		searchPrevious(searchBox.getText());
	if (searcherTheClosest.wasPressed(mousePositionHUD, wasMousePressed) and searchBox.getText() != "")
		searchTheClosest(searchBox.getText());
	if (wasEnterPressed)
	{
		if (searchBox.isActive() and searchBox.getText() != "")
			searchTheClosest(searchBox.getText());
	}
	if (searchBox.wasPressed(mousePositionHUD, wasMousePressed) and searchBox.getText() != "")
		findAllButtons(searchBox.getText());

	if (wasUpPressed)
		searchPrevious(searchBox.getText());
	if (wasDownPressed)
		searchNext(searchBox.getText());
	if (wasEscapePressed)
	{
		if (searchBox.isActive())
		{
			lastSearchedButton = saveButtons.end();
			allFoundButtons.clear();
			searchBox.setActive(false);
		}
	}

	if (deleteSearching.wasPressed(mousePositionHUD, wasMousePressed))
	{
		lastSearchedButton = saveButtons.end();
		searchBox.setText("");
		allFoundButtons.clear();
	}

	for (auto& i : allFoundButtons)
		i->get()->setIdleColor(sf::Color(0, 255, 255));

	if (lastSearchedButton != saveButtons.end())
		lastSearchedButton->get()->setIdleColor(sf::Color::Green);
}

void FileSelection::handleSortOfButtons()
{
	howSortButton.update(mousePositionHUD, wasMousePressed);
	if (howSortButton.wasNewOptionChosen())
		sortSaveButtons();
}

void FileSelection::sortSaveButtons()
{
	std::string nameOfLastFound;
	if (lastSearchedButton != saveButtons.end())
		nameOfLastFound = lastSearchedButton->get()->getName();
	switch (howSortButton.getNumberOfChosenOption())
	{
	case 0:
		std::sort(saveButtons.begin(), saveButtons.end(), [](const std::unique_ptr< SaveButton >& a, const std::unique_ptr< SaveButton >& b) {
			std::string AName = a->getName();
			std::string BName = b->getName();
			std::transform(AName.begin(), AName.end(), AName.begin(), ::tolower);
			std::transform(BName.begin(), BName.end(), BName.begin(), ::tolower);
			return AName < BName;
			});
		break;
	case 1:
		std::sort(saveButtons.begin(), saveButtons.end(), [](const std::unique_ptr< SaveButton >& a, const std::unique_ptr< SaveButton >& b) {
			std::string AName = a->getName();
			std::string BName = b->getName();
			std::transform(AName.begin(), AName.end(), AName.begin(), ::tolower);
			std::transform(BName.begin(), BName.end(), BName.begin(), ::tolower);
			return AName > BName;
			});
		break;
	case 2:
		std::sort(saveButtons.begin(), saveButtons.end(), [](const std::unique_ptr< SaveButton >& a, const std::unique_ptr< SaveButton >& b) {
			if (a->getDateOfLastRun() == b->getDateOfLastRun())
			{
				std::string AName = a->getName();
				std::string BName = b->getName();
				std::transform(AName.begin(), AName.end(), AName.begin(), ::tolower);
				std::transform(BName.begin(), BName.end(), BName.begin(), ::tolower);

				return AName < BName;
			}
			else
				return a->getDateOfLastRun() < b->getDateOfLastRun();
			});
		break;
	case 3:
		std::sort(saveButtons.begin(), saveButtons.end(), [](const std::unique_ptr< SaveButton >& a, const std::unique_ptr< SaveButton >& b) {
			if (a->getDateOfLastRun() == b->getDateOfLastRun())
			{
				std::string AName = a->getName();
				std::string BName = b->getName();
				std::transform(AName.begin(), AName.end(), AName.begin(), ::tolower);
				std::transform(BName.begin(), BName.end(), BName.begin(), ::tolower);

				return a->getDateOfCreation() > b->getDateOfCreation();
			}
			else
				return a->getDateOfLastRun() > b->getDateOfLastRun();
			});
		break;
	case 4:
		std::sort(saveButtons.begin(), saveButtons.end(), [](const std::unique_ptr< SaveButton >& a, const std::unique_ptr< SaveButton >& b) {
			if (a->getDateOfCreation() == b->getDateOfCreation())
			{
				std::string AName = a->getName();
				std::string BName = b->getName();
				std::transform(AName.begin(), AName.end(), AName.begin(), ::tolower);
				std::transform(BName.begin(), BName.end(), BName.begin(), ::tolower);
				return a->getDateOfLastRun() < b->getDateOfLastRun();

			}
			else
				return a->getDateOfCreation() < b->getDateOfCreation();
			});
		break;
	case 5:
		std::sort(saveButtons.begin(), saveButtons.end(), [](const std::unique_ptr< SaveButton >& a, const std::unique_ptr< SaveButton >& b) {
			if (a->getDateOfCreation() == b->getDateOfCreation())
			{
				std::string AName = a->getName();
				std::string BName = b->getName();
				std::transform(AName.begin(), AName.end(), AName.begin(), ::tolower);
				std::transform(BName.begin(), BName.end(), BName.begin(), ::tolower);
				return a->getDateOfLastRun() > b->getDateOfLastRun();
			}
			else
				return a->getDateOfCreation() > b->getDateOfCreation();
			});
		break;
	}
	setPositionOfSaveButtons();
	if (lastSearchedButton != saveButtons.end())
	{
		for (auto i = saveButtons.begin(); i != saveButtons.end(); i++)
		{
			if (i->get()->getName() == nameOfLastFound)
			{
				lastSearchedButton = i;
				break;
			}
		}
		scrollbar.moveViewToPositionY(lastSearchedButton->get()->getPosition().y + lastSearchedButton->get()->getSize().y / 2);
	}
	findAllButtons(searchBox.getText());
}

void FileSelection::setPositionOfSaveButtons()
{
	for (auto i = saveButtons.begin(); i != saveButtons.end(); i++)
		i->get()->setPosition(sf::Vector2f(547.5, 100.f + (i - saveButtons.begin()) * 300));
}

void FileSelection::createMessageBoxAreYouSureToDeleteSave()
{
	areYouSureToDeleteSave = std::make_unique<game::MessageBox>(HUDView.getCenter(), sf::Vector2f(575, 200), sf::Vector2f(100, 55),
		stateData.resources[TextureID::MessageboxBackground], stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
		L"Czy na pewno chcesz usunac ten save?", L"Tak", L"Nie");
}

void FileSelection::handleMessageBoxAreYouSureToDeleteSave()
{
	if (areYouSureToDeleteSave)
	{
		areYouSureToDeleteSave->update(mousePositionHUD);
		if (areYouSureToDeleteSave->FirstOptionWasPressed(mousePositionHUD, wasMousePressed))
		{
			fs::path dir = fs::current_path().string() += makeFilePathByNameOfSaveButton(deletingSaveButton->get()->getName());
			fs::remove(dir);
			saveButtons.erase(deletingSaveButton);
			areYouSureToDeleteSave.reset();
			lastSearchedButton = saveButtons.end();
			setPositionOfSaveButtons();
			updatePageHeight();
			searchBox.setText("");
			searchBox.setActive(false);
			allFoundButtons.clear();
			lastSearchedButton = saveButtons.end();
		}
		else if (areYouSureToDeleteSave->SecondOptionWasPressed(mousePositionHUD, wasMousePressed))
			areYouSureToDeleteSave.reset();
	}
}

void FileSelection::addSave()
{
	if (!isAddingSave and !isChangingSaveButtonName())
	{
		if (saveCreator.wasPressed(mousePositionHUD, wasMousePressed))
			if (saveCreator.wasPressed(mousePositionHUD, wasMousePressed))
			{
				saveButtons.emplace(saveButtons.begin(), std::make_unique<SaveButton>(sf::Vector2f(547.5, 100.f),
					stateData.resources[TextureID::SaveButton], stateData.resources[TextureID::TextboxBackground],
					stateData.resources[TextureID::GreyButton100x50], stateData.resources[TextureID::AcceptButton], stateData.resources[TextureID::DeleteButton], stateData.resources[TextureID::DeleteSaveButton],
					stateData.resources.font, SaveButtonState::changeableName));
				isAddingSave = true;
				saveButtons[0]->setDateOfLastRun("Nigdy");
				lastSearchedButton = saveButtons.end();
				setPositionOfSaveButtons();
				scrollbar.moveViewToPositionY(0);
				updatePageHeight();
			}
	}
}

void FileSelection::updatePageHeight()
{
	PageHeight = 0;
	if (saveButtons.size() > 3)
	{
		PageHeight = (saveButtons.size() - 3) * 300 - 40;
	}
	else
	{
		PageHeight = 0;
	}

}

void FileSelection::drawSaveButtons(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& i : saveButtons)
		target.draw(*i, states);
}

void FileSelection::updateButtons(const float deltaTime)
{
	if (isChangingSaveButtonName())
	{
		for (auto& i : saveButtons)
		{
			if (isChangingSaveButtonName())
			{
				i->updateIfIsChangingName(mousePositionView, wasMousePressed, deltaTime, wasNameChangeCorrectly, isNameOfSaveButtonAlreadyInUse());
			}
		}
	}
	else
	{
		for (auto& i : saveButtons)
		{
			i->updateIfIsNotChangingName(mousePositionView, wasMousePressed);
			for (auto i = saveButtons.begin(); i != saveButtons.end(); i++)
			{
				if (i->get()->wasDeleteSavePressed(mousePositionView, wasMousePressed))
				{
					createMessageBoxAreYouSureToDeleteSave();
					deletingSaveButton = i;
				}
			}
		}
	}

}

bool FileSelection::isChangingSaveButtonName()
{
	for (auto i = 0; i < saveButtons.size(); i++)
	{
		if (saveButtons[i]->getSaveButtonState() == SaveButtonState::changeableName)
		{
			numberOfButtonWhichNameIsChanging = i;
			return true;
		}
	}
	return false;
}

bool FileSelection::isNameOfSaveButtonAlreadyInUse()
{
	int numberOfSameNamesOfSaveButtons = 0;
	for (auto const& i : saveButtons)
	{
		std::string AName = saveButtons[numberOfButtonWhichNameIsChanging]->getName();
		std::string BName = i->getName();
		std::transform(AName.begin(), AName.end(), AName.begin(), ::tolower);
		std::transform(BName.begin(), BName.end(), BName.begin(), ::tolower);
		if (AName == BName)
			numberOfSameNamesOfSaveButtons++;
	}
	if (numberOfSameNamesOfSaveButtons > 1)
		return true;
	else
		return false;
}


std::string FileSelection::makeFilePathByNameOfSaveButton(const std::string& nameOfSaveButton)
{
	std::string filepath = "." + directoryPath + "\\";
	filepath += nameOfSaveButton + ".txt";
	return filepath;
}

int FileSelection::numberOfAllBoughtUpgradesFrom(const PlayerData& playerData)
{
	int numberOfAllBoughtUpgrades = 0;
	for (auto const& i : playerData.numbersOfUpgradeBought)
	{
		numberOfAllBoughtUpgrades += i.second;
	}
	return numberOfAllBoughtUpgrades;
}

