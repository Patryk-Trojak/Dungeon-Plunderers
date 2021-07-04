#pragma once
#include "State.h"
#include "MenuState.h"
#include "SaveSelectionState.h"
#include "SettingsState.h"
#include "Block.h"
#include "LevelsOfPlayerSelection.h"

class FirstMenuState :
	public MenuState
{
public:
	FirstMenuState(StateData& stateData);
	virtual ~FirstMenuState();
	virtual void update(const float deltaTime) override;
	virtual void updateInput(const float deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
private:
	void initButtons();
	void handleFunctionalityOfButtons();
	void handleFunctionalityOfMessageBox();
	virtual void makeMessageBoxAreYouSureToExit() override;

	sf::Text text;

	sf::Texture textureOfCaption;
	sf::Sprite caption;
};

