#include "pch.h"
#include "FirstMenuState.h"


FirstMenuState::FirstMenuState(StateData& stateData)
	:MenuState(stateData)
{
	initButtons();

	text.setFont(stateData.resources.font);
	text.setCharacterSize(200);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(10);
	text.setString("Dungeon Plunderers");
	text.setPosition(view.getCenter().x - text.getGlobalBounds().width / 2, 70);

	textureOfCaption.loadFromFile(".\\Textures\\inscription.png");

	caption.setTexture(textureOfCaption);
	caption.setPosition(sf::Vector2f((1920 - textureOfCaption.getSize().x) / 2, 120));

}


FirstMenuState::~FirstMenuState()
{
}

void FirstMenuState::update(const float deltaTime)
{
	if(MessageBoxAreYouSureToExit)
		MessageBoxAreYouSureToExit->update(mousePositionView);
	else
		updateButtons();
	updateInput(deltaTime);
}

void FirstMenuState::updateInput(const float deltaTime)
{
	if (!MessageBoxAreYouSureToExit)
		handleFunctionalityOfButtons();
	handleFunctionalityOfMessageBox();
}

void FirstMenuState::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.setView(view);
	target.draw(background, states);
	drawButtons(target, states);
	if (MessageBoxAreYouSureToExit)
		target.draw(*MessageBoxAreYouSureToExit);
	target.setView(HUDView);
	//temp
	target.draw(caption);
}

void FirstMenuState::initButtons()
{
	buttons.insert(std::pair< std::string, TextButton >("GoToSaveSelectionState", TextButton(sf::Vector2f(810, 300), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Graj", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("GoToLevelsOfPlayerSelectionState", TextButton(sf::Vector2f(810, 400), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Kreator Leveli", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("GoToSettingsState", TextButton(sf::Vector2f(810, 500), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"Opcje", 50, ContentAlignment::center)));
	buttons.insert(std::pair< std::string, TextButton >("ExitButton", TextButton(sf::Vector2f(810, 600), sf::Vector2f(300, 70), stateData.resources[TextureID::GreyButton300x70], stateData.resources.font, L"WyjdŸ", 50, ContentAlignment::center)));
}

void FirstMenuState::handleFunctionalityOfButtons()
{
	if (buttons.at("GoToLevelsOfPlayerSelectionState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<LevelsOfPlayerSelection>(stateData));
	}
	if (buttons.at("GoToSaveSelectionState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<SaveSelectionState>(stateData));
	}
	if (buttons.at("GoToSettingsState").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		stateData.states.push(std::make_unique<SettingsState>(stateData));
 	}

	if (buttons.at("ExitButton").wasPressed(mousePositionView, wasMousePressed))
	{
		wasMousePressed = false;
		makeMessageBoxAreYouSureToExit();
	}
}

void FirstMenuState::handleFunctionalityOfMessageBox()
{
	if (MessageBoxAreYouSureToExit)
	{
		if (MessageBoxAreYouSureToExit->FirstOptionWasPressed(mousePositionView, wasMousePressed))
			closeWindow = true;
		else if (MessageBoxAreYouSureToExit->SecondOptionWasPressed(mousePositionView, wasMousePressed))
			MessageBoxAreYouSureToExit.reset();
	}
}

void FirstMenuState::makeMessageBoxAreYouSureToExit()
{
	MessageBoxAreYouSureToExit = std::make_unique<game::MessageBox>(view.getCenter(), sf::Vector2f(575, 200), sf::Vector2f(100, 55),
		stateData.resources[TextureID::MessageboxBackground], stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
		L"Czy na pewno chcesz wyjœæ z gry?", L"Tak", L"Nie");
}
