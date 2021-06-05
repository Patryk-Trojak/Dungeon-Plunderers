#include "pch.h"
#include "LevelSelectionState.h"

LevelSelectionState::LevelSelectionState(StateData& stateData)
	: State(stateData)	
{
	buttons.insert(std::make_pair(LevelName::Level1, TextButton(sf::Vector2f(585, 50), sf::Vector2f(750, 86),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Level 1", 60)));

	buttons.insert(std::make_pair(LevelName::Level2, TextButton(sf::Vector2f(585, 250), sf::Vector2f(750, 86),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Level 2", 60)));

	buttons.insert(std::make_pair(LevelName::Level3, TextButton(sf::Vector2f(585, 450), sf::Vector2f(750, 86),
		stateData.resources[TextureID::GreyButton750x86], stateData.resources.font,
		L"Level 3", 60)));
}

LevelSelectionState::~LevelSelectionState()
{
}

void LevelSelectionState::update(const float deltaTime) 
{
	for (auto & i : buttons)
	{
		i.second.update(mousePositionView);
	}
	handleFunctionalityOfButtons();
	updateBackToPreviousState();
}

void LevelSelectionState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
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
				stateData.states.pop();
			}
		}
	}
}

void LevelSelectionState::updateInput(const float deltaTime)
{
}

void LevelSelectionState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background, states);
	target.draw(backToPreviousState, states);
	drawButtons(target, states);
}

void LevelSelectionState::handleFunctionalityOfButtons()
{
	for (auto const&i : buttons)
	{
		if (i.second.wasPressed(mousePositionView, wasMousePressed))
		{
			LevelName levelName = i.first;
			wasMousePressed = false;
			createCurrentLevel = DefaultLevelMaker::makeFunctionCreatingDefaultLevel(levelName);
			stateData.states.push(std::make_unique<GameplayState>(stateData, createCurrentLevel));
		}
	}
}

void LevelSelectionState::drawButtons(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& i : buttons)
	{
		target.draw(i.second);
	}
}
