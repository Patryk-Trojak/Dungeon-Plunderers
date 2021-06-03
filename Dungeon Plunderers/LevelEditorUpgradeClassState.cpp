#include "pch.h"
#include "LevelEditorUpgradeClassState.h"

LevelEditorUpgradeClassState::LevelEditorUpgradeClassState(StateData& stateData)
	: PlayerUpgradeState(stateData),
	stormtrooper(sf::Vector2f(100, 30), sf::Vector2f(200, 100),
		stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
		L"Strzelec", 40),
	wizard(sf::Vector2f(400, 30), sf::Vector2f(200, 100),
		stateData.resources[TextureID::GreyButton100x50], stateData.resources.font,
		L"Czarodziej", 40)
{
	if (stateData.savedPlayerData.isStormtrooperChosen)
	{
		stormtrooper.setHoverColor(sf::Color::Red);
		stormtrooper.setIdleColor(sf::Color::Red);
	}
	else
	{
		wizard.setHoverColor(sf::Color::Red);
		wizard.setIdleColor(sf::Color::Red);
	}
	
	for (auto& i : upgradeButtons)
		i.second.setPosition(i.second.getPosition() + sf::Vector2f(0.f, 300.f));


	for (auto& i : weapons)
		i.move(0, 300);

	for (auto& i : texts)
		i.move(0, 300);
}

LevelEditorUpgradeClassState::~LevelEditorUpgradeClassState()
{
}


void LevelEditorUpgradeClassState::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	PlayerUpgradeState::draw(target, state);
	target.draw(stormtrooper, state);
	target.draw(wizard, state);
}

void LevelEditorUpgradeClassState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
{
	wasMousePressed = false;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		resizeWindowProportionally(window, event);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				wasMousePressed = true;
			}
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PersistenceSaver::saveLevelEditorPlayerData(stateData.savedPlayerData);
				numberOfStatesPop = 1;
			}
		}
	}
}

void LevelEditorUpgradeClassState::update(const float deltaTime)
{
	PlayerUpgradeState::update(deltaTime);
	stormtrooper.update(mousePositionHUD);
	wizard.update(mousePositionHUD);
	handleChangingClass();
	updateColorOfClassButtonDependingOnChosenClass();
	
}

void LevelEditorUpgradeClassState::handleChangingClass()
{
	if (stormtrooper.wasPressed(mousePositionView, wasMousePressed))
	{
		playerData.isStormtrooperChosen = true;
	}


	if (wizard.wasPressed(mousePositionView, wasMousePressed))
	{
		playerData.isStormtrooperChosen = false;
	}
}

void LevelEditorUpgradeClassState::updateColorOfClassButtonDependingOnChosenClass()
{
	if (playerData.isStormtrooperChosen)
	{
		stormtrooper.setIdleColor(sf::Color::Red);
		wizard.setIdleColor(sf::Color::White);
	}
	else
	{
		stormtrooper.setIdleColor(sf::Color::White);
		wizard.setIdleColor(sf::Color::Red);
	}
	
}

void LevelEditorUpgradeClassState::savePlayerData()
{
	PersistenceSaver::saveLevelEditorPlayerData(playerData);
}
