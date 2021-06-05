#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stack>
#include <memory>
#include <array>
#include "TextureHolder.h"
#include "PlayerData.h"
#include "Block.h"
#include "Block.h"
#include "Resources.h"
#include "Keybinds.h"
#include "PersistenceLoader.h"
#include "PersistenceSaver.h"
#include "DefaultPersistenceCreator.h"
#include "SettingsData.h"
#include "TextButton.h"

class State;

struct StateData {
	std::stack< std::unique_ptr< State > > states;
	Resources resources;
	PlayerData savedPlayerData;
	Keybinds keybinds;
	SettingsData settings;
	std::string nameOfCurrentlyLoadedPlayerSave;
};


class State
	:public sf::Drawable
{
public:
	State(StateData& stateData);
	virtual ~State();
	virtual void update(const float deltaTime) = 0;
	virtual void handleSFMLEvent(sf::RenderWindow& window, sf::Event& event) = 0;
	void updateMousePositions(sf::RenderWindow& window);
	const sf::View& getView() const;
	const sf::View& getHUDView() const;
	bool getCloseWindow();
	bool hasCustomCursor();
	int getNumberOfStatesPop() const;
	bool wereSettingsChanged();

protected:
	StateData& stateData;
	sf::Vector2f mousePositionView;
	sf::Vector2f mousePositionHUD;
	sf::Vector2f mousePositionWindow;
	sf::Sprite background;
	sf::View view;
	sf::View HUDView;
	TextButton backToPreviousState;
	void updateBackToPreviousState();
	bool closeWindow;
	bool HasCustomCursor;
	int numberOfStatesPop;
	virtual void updateInput(const float deltaTime) = 0;
	bool wasMousePressed;
	sf::Vector2u lastWindowSize;
	void resizeWindowProportionally(sf::RenderWindow& window, sf::Event& event);
	bool WereSettingsChanged;
};
