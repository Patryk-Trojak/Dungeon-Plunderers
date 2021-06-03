#include "pch.h"
#include "MenuState.h"


MenuState::MenuState(StateData& stateData)
	: State(stateData)
{
	wasMousePressed = false;
}


MenuState::~MenuState()
{
}

void MenuState::handleSFMLEvent(sf::RenderWindow& window, sf::Event& event)
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
				makeMessageBoxAreYouSureToExit();
			}
		}
	}
}

void MenuState::updateButtons()
{
	for (auto &i : buttons)
	{
		i.second.update(mousePositionView);
	}
}

void MenuState::drawButtons(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto const &i : buttons)
	{
		target.draw(i.second, states);
	}
}


