#include "pch.h"
#include "SecondMenuState.h"

SecondMenuState::SecondMenuState(StateData& stateData)
	:MenuState(stateData)
{

	initButtons();
}

SecondMenuState::~SecondMenuState()
{
}

void SecondMenuState::update(const float deltaTime)
{
	if (MessageBoxAreYouSureToExit)
	{
		MessageBoxAreYouSureToExit->update(mousePositionView);
		handleFunctionalityOfMessageBox();
	}
	else 
	{
		updateButtons();
		if (feedback)
			feedback->update(deltaTime);
		updateInput(deltaTime);
	}
}

void SecondMenuState::updateInput(const float deltaTime)
{
	handleFunctionalityOfButtons();	
}

void SecondMenuState::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(background, state);
	drawButtons(target, state);
	if (feedback)
		target.draw(*feedback, state);
	if(MessageBoxAreYouSureToExit)
		target.draw(*MessageBoxAreYouSureToExit, state);

	target.setView(HUDView);
}

void SecondMenuState::initButtons()
{
	buttons.insert(std::pair< std::string, TextButton >("GoToLevelSelectionState", TextButton(sf::Vector2f(810, 300), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Graj", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("GoToPlayersLevelSelectionState", TextButton(sf::Vector2f(810, 400), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Poziomy gracza", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("GoToClassSelectionState", TextButton(sf::Vector2f(810, 500), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Wybierz Postaæ", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("GoToShopState", TextButton(sf::Vector2f(810, 600), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Sklep", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("GoToSettingsState", TextButton(sf::Vector2f(810, 700), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Opcje", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("SaveData", TextButton(sf::Vector2f(810, 800), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Zapisz", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("GoToFirstMenuState", TextButton(sf::Vector2f(810, 900), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Menu G³owne", 50, ContentAlignment::center)));
}

void SecondMenuState::handleFunctionalityOfButtons()
{
	if (buttons.at("GoToLevelSelectionState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<LevelSelectionState>(stateData));
	}
	if (buttons.at("GoToPlayersLevelSelectionState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<LevelsOfPlayerSelection>(stateData, false));
	}
	if (buttons.at("GoToClassSelectionState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<ClassSelectionState>(stateData));
	}
	
	if (buttons.at("GoToShopState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<ShopState>(stateData));
	}
	if (buttons.at("GoToSettingsState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<SettingsState>(stateData));
	}
	if (buttons.at("SaveData").wasPressed(mousePositionView, wasMousePressed))
	{
		//feedback = std::make_unique<Feedback>(stateData);
		PersistenceSaver::save(stateData.savedPlayerData, stateData.nameOfCurrentlyLoadedPlayerSave);
	}
	if (buttons.at("GoToFirstMenuState").wasPressed(mousePositionView, wasMousePressed))
	{
		makeMessageBoxAreYouSureToExit();
	}
}

void SecondMenuState::handleFunctionalityOfMessageBox()
{
	if (MessageBoxAreYouSureToExit)
	{
		if (MessageBoxAreYouSureToExit->FirstOptionWasPressed(mousePositionView, wasMousePressed))
			numberOfStatesPop = 2;
		else if (MessageBoxAreYouSureToExit->SecondOptionWasPressed(mousePositionView, wasMousePressed))
			MessageBoxAreYouSureToExit.reset();
	}
}

void SecondMenuState::makeMessageBoxAreYouSureToExit()
{
	MessageBoxAreYouSureToExit = std::make_unique<game::MessageBox>(view.getCenter(), sf::Vector2f(685, 200), sf::Vector2f(100, 55),
															  stateData.resources[TextureID::MessageboxBackground], stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
															  L"Czy na pewno chcesz wróciæ do pierwszego menu?", L"Tak", L"Nie");
}
