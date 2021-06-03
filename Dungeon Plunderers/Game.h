#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "State.h"
#include "TextureHolder.h"
#include "FirstMenuState.h"
#include "TextButton.h"
#include "PlayerData.h"
#include "LoadDataState.h"
#include "PersistenceLoader.h"
#include "PersistenceSaver.h"
#include "DefaultPersistenceCreator.h"


class Game
{
public:
	Game();
	virtual ~Game();
	void run();

private:
	StateData stateData;
	sf::RenderWindow window;
	sf::Clock deltaTimeClock;
	sf::Event event;
	sf::Vector2i lastWindowPosition;
	float deltaTime;
	int numberOfFPS;
	float timeOfUpdateFPS;
	sf::View FPSView;
	sf::Text FPS;
	bool closeWindow;
	void render();
	void update();
	void updateSFMLEvents();
	void updateDeltaTime();
	void popStates(int numberOfStates);
	void updateFPS();
};

