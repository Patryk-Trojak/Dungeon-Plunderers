#include "pch.h"
#include "Game.h"


Game::Game()
	:numberOfFPS(0),
	timeOfUpdateFPS(0)
{
	stateData.states.emplace(std::make_unique< LoadDataState >(stateData));
	stateData.states.top()->update(deltaTime);
	stateData.states.pop();
	stateData.states.emplace(std::make_unique< FirstMenuState >(stateData));
	 
	if (stateData.settings.fullscreen)
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Dungeon Plunderers", sf::Style::Fullscreen);
	else
		window.create(sf::VideoMode(stateData.settings.windowSize.x, stateData.settings.windowSize.y), "Dungeon Plunderers");

	window.setPosition(stateData.settings.windowPosition);

	
	if (stateData.settings.isVerticalSyncEnabled)
		window.setVerticalSyncEnabled(true);
	else if (stateData.settings.isLimitFPSEnabled)
		window.setFramerateLimit(stateData.settings.maxFPS);

	FPSView.setSize(sf::Vector2f(1920, 1080));
	FPSView.setCenter(1920 / 2, 1080 / 2);
	FPS.setFont(stateData.resources.font);

	updateFPS();
}


Game::~Game()
{
}

void Game::run()
{
	while (window.isOpen())
	{	
		if (stateData.states.top()->getCloseWindow())
			window.close();
		updateSFMLEvents();

		if (window.hasFocus())
		{
			if (stateData.states.top()->hasCustomCursor())
				window.setMouseCursorVisible(false);
			else
				window.setMouseCursorVisible(true);

			updateDeltaTime();
			stateData.states.top()->updateMousePositions(window);
			if (stateData.states.top()->wereSettingsChanged())
				updateFPS();

			//if (deltaTime < 0.3f)
			{
				update();
				numberOfFPS++;
				timeOfUpdateFPS += deltaTime;
				if (timeOfUpdateFPS >= 0.5)
				{
					FPS.setString(std::to_string(numberOfFPS * 2));
					numberOfFPS = 0;
					timeOfUpdateFPS = 0;
				}
			}

			render();
			if (window.getPosition() != lastWindowPosition)
			{
				stateData.settings.windowPosition = window.getPosition();
				PersistenceSaver::save(stateData.settings);
			}
			lastWindowPosition = window.getPosition();
			popStates(stateData.states.top()->getNumberOfStatesPop());
		}		
	}
}

void Game::render()
{
	window.clear(sf::Color(20, 20, 20));
	window.draw(*stateData.states.top());
	if (stateData.settings.showFPS)
	{
		sf::View WindowView = window.getView();
		window.setView(FPSView);
		window.draw(FPS);
		window.setView(WindowView);
	}
	
	window.display();
}

void Game::update()
{
	stateData.states.top()->update(deltaTime);
}

void Game::updateSFMLEvents()
{
	stateData.states.top()->handleSFMLEvent(window, event);
}

void Game::updateDeltaTime()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::XButton1))
		deltaTime = deltaTimeClock.restart().asSeconds() * 2;
	else if (sf::Mouse::isButtonPressed(sf::Mouse::XButton2))
		deltaTime = deltaTimeClock.restart().asSeconds() * 0.1;
	else
		deltaTime = deltaTimeClock.restart().asSeconds();
}

void Game::popStates(int numberOfStates)
{
	for (int i = 0; i < numberOfStates; i++)
	{
		if (!stateData.states.empty())
			stateData.states.pop();
		else
			window.close();
	}
}

void Game::updateFPS()
{
	FPS.setCharacterSize(stateData.settings.characterSizeOfFPS);

	FPS.setFillColor(stateData.settings.colorOfFPS);
	std::string currentFPS = FPS.getString();
	FPS.setString("9999");
	FPS.setOutlineThickness(0);

	if(stateData.settings.FPSOnLeft)
		FPS.setPosition(sf::Vector2f(10, 0));
	else
		FPS.setPosition(sf::Vector2f(1910 - FPS.getGlobalBounds().width , 0));

	if (stateData.settings.FPSOnTop)
		FPS.setPosition(sf::Vector2f(FPS.getPosition().x, 10));
	else
		FPS.setPosition(sf::Vector2f(FPS.getPosition().x, 1080 - FPS.getCharacterSize() * 0.6 - 10));

	if (stateData.settings.showOutlineFPS)
	{
		FPS.setOutlineThickness(stateData.settings.outlineThickness);
		FPS.setOutlineColor(stateData.settings.colorOfOutlineFPS);
	}
	else
	{
		FPS.setOutlineThickness(0);
		FPS.setOutlineColor(sf::Color::Black);
	}

	FPS.setString(currentFPS);
	FPS.setOrigin(sf::Vector2f(0.f, FPS.getCharacterSize() * 0.4f));
}



